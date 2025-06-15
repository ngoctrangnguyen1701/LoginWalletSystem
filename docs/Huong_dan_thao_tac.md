### Thao tác chính trong chương trình
**🔹 Màn hình đăng nhập**<br>
**1. Đăng nhập**<br>
_Nhập `Ten dang nhap`, `Mat khau`-> Đăng nhập thành công -> Chuyển sang `Menu dành cho Admin`(nếu là admin) hoặc `Menu cho người dùng thông thường`(nếu không phải là admin)

**2. Đăng ký**<br>
_Nhập `Ten dang nhap`, `Ho va ten`, `Email`, `Mat khau` -> Đăng ký thành công -> Quay trở về `Màn hình đăng nhập`

**3. Thoát chương trình**<br>

---

**🔹 Menu dành cho Admin**<br>
**1. Đọc danh sách người dùng**<br>
_Hiển thị toàn bộ danh sách người dùng đang có trong hệ thống -> Nhập `y` để quay trở về menu

**2. Thêm user**<br>
_Nhập `Ten dang nhap`, `Ho va ten`, `Email`, mật khẩu sẽ tự sinh với định dạng độ dài tối thiểu 7 ký tự bao gồm chứ hoa, chữ thường, số và ký tự đặc biệt 
_Thêm người dùng mới thành công, nhập `y` để quay trở về menu

**3. Thay đổi thông tin user**<br>
_Nhập `y` để hiển thị danh sách người dùng (nhập `n` để từ chối)
_Nhập ID người dùng muốn thay đổi
_Chọn thông tin muốn thay đổi
_Nhập thông tin mới
_Thay đổi thông tin thành công -> Nhập `y` để quay trở về menu

**4. Đọc danh sách tất cả các ví**<br>
_Hiển thị toàn bộ danh sách ví hiện có trong hệ thống -> Nhập `y` để quay trở về menu

**5. Ví tổng**<br>
_Chuyển sang `Menu thao tác ví tổng`

**6. Sao lưu và khôi phục dữ liệu**<br>
_Chuyển sang `Menu sao lưu và khôi phục dữ liệu`

**7. Đăng xuất**<br>
_Chuyển sang `Màn hình đăng nhập`

---
**🔹 Menu thao tác ví tổng**<br>
**1. Nạp**<br>
_Nhập số điểm cần nạp (số điểm nạp phải lớn hơn 0)
_Nhập `y` để xác nhận (nhập `n` để từ chối)
_Xác thực OTP (mã OTP sẽ được đến email đăng ký)
_Tạo giao dịch thành công -> Nhập `y` để quay trở về menu

**2. Rút**<br>
_Nhập số điểm cần rút (số điểm rút phải lớn hơn 0 và nhỏ hơn số điểm hiện có của ví tổng)
_Nhập `y` để xác nhận (nhập `n` để từ chối)
_Xác thực OTP (mã OTP sẽ được đến email đăng ký)
_Tạo giao dịch thành công -> Nhập `y` để quay trở về menu

**3. Xem số dư**<br>
_Hiển thị số dư hiện tại trong ví tổng -> Nhập `y` để quay trở về menu

**4. Lịch sử giao dịch**<br>
_Hiển thị lịch sử giao dịch của ví tổng -> Nhập `y` để quay trở về menu

**5. Quay về menu trước**<br>
_Chuyển sang `Menu dành cho Admin`

---

**🔹 Menu sao lưu và khôi phục dữ liệu**<br>
**1. Sao lưu**<br>
_Chuyển sang `Menu sao lưu dữ liệu`

**2. Khôi phục**<br>
_Hiển thị các phiên bản sao lưu để khôi phục dữ liệu
_Nhập phiên bản sao lưu muốn khôi phục *(Cảnh báo: Khôi phục dữ liệu có thể làm mất dữ liệu hiện tại)*
_Nhập `y` để xác nhận (nhập `n` để từ chối)
_Khôi phục dữ liệu thành công -> Nhập `y` để quay trở về menu

