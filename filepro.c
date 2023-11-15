#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>

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
    FILE *file = fopen(name, "w");
    if (file == NULL) {
        perror("create_file");
        exit(EXIT_FAILURE);
    }
    fclose(file);
    printf("File created successfully: %s\n", name);
}

void read_file(const char *name) {
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
    char command[256];
    snprintf(command, sizeof(command), "nano %s", name);
    system(command);
    printf("File edited successfully: %s\n", name);
}

void delete_file(const char *name) {
    if (remove(name) == 0) {
        printf("File deleted successfully: %s\n", name);
    } else {
        perror("delete_file");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s -c/-r/-e/-d filename [path]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *command = argv[1];
    char *file = argv[2];
    char *path = (argc == 4) ? argv[3] : ".";

    chdir(path);

    if (strcmp(command, "-p") == 0) {
        print_file_info(file);
    } else if (strcmp(command, "-c") == 0) {
        create_file(file);
    } else if (strcmp(command, "-r") == 0) {
        read_file(file);
    } else if (strcmp(command, "-e") == 0) {
        edit_file(file);
    } else if (strcmp(command, "-d") == 0) {
        delete_file(file);
    } else {
        fprintf(stderr, "Invalid command\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
T3 09:20
Bạn đã gửi
Bạn đã thu hồi một tin nhắn
T3 11:27
Bạn đã gửi
Bạn đã thu hồi một tin nhắn
00:35
Bạn đã gửi
Bạn đã thu hồi một tin nhắn
Bạn đã gửi
Bạn đã thu hồi một tin nhắn
Bạn đã gửi
Bạn đã thu hồi một tin nhắn
Bạn đã gửi
Bạn đã thu hồi một tin nhắn
Bạn đã gửi
Bạn đã thu hồi một tin nhắn
Bạn đã gửi
Bạn đã thu hồi một tin nhắn
Bạn đã gửi
Bạn đã thu hồi một tin nhắn
Bạn đã gửi
Bạn đã thu hồi một tin nhắn
Bạn đã gửi
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>

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
    FILE *file = fopen(name, "w");
    if (file == NULL) {
        perror("create_file");
        exit(EXIT_FAILURE);
    }
    fclose(file);
    printf("File created successfully: %s\n", name);
}

void read_file(const char *name) {
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
    char command[256];
    snprintf(command, sizeof(command), "nano %s", name);
    system(command);
    printf("File edited successfully: %s\n", name);
}

void delete_file(const char *name) {
    if (remove(name) == 0) {
        printf("File deleted successfully: %s\n", name);
    } else {
        perror("delete_file");
    }
}

void rename_file(const char *old_name, const char *new_name) {
    if (rename(old_name, new_name) == 0) {
        printf("File renamed successfully: %s -> %s\n", old_name, new_name);
    } else {
        perror("rename_file");
    }
}

void copy_file(const char *src_name, const char *dest_name) {
    FILE *src_file = fopen(src_name, "rb");
    FILE *dest_file = fopen(dest_name, "wb");

    if (src_file == NULL || dest_file == NULL) {
        perror("copy_file");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src_file)) > 0) {
        fwrite(buffer, 1, bytesRead, dest_file);
    }

    fclose(src_file);
    fclose(dest_file);

    printf("File copied successfully: %s -> %s\n", src_name, dest_name);
}

void move_file(const char *old_path, const char *filename, const char *new_path) {
    char old_full_path[PATH_MAX];
    char new_full_path[PATH_MAX];

    snprintf(old_full_path, sizeof(old_full_path), "%s/%s", old_path, filename);
    snprintf(new_full_path, sizeof(new_full_path), "%s/%s", new_path, filename);

    if (rename(old_full_path, new_full_path) == 0) {
        printf("File moved successfully: %s -> %s\n", old_full_path, new_full_path);
    } else {
        perror("move_file");
    }
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

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s -c/-r/-e/-d/-rn/-cp/-cd/-ls old_filename new_filename [path]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *command = argv[1];
    char *old_name = argv[2];
    char *new_name = (argc == 5 && (strcmp(command, "-rn") == 0 || strcmp(command, "-cp") == 0)) ? argv[3] : NULL;
    char *path = (argc == 5) ? argv[4] : ".";
    char *new_path = (argc == 6 && strcmp(command, "-cd") == 0) ? argv[5] : ".";

    if (access(path, F_OK) == -1) {
        fprintf(stderr, "Error: Path '%s' does not exist. Please enter a valid path.\n", path);
        exit(EXIT_FAILURE);
    }

    chdir(path);

    if (strcmp(command, "-p") == 0) {
        print_file_info(old_name);
    } else if (strcmp(command, "-c") == 0) {
        create_file(old_name);
    } else if (strcmp(command, "-r") == 0) {
        read_file(old_name);
    } else if (strcmp(command, "-e") == 0) {
        edit_file(old_name);
    } else if (strcmp(command, "-d") == 0) {
        delete_file(old_name);
    } else if (strcmp(command, "-rn") == 0) {
        if (new_name != NULL) {
            rename_file(old_name, new_name);
        } else {
            fprintf(stderr, "Usage: %s -rn old_filename new_filename [path]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    } else if (strcmp(command, "-cp") == 0) {
        if (new_name != NULL) {
            copy_file(old_name, new_name);
        } else {
            fprintf(stderr, "Usage: %s -cp old_filename new_filename [path]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    } else if (strcmp(command, "-cd") == 0) {
        move_file(path, old_name, new_path);
    } else if (strcmp(command, "-ls") == 0) {
        list_files(path);
    } else {
        fprintf(stderr, "Invalid command\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}