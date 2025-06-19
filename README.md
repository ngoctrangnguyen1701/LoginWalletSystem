### Giới thiệu dự án
Dự án Hệ thống đăng nhập và đăng ký chủ yếu liên quan đến quá trình đăng ký người dùng. Thông tin xác thực người dùng như tên người dùng và mật khẩu được yêu cầu từ người dùng. Nếu người dùng đăng ký thành công thì với thông tin xác thực được cung cấp, một bản ghi (có thể là tập tin) của người dùng cụ thể sẽ được tạo trong cơ sở dữ liệu (CSDL).
Ví điểm thưởng là cơ chế quản lý các lượng (đơn vị : điểm) được dùng để quy đổi ra hàng hóa (còn gọi là hoạt động mua - bán). Giữa các ví có giao dịch chuyển điểm.


🔹 Ngôn ngữ: **C++**  
🔹 Hỗ trợ trên: **Windows / Mac / Linux**  
🔹 Giao diện: **Dòng lệnh văn bản**
🔹 Lưu trữ: **File văn bản (không sử dụng CSDL)**


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
**🔹 Biên dịch chương trình bằng DevC++**
1. Mở DevC++
2. Chọn File → Open → Vào folder tải chương trình → Chọn folder `src` → Chọn file `LoginWalletSystem.dev`
3. Chọn Execute → Rebuild All
4. Sau khi build thành công, vào lại folder tải chương trình → Chọn folder `src` → Mở file `LoginWalletSystem.exe` với quyền admin (Click chuột phải chọn `Run as administrator`)<br>
*_Lưu ý 1: Nếu dùng Execute → Run của DevC++ để chạy chương trình, một số tính năng sẽ không hoạt động đúng do phân quyền của hệ điều hành*<br>
*_Lưu ý 2: Trường hợp chạy lệnh `Execute → Rebuild All` bị lỗi, vào folder tải chương trình → Chọn folder `src` → Xóa file `LoginWalletSystem.exe`, rồi chạy lại lệnh*

**🔹 Biên dịch chương trình bằng Visual Studio Code**
1. Mở Visual Studio Code với quyền admin (Click chuột phải chọn `Run as administrator`)
2. Cài đặt C++ compiler (MinGW cho Windows, GCC cho Linux, hoặc Clang cho macOS)<br>
*Sau khi cài đặt compiler thành công dùng lệnh `g++ --version` ở terminal để kiểm tra*
3. Cài đặt C/C++ extension trong VSCode
*[Xem hướng dẫn chi tiết cho bước 2 và 3](https://code.visualstudio.com/docs/languages/cpp)*
4. Trên thanh công cụ, chọn `File` -> `Open Folder` -> chọn thư mục nơi tải chương trình
5. Chọn terminal mặc định<br>
_Trên thanh công cụ, chọn `View` -> `Command Palette...` -> gõ `Terminal: Select Default Profile` -> nhấn Enter<br>
_Nếu dùng hệ điều hành Windows chọn `Command Prompt`, macOS hoặc Linux chọn `bash`<br>
6. Trên thanh công cụ, chọn `Terminal` -> `Run Build Task...`
7. Chọn `Build and run the program LoginWalletSystem`<br>
*_Lưu ý 1: Nếu chương trình build bằng Visual Studio Code thành công nhưng chạy bị lỗi do khác môi trường đường dẫn(path),*<br>
*vào folder tải chương trình → Chọn folder `src` → Mở file `LoginWalletSystem.exe` với quyền admin (Click chuột phải chọn `Run as administrator` đối với hệ điều hành Windows, hệ điều hành khác chỉ cần mở file bình thường)*<br>
*_Lưu ý 2: Trường hợp chạy lệnh `Run Build Task...` bị lỗi, vào folder tải chương trình → Chọn folder `src` → Xóa file `LoginWalletSystem.exe`, rồi chạy lại lệnh*
---

### Dữ liệu cho sẵn trong chương trình
*Xem chi tiết trong file [Dữ liệu cho sẵn](./docs/Du_lieu_mau.md).*

---

### Thao tác chính trong chương trình
*Xem chi tiết trong file [Hướng dẫn thao tác](./docs/Huong_dan_thao_tac.md).*

---

### Tài liệu tham khảo
- [C++ SHA256 hash generator](https://github.com/B-Con/crypto-algorithms)
- [TOTP (Time-based One-Time Password)](https://chatgpt.com/share/685046f1-8e78-8001-8c04-f237c59a9347)

---

### Sơ đồ
[Chi tiết](https://docs.google.com/spreadsheets/d/15pDtCsO1byHXWuiSaONQUGUSVJRMGmBcl1brPSEpmDE/edit?gid=1628233281#gid=1628233281)

---

### Tài liệu đề xuất giải pháp
[Chi tiết]([https://docs.google.com/document/d/1xMLW7Kc3PsWiafz0cpkj4xGTv_zypUjc/edit](https://docs.google.com/document/d/1xMLW7Kc3PsWiafz0cpkj4xGTv_zypUjc/edit?usp=sharing&ouid=104113783284477848584&rtpof=true&sd=true))

---

### Cấu trúc thư mục
[Chi tiết](./docs/Cau_truc_thu_muc.md)
