# Hướng dẫn sử dụng

## Giới thiệu
Chương trình này cung cấp một số chức năng cơ bản để thao tác với tệp tin và thư mục trong hệ thống tệp Linux. Dưới đây là mô tả về các chức năng chính:

**In thông tin tệp tin/thư mục:** Hiển thị thông tin chi tiết của tệp tin hoặc thư mục, bao gồm kiểu, số liên kết, quyền truy cập, kích thước và thời gian tạo, sửa đổi và truy cập lần cuối.

   ```bash
   ./programname -p filename [path]
1. Tạo tệp mới: Tạo một tệp tin mới với tên được chỉ định.

bash

./programname -c filename [path]
Đọc nội dung tệp tin: Hiển thị nội dung của một tệp tin.

bash
Copy code
./programname -r filename [path]
Sửa nội dung tệp tin: Mở tệp tin trong trình soạn thảo Nano để sửa đổi.

bash
Copy code
./programname -e filename [path]
Xóa tệp tin/thư mục: Xóa một tệp tin hoặc thư mục.

bash
Copy code
./programname -d filename [path]
Đổi tên tệp tin/thư mục: Đổi tên một tệp tin hoặc thư mục.

bash
Copy code
./programname -rn old_filename new_filename [path]
Sao chép tệp tin: Sao chép nội dung từ một tệp tin vào một tệp tin mới.

bash
Copy code
./programname -cp src_filename dest_filename [path]
Di chuyển tệp tin: Di chuyển một tệp tin từ một vị trí đến vị trí khác.

bash
Copy code
./programname -cd oldpath filename newpath
Liệt kê tệp tin trong thư mục: Hiển thị danh sách các tệp tin trong thư mục được chỉ định.

bash
Copy code
./programname -ls path
