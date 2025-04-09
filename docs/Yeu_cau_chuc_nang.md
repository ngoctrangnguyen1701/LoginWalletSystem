### Phân tích & đặc tả chức năng
#### A. Các chức năng:
1. **Tạo mới tài khoản khi đăng ký**
   - Người dùng nhập dữ liệu để tạo tài khoản.
   - Nhân viên quản lý có thể tạo tài khoản hộ người dùng.
   - Cấu trúc dữ liệu quản lý tài khoản cần được phân tích và đề xuất.

2. **Lưu trữ dữ liệu**
   - Lưu dữ liệu tài khoản người dùng xuống tập tin văn bản (file .csv).
   - Cân nhắc việc lưu trữ dưới dạng tập tin riêng lẻ hoặc tập tin chung (Lý do chọn giải pháp?).
   - Mật khẩu phải được lưu trữ an toàn bằng cách sử dụng hàm băm (hash function).
   - Có cơ chế sao lưu (backup) và phục hồi dữ liệu. (Chưa rõ chức năng sao lưu sẽ theo hình thức nào? dữ liệu nào được sao lưu?)

3. **Quản lý đăng nhập**
   - Sinh mật khẩu tự động khi người dùng không nhập mật khẩu(thường dùng khi nhân viên quản lý mở tài khoản hộ).
   - Người dùng có thể thay đổi mật khẩu, với trường hợp mật khẩu tự sinh hệ thống kiểm tra có phải là tự sinh và yêu cầu người dùng thay đổi ngay mật khẩu mới trong lần đăng nhập đầu tiên của mình.
   - Xác thực hai lớp (OTP) cho các thay đổi thông tin quan trọng.
   - Xác thực đăng nhập để kiểm tra thông tin hợp lệ(thông tin đó đã được sử dụng chưa).

#### B. Phân chia người dùng và chức năng
1. **Người dùng thông thường**
   - Chỉ có quyền truy xuất và chỉnh sửa thông tin cá nhân (tên, mật khẩu, kiểm tra tên đã được sử dụng chưa).
   - Sau khi điều chỉnh, hệ thống gửi OTP kèm thông báo những nội dung thay đổi
   - Nhập mã OTP hợp lệ, tiến hành thay đổi.

2. **Người dùng quản lý**
   - Có quyền theo dõi danh sách nhóm.
   - Tạo tài khoản mới.
   - Điều chỉnh thông tin tài khoản khi có yêu cầu, kèm theo xác thực OTP gửi đến chủ tài khoản.
   - Không được thay đổi tên tài khoản đăng nhập.

#### C. Quản lý hoạt động ví
- Mỗi người dùng có một ví điện tử (wallet) với điểm số và lịch sử giao dịch.
- Ví có **mã định danh duy nhất**.
- Ví tổng là nguồn duy nhất tạo ra tổng số điểm trong hệ thống.
- **Quy trình giao dịch giữa các ví:**
  1. Xác định ví nguồn (A) (Nếu tồn tại thì tiếp tục).
  2. Xác định ví đích (B) (Nếu tồn tại thì tiếp tục).
  3. Kiểm tra số dư ví A, nếu đủ thực hiện giao dịch:
     - Giảm số dư ví A.
     - Tăng số dư ví B.
  4. Nếu có lỗi, hệ thống **hủy giao dịch và khôi phục số dư ban đầu** của 2 ví.
  