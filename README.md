### Giới thiệu dự án
Dự án Hệ thống đăng nhập và đăng ký chủ yếu liên quan đến quá trình đăng ký người dùng. Thông tin xác thực người dùng như tên người dùng và mật khẩu được yêu cầu từ người dùng. Nếu người dùng đăng ký thành công thì với thông tin xác thực được cung cấp, một bản ghi (có thể là tập tin) của người dùng cụ thể sẽ được tạo trong cơ sở dữ liệu (CSDL).
Ví điểm thưởng là cơ chế quản lý các lượng (đơn vị : điểm) được dùng để quy đổi ra hàng hóa (còn gọi là hoạt động mua - bán). Giữa các ví có giao dịch chuyển điểm.


🔹 Công nghệ sử dụng: **C++**  
🔹 Hỗ trợ trên: **Windows / Mac / Linux**  
🔹 Trạng thái: **Đang phát triển**  
<!-- - - Trạng thái: **[Hoàn thành / Đang phát triển]**   -->

---

### 👥 Thành viên tham gia dự án
| Mã SV       | Họ, đệm              | Tên     | Lớp            |
|------------|------------------|--------|--------------|
| B24DTCN064 | Trương Thượng    | Tiến   | D24TXCN06-B  |
| B24DTCN498 | Dương Tất        | Trường | D24TXCN12-B  |
| K24DTCN661 | Thái Thị Thanh   | Hòa    | D24TXCN16-K  |
| K24DTCN673 | Nguyễn Ngọc      | Trang  | D24TXCN16-K  |

*Xem chi tiết công việc trong file [Phân công công việc](./docs/Phan_cong_cong_viec.md).*

---

### Phân tích & đặc tả chức năng
*Xem chi tiết trong file [Yêu cầu tính năng](./docs/Yeu_cau_chuc_nang.md) và file [Phân tích chức năng](./docs/Phan_tich_tong_hop_chuc_nang.md).*

---

### 📥 Hướng dẫn tải & cài đặt
**🔹 Yêu cầu hệ thống**
- Hệ điều hành: Windows 10+, macOS, Linux
- Công cụ hỗ trợ: DevC++, Visual Studio Code

**🔹 Tải chương trình**
1. Download git: https://git-scm.com/downloads
2. Sử dụng giao diện terminal
```sh
git clone https://github.com/ngoctrangnguyen1701/LoginWalletSystem.git
```
```sh
cd LoginWalletSystem
```
```sh
git checkout develop
```
<!-- TODO MacOS và Linux không có dev C++, nên viết hướng dẫn thêm ở 1 IDE khác -->
**🔹 Biên dịch chương trình bằng DevC++**
1. Mở DevC++
2. Chọn File → Open → Vào folder tải chương trình → Chọn folder `src` → Chọn file `LoginWalletSystem.dev`
3. Chọn Execute → Rebuild All (hoặc nhấn phím tắt F12)
4. Sau khi build thành công, chọn Execute → Run (hoặc nhấn phím tắt F10)

<!-- TODO -->
**🔹 Biên dịch chương trình bằng Visual Studio Code**
1. Mở Visual Studio Code
2. Cài đặt C++ compiler (MinGW cho Windows, GCC cho Linux, hoặc Clang cho macOS)
3. Cài đặt C/C++ extension trong VSCode
*[Xem hướng dẫn chi tiết cho bước 2 và 3](https://code.visualstudio.com/docs/languages/cpp)*
4. Trong Visual Studio Code, Chọn File -> Open Folder -> chọn folder nơi tải chương trình
5. Trên thanh công cụ, chọn Terminal -> Run Build Task... (hoặc nhấn phím tắt Ctrl+Shift+B trên Windows/Linux, Cmd+Shift+B trên macOS)
6. Chọn `Build and run the program LoginWalletSystem`

---

### Thao tác chính trong chương trình
*Xem chi tiết trong file [Hướng dẫn thao tác](./docs/Huong_dan_thao_tac.md).*

---

### Tài liệu tham khảo
<!-- nội dung đang cập nhật -->
- [C++ SHA256 hash generator](https://github.com/okdshin/PicoSHA2)
- [Tên tài liệu 1](https://example.com)
- [Tên tài liệu 2](https://example.com)

---

### Sơ đồ
[Chi tiết](https://docs.google.com/spreadsheets/d/15pDtCsO1byHXWuiSaONQUGUSVJRMGmBcl1brPSEpmDE/edit?gid=1628233281#gid=1628233281)
---

### Cấu trúc thư mục
[Chi tiết](./docs/Cau_truc_thu_muc.md)
