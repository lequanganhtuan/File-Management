#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <libgen.h>


void print_file_info(const char *name) {
    struct stat file_stat;

    if (stat(name, &file_stat) == -1) {
        perror("stat");
        return;
    }

    printf("File path: \t\t%s\n", name);

    printf("File type: \t\t");
    if (S_ISREG(file_stat.st_mode)) {
        printf("Regular File\n");
    } else if (S_ISDIR(file_stat.st_mode)) {
        printf("Directory\n");
    } else {
        printf("Unknown\n");
    }

    printf("Number of links: \t%ld\n", (long)file_stat.st_nlink);

    struct passwd *pwd = getpwuid(file_stat.st_uid);
    if (pwd != NULL) {
        printf("Owner: \t\t\t%s\n", pwd->pw_name);
    }

    struct group *grp = getgrgid(file_stat.st_gid);
    if (grp != NULL) {
        printf("Group: \t\t\t%s\n", grp->gr_name);
    }

    printf("Permissions: \t\t");
    printf((S_ISDIR(file_stat.st_mode)) ? "d" : "-");
    printf((file_stat.st_mode & S_IRUSR) ? "r" : "-");
    printf((file_stat.st_mode & S_IWUSR) ? "w" : "-");
    printf((file_stat.st_mode & S_IXUSR) ? "x" : "-");
    printf((file_stat.st_mode & S_IRGRP) ? "r" : "-");
    printf((file_stat.st_mode & S_IWGRP) ? "w" : "-");
    printf((file_stat.st_mode & S_IXGRP) ? "x" : "-");
    printf((file_stat.st_mode & S_IROTH) ? "r" : "-");
    printf((file_stat.st_mode & S_IWOTH) ? "w" : "-");
    printf((file_stat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    printf("File size: \t\t%ld byte\n", (long)file_stat.st_size);

    printf("Last access time: \t%s", ctime(&file_stat.st_atime));
    printf("Last modification time: %s", ctime(&file_stat.st_mtime));
    printf("Create time: \t\t%s", ctime(&file_stat.st_ctime));

    printf("/-----------------------/\n");
}

void create_file(const char *name) {
    if (access(name, F_OK) != -1) {
        fprintf(stderr, "Error: File '%s' already exists. Please choose a different name.\n", name);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(name, "w");
    if (file == NULL) {
        perror("create_file");
        exit(EXIT_FAILURE);
    }
    fclose(file);
    printf("File created successfully: %s\n", name);
}

void read_file(const char *name) {
    struct stat file_stat;

    if (stat(name, &file_stat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    if (S_ISDIR(file_stat.st_mode)) {
        fprintf(stderr, "Error: Cannot read a directory. Please provide a valid file name.\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(name, "r");
    if (file == NULL) {
        perror("read_file");
        exit(EXIT_FAILURE);
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}

void edit_file(const char *name) {
    struct stat file_stat;

    if (stat(name, &file_stat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    if (S_ISDIR(file_stat.st_mode)) {
        fprintf(stderr, "Error: Cannot edit a directory. Please provide a valid file name.\n");
        exit(EXIT_FAILURE);
    }

    char command[256];
    snprintf(command, sizeof(command), "nano %s", name);
    system(command);
    printf("File edited successfully: %s\n", name);
}

int delete_file(const char *name) {
    struct stat file_stat;

    if (stat(name, &file_stat) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    if (S_ISDIR(file_stat.st_mode)) {
        DIR *dir;
        struct dirent *entry;
        int is_empty = 1;

        if ((dir = opendir(name)) != NULL) {
            while ((entry = readdir(dir)) != NULL) {
                if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                    is_empty = 0;
                    break;
                }
            }
            closedir(dir);
        } else {
            perror("delete_file");
            exit(EXIT_FAILURE);
        }

        if (is_empty) {
            if (rmdir(name) == 0) {
                return 0;
            } else {
                perror("delete_file");
            }
        } else {
            fprintf(stderr, "Error: Cannot delete non-empty directory '%s'.\n", name);
        }
    } else {
        if (remove(name) == 0) {
            return 0;
        } else {
            perror("delete_file");
        }
    }
    return 1;
}

void rename_file(const char *old_name, const char *new_name) {
    if (strcmp(old_name, new_name) == 0) {
        fprintf(stderr, "Error: New file name is the same as the old file name. Please choose a different name.\n");
        exit(EXIT_FAILURE);
    }

    if (access(new_name, F_OK) != -1) {
        fprintf(stderr, "Error: File '%s' already exists. Please choose a different name.\n", new_name);
        exit(EXIT_FAILURE);
    }

    if (rename(old_name, new_name) == 0) {
        printf("File renamed successfully: %s -> %s\n", old_name, new_name);
    } else {
        perror("rename_file");
    }
}

void copy_file(const char *src_name, const char *dest_name) {
    struct stat src_stat;
    struct stat dest_stat;

    if (stat(src_name, &src_stat) == -1 || stat(dest_name, &dest_stat) == -1) {
        exit(EXIT_FAILURE);
    }

    if (S_ISDIR(src_stat.st_mode)) {
        exit(EXIT_FAILURE);
    }

    if (S_ISDIR(dest_stat.st_mode)) {
        char dest_file_path[PATH_MAX];

        // Duplicate the source name to create a non-const version
        char *src_name_copy = strdup(src_name);
        if (src_name_copy == NULL) {
            exit(EXIT_FAILURE);
        }

        snprintf(dest_file_path, sizeof(dest_file_path), "%s/%s", dest_name, basename(src_name_copy));

        // Free the allocated memory for the duplicated source name
        free(src_name_copy);

        FILE *src_file = fopen(src_name, "rb");
        FILE *dest_file = fopen(dest_file_path, "wb");

        if (src_file == NULL || dest_file == NULL) {
            exit(EXIT_FAILURE);
        }

        char buffer[1024];
        size_t bytesRead;

        while ((bytesRead = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
            fwrite(buffer, 1, bytesRead, dest_file);
        }

        fclose(src_file);
        fclose(dest_file);
    } else {
        fprintf(stderr, "Error: Destination '%s' is not a directory. Please provide a valid directory name.\n", dest_name);
    }
}

void move_file(char *old_path, char *new_path) {

    copy_file(old_path, new_path);
    delete_file(old_path);

    printf("Move successfully\n");
}



void list_files(const char *path) {
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(path)) == NULL) {
        perror("list_files");
        fprintf(stderr, "Error: Cannot open directory '%s'. Please enter a valid path.\n", path);
        exit(EXIT_FAILURE);
    }

    printf("Files in directory '%s':\n", path);

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

void checkpath(char * path) {
    if (access(path, F_OK) == -1) {
    	fprintf(stderr, "Error: Path '%s' does not exist. Please enter a valid path.\n", path);
    	exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s -c/-r/-e/-d/-rn/-cp/-cd/-ls old_filename new_filename [path]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char * command = argv[1];
    char * filename = argv[2];
    char * path = (argc >= 4) ? argv[argc-1] : ".";
    char * new_path = "";

    checkpath(path);
    chdir(path);
    
    if (strcmp(command, "-p") == 0) {
    	print_file_info(filename);
    } else if (strcmp(command, "-c") == 0) {
    	create_file(filename);
    } else if (strcmp(command, "-r") == 0) {
    	read_file(filename);
    } else if (strcmp(command, "-e") == 0) {
    	edit_file(filename);
    } else if (strcmp(command, "-d") == 0) {
    	if (delete_file(filename) == 0) {
    		printf("Deleted successfully \n");
    	};
    } else if (strcmp(command, "-ls") == 0) {
    	list_files(filename);
    } else if (strcmp(command, "-cd") == 0) {
    	path = (argc >= 3) ? argv[2] : ".";
    	checkpath(path);
	new_path = (argc >= 4) ? argv[3] : ".";
	checkpath(new_path);
    	move_file(path, new_path);
    } else if (strcmp(command, "-rn") == 0) {
	char * new_filename = (argc >= 4) ? argv[3] : NULL;
        if (new_filename != NULL) {
            rename_file(filename, new_filename);
        } else {
            fprintf(stderr, "Usage: %s -rn old_filename new_filename [path]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Invalid command\n");
        exit(EXIT_FAILURE);	
    }
    return 0;
}
