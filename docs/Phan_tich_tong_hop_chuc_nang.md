#### A. Chức năng quản lý tài khoản người dùng
1. **Tạo mới tài khoản khi đăng ký**
  - Thiết kế lớp (class) User để lưu trữ thông tin người dùng (tên đăng nhập, mật khẩu, tên hiển thị...)
  - Xây dựng giao diện nhập liệu thông tin đăng ký
  - Xác thực dữ liệu người dùng nhập vào
  - Kiểm tra trùng lặp tên tài khoản
  - Xử lý trường hợp nhân viên quản lý tạo tài khoản hộ người dùng
  
2. **Lưu trữ dữ liệu**
  - Cài đặt hàm băm (hash function) cho mật khẩu khi lưu tài khoản người dùng
  - Phương thức lưu trữ theo tập tin chung kiểu danh sách
  - Thiết kế cấu trúc dữ liệu tập tin theo danh sách chứa các phẩn tử là thông tin tài khoản người dùng
  - Xây dựng hệ thống sao lưu và phục hồi dữ liệu (Chưa rõ chức năng sao lưu sẽ theo hình thức nào? dữ liệu nào được sao lưu?)

3. **Quản lý đăng nhập**
3.1. **Sinh mật khẩu tự động**
Công việc cần làm
  - Phát triển thuật toán sinh mật khẩu tự động ngẫu nhiên
  - Lưu và gửi mật khẩu tự động cho người dùng
  - Đánh dấu mật khẩu là "tự sinh" để yêu cầu đổi lần đầu

3.2. **Thay đổi mật khẩu**
  - Xây dựng giao diện đổi mật khẩu
  - Xác thực mật khẩu cũ
  - Cập nhật và lưu mật khẩu mới đã được băm
  - Xử lý trường hợp mật khẩu tự sinh, kiểm tra có phải là tự sinh và yêu cầu người dùng thay đổi ngay mật khẩu mới trong lần đăng nhập đầu tiên của mình.

3.3. **OTP - One Time Password**
  - Thiết kế tính năng sinh OTP và gửi OTP đến người dùng
  - Xác thực OTP nhập vào
  - Tích hợp OTP vào quy trình xác thực

3.4. **Đăng nhập**
  - Xây dựng giao diện đăng nhập
  - Tìm kiếm trong dữ liệu người dùng thông tin đăng nhập có tồn tại
  - Nếu tồn tại dữ liệu, cho đăng nhập vào hệ thống
  - Xử lý trường hợp đăng nhập lần đầu với mật khẩu tự sinh(kiểm tra nếu là mật khẩu tự sinh phải yêu cầu đổi người dùng mật khẩu)

#### B. Phân quyền người dùng
1. **Người dùng thông thường**
  - Xây dựng giao diện xem/chỉnh sửa thông tin cá nhân, chỉ cho phép chỉnh sửa những trường dữ liệu được chỉnh sửa(như tên hiển thị, mật khẩu...)
  - Tích hợp OTP cho xác nhận thay đổi thông tin
  - Không thay đổi tên tài khoản đăng nhập

2. **Người dùng quản lý**
  - Phát triển giao diện quản lý danh sách người dùng
  - Xây dựng chức năng tạo tài khoản mới
  - Xây dựng chức năng điều chỉnh thông tin người dùng
  - Tích hợp OTP cho xác nhận thay đổi thông tin người dùng
  - Không thay đổi tên tài khoản đăng nhập

#### C. Quản lý ví điểm thưởng
1. **Tạo và quản lý ví**
  - Thiết kế lớp Wallet để lưu trữ thông tin ví
  - Tạo mã định danh duy nhất cho mỗi ví
  - Xây dựng giao diện quản lý ví

2. **Giao dịch chuyển điểm**
  - Xây dựng quy trình chuyển điểm giữa các ví
  - Xử lý hủy giao dịch các trường hợp ngoại lệ (không tìm thấy ví chủ, không tìm thấy ví đích, ví chủ không đủ số dư), trả lại số dư ban đầu
  - Tích hợp OTP xác nhận giao dịch
  - Lưu trữ lịch sử giao dịch

3. **Báo cáo giao dịch**
 - Thiết kế lớp Transaction để lưu trữ thông tin giao dịch
 - Xây dựng giao diện xem số dư, lịch sử giao dịch, trạng thái thực hiện giao dịch
