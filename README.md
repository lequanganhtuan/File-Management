# Hướng dẫn sử dụng

## Giới thiệu
Chương trình này cung cấp một số chức năng cơ bản để thao tác với tệp tin và thư mục trong hệ thống tệp Linux. Dưới đây là mô tả về các chức năng chính:

- ****In thông tin tệp tin/thư mục:** Hiển thị thông tin chi tiết của tệp tin hoặc thư mục, bao gồm kiểu, số liên kết, quyền truy cập, kích thước và thời gian tạo, sửa đổi và truy cập lần cuối.

   ```bash
   ./programname -p filename || foldername [path]
1. Tạo tệp mới: Tạo một tệp tin mới với tên được chỉ định.
    ```bash
   ./programname -c filename [path]
2. Đọc nội dung tệp tin: Hiển thị nội dung của một tệp tin.
   ```bash
   ./programname -r filename [path]
3. Sửa nội dung tệp tin: Mở tệp tin trong trình soạn thảo Nano để sửa đổi.
   ```bash
   ./programname -e filename [path]
4. Xóa tệp tin/thư mục: Xóa một tệp tin hoặc thư mục.
   ```bash
   ./programname -d filename [path]
5. Đổi tên tệp tin/thư mục: Đổi tên một tệp tin hoặc thư mục.
   ```bash
   ./programname -rn old_filename new_filename [path]
6. Di chuyển tệp tin: Di chuyển một tệp tin từ một vị trí đến vị trí khác.
   ```bash
   ./programname -cd oldpath filename newpath
7. Liệt kê tệp tin trong thư mục: Hiển thị danh sách các tệp tin trong thư mục được chỉ định.
   ```bash
   ./programname -ls [path]