**3. Quay về menu trước**<br>
_Chuyển sang `Menu dành cho Admin`

---

**🔹 Menu sao lưu dữ liệu**<br>
**1. Sao lưu ngay bây giờ**<br>
_Tạo 1 phiên bản sao lưu dữ liệu ngay tại thời điểm hiện tại *(bản sao lưu nằm ở ["Thư mục chương trình/backup/..."](../backup))*

**2. Sao lưu khi thoát chương trình**<br>
_Bật/tắt sao lưu khi đăng xuất tài khoản admin khỏi chương trình

**3. Quay về menu trước**<br>
_Chuyển sang `Menu sao lưu và khôi phục dữ liệu`

---

**🔹 Menu cho người dùng thông thường**<br>
**1. Thay đổi thông tin**<br>
_Chọn thông tin muốn thay đổi
_Nhập thông tin mới
_Xác thực OTP (mã OTP sẽ được đến email đăng ký)
_Thay đổi thông tin thành công -> Nhập `y` để quay trở về menu

**2. Thay đổi mật khẩu**<br>
_Nhập mật khẩu mới *(không được trùng với mật khẩu hiện tại và theo định dạng độ dài tối thiểu 7 ký tự bao gồm chứ hoa, chữ thường, số và ký tự đặc biệt)*
_Xác thực OTP (mã OTP sẽ được đến email đăng ký)
_Thay đổi thông tin thành công -> Quay trở về `Màn hình đăng nhập` để đăng nhập lại

**3. Ví của tôi**<br>
_Chuyển sang `Menu thao tác ví`(nếu đã có ví) hoặc `Menu tạo ví`(nếu chưa có ví)

**4. Đăng xuất**<br>
_Chuyển sang `Màn hình đăng nhập`

---

**🔹 Menu tạo ví** <br>
**1. Tạo ví**<br>
_Nhập `y` để tạo ví (nhập `n` để từ chối)

**2. Quay về menu trước**<br>
_Chuyển sang `Menu cho người dùng thông thường`

---

**🔹 Menu thao tác ví**<br>
**1. Nạp**<br>
_Nhập số điểm cần nạp (số điểm nạp phải lớn hơn 0 và nhỏ hơn số điểm hiện có của ví tổng)
_Nhập `y` để xác nhận (nhập `n` để từ chối)
_Xác thực OTP (mã OTP sẽ được đến email đăng ký)
_Tạo giao dịch thành công -> Nhập `y` để quay trở về menu

**2. Rút**<br>
_Nhập số điểm cần rút (số điểm rút phải lớn hơn 0 và nhỏ hơn số điểm hiện có của ví người dùng)
_Nhập `y` để xác nhận (nhập `n` để từ chối)
_Xác thực OTP (mã OTP sẽ được đến email đăng ký)
_Tạo giao dịch thành công -> Nhập `y` để quay trở về menu

**3. Chuyển khoản**<br>
_Nhập ID của ví cần chuyển (ví nhận điểm phải tồn tại)
_Nhập số điểm cần chuyển (số điểm chuyển phải lớn hơn 0 và nhỏ hơn số điểm hiện có của ví người dùng)
_Nhập `y` để xác nhận (nhập `n` để từ chối)
_Xác thực OTP (mã OTP sẽ được đến email đăng ký)
_Tạo giao dịch thành công -> Nhập `y` để quay trở về menu

**4. Xem số dư**<br>
_Hiển thị số dư hiện tại trong ví người dùng -> Nhập `y` để quay trở về menu

**5. Lịch sử giao dịch**<br>
_Hiển thị lịch sử giao dịch của ví người dùng -> Nhập `y` để quay trở về menu

**6. Quay về menu trước**<br>
_Chuyển sang `Menu cho người dùng thông thường`
