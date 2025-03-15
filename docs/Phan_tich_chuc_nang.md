### Phân tích & đặc tả chức năng
#### A. Các chức năng:
1. **Tạo mới tài khoản khi đăng ký**
   - Người dùng nhập dữ liệu để tạo tài khoản.
   - Nhân viên quản lý có thể tạo tài khoản hộ người dùng.
   - Cấu trúc dữ liệu quản lý tài khoản cần được phân tích và đề xuất.

2. **Lưu trữ dữ liệu**
   - Lưu dữ liệu tài khoản người dùng xuống tập tin.
   - Cân nhắc việc lưu trữ dưới dạng tập tin riêng lẻ hoặc tập tin chung.
   - Mật khẩu phải được lưu trữ an toàn bằng cách sử dụng hàm băm (hash function).
   - Có cơ chế sao lưu (backup) và phục hồi dữ liệu.

3. **Quản lý đăng nhập**
   - Sinh mật khẩu tự động khi người dùng không nhập mật khẩu.
   - Thay đổi mật khẩu với cơ chế kiểm tra mật khẩu tự sinh.
   - Xác thực hai lớp (OTP) cho các thay đổi thông tin quan trọng.
   - Xác thực đăng nhập để kiểm tra thông tin hợp lệ.

#### B. Phân chia người dùng và chức năng
1. **Người dùng thông thường**
   - Chỉ có quyền truy xuất và chỉnh sửa thông tin cá nhân.
   - Thay đổi mật khẩu và thông tin với xác thực OTP.

2. **Người dùng quản lý**
   - Có quyền theo dõi danh sách nhóm.
   - Tạo tài khoản mới.
   - Điều chỉnh thông tin tài khoản khi có yêu cầu, kèm theo xác thực OTP.
   - Không được thay đổi tên tài khoản đăng nhập.

#### C. Quản lý hoạt động ví
- Mỗi người dùng có một ví điện tử (wallet) với điểm số và lịch sử giao dịch.
- Ví có **mã định danh duy nhất**.
- Ví tổng là nguồn duy nhất tạo ra tổng số điểm trong hệ thống.
- **Quy trình giao dịch giữa các ví:**
  1. Xác định ví nguồn (A).
  2. Xác định ví đích (B).
  3. Kiểm tra số dư ví A, nếu đủ thực hiện giao dịch:
     - Giảm số dư ví A.
     - Tăng số dư ví B.
  4. Nếu có lỗi, hệ thống **hủy giao dịch và khôi phục số dư ban đầu**.
  