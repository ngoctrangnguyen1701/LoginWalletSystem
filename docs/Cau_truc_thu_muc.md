```bash
/LoginWalletSystem (thư mục mã nguồn)
|
|-- /src                              # Mã nguồn chính
|   |-- /common
|   |-- /libraries
|   |
|   |-- /models                       # Các lớp dữ liệu
|   |   |-- User.h                    # Khai báo lớp User
|   |   |-- User.cpp                  # Cài đặt lớp User
|   |   |-- Wallet.h                  # Khai báo lớp Wallet
|   |   |-- Wallet.cpp                # Cài đặt lớp Wallet
|   |   |-- UserWallet.h              # Khai báo lớp UserWallet
|   |   |-- UserWallet.cpp            # Cài đặt lớp UserWallet
|   |   |-- MasterWallet.h            # Khai báo lớp MasterWallet
|   |   |-- MasterWallet.cpp          # Cài đặt lớp MasterWallet
|   |   |-- Transaction.h             # Khai báo lớp Transaction
|   |   |-- Transaction.cpp           # Cài đặt lớp Transaction
|   |
|   |-- /managers                     # Quản lý nghiệp vụ
|   |   |-- UserManager.h             # Quản lý người dùng
|   |   |-- UserManager.cpp
|   |   |-- WalletManager.h           # Quản lý ví
|   |   |-- WalletManager.cpp
|   |   |-- TransactionManager.h      # Quản lý lịch sử giao dịch
|   |   |-- TransactionManager.cpp
|   |   |-- OTPManager.h              # Quản lý mã OTP
|   |   |-- OTPManager.cpp
|   |   |-- BackupMananger.h          # Quản lý sao lưu và khôi phục
|   |   |-- BackupManager.cpp
|   |
|   |-- /utils                        # Các hàm tiện ích
|   |   |-- ConsoleUtils.h            # Hàm in
|   |   |-- ConsoleUtils.cpp
|   |   |-- HashUtils.h               # Hàm băm mật khẩu
|   |   |-- HashUtils.cpp
|   |   |-- FileUtils.h               # Thao tác file
|   |   |-- FileUtils.cpp
|   |   |-- Utils.h                   # Các hàm tiện ích khác
|   |
|   |-- /views                        # Giao diện người dùng
|   |   |-- Menu.h                    # Lớp menu cơ bản
|   |   |-- Menu.cpp
|   |   |-- LoginMenu.h               # Màn hình đăng nhập
|   |   |-- LoginMenu.cpp
|   |   |-- UserMenu.h                # Menu người dùng thông thường
|   |   |-- UserMenu.cpp
|   |   |-- AdminMenu.h               # Menu người dùng quản trị
|   |   |-- AdminMenu.cpp
|   |   |-- WalletMenu.h              # Menu thao tác ví
|   |   |-- WalletMenu.cpp
|   |   |-- CreateWalletMenu.h        # Menu tạo ví mới
|   |   |-- CreateWalletMenu.cpp
|   |   |-- UserWalletMenu.h          # Menu ví người dùng thông thường
|   |   |-- UserWalletMenu.cpp
|   |   |-- MasterWalletMenu.h        # Menu ví tổng
|   |   |-- MasterWalletMenu.cpp
|   |   |-- BackupRestoreMenu.h       # Menu sao lưu và khôi phục
|   |   |-- BackupRestoreMenu.cpp
|   |   |-- BackupMenu.h              # Menu sao lưu
|   |   |-- BackupMenu.cpp
|   |
|   |-- Application.h                 # Trình điều khiển ứng dụng chính
|   |-- Application.cpp
|   |-- main.cpp                      # Điểm khởi đầu chương trình
|
|-- /.vscode                          # Cấu hình cho Visual Studio Code
|   |-- launch.json
|   |-- tasks.json
|
|-- /docs                             # Tài liệu
|   |-- Cau_truc_thu_muc
|   |-- Huong_dan_thao_tac
|   |-- Phan_cong_cong_viec
|   |-- Phan_tich_tong_hop_chuc_nang
|   |-- Yeu_cau_chuc_nang
|
|-- /data                             # Lưu trữ dữ liệu
|   |-- userData.csv                  # File dữ liệu người dùng
|   |-- nextUserId.txt                # File ID kế tiếp cho người dùng
|   |-- walletData.csv                # File dữ liệu ví
|   |-- nextWalletId.txt              # File ID kế tiếp cho ví
|   |-- transactionData.csv           # File lịch sử giao dịch
|   |-- nextTransactionId.txt         # File ID kế tiếp cho giao dịch
|
|-- /backup                           # Thư mục sao lưu
|   |-- /20250101_12:00:00
|   |   |-- backup_userData.csv
|   |   |-- backup_nextUserId.txt
|   |   |-- backup_walletData.csv
|   |   |-- backup_nextWalletId.txt
|   |   |-- backup_transactionData.csv
|   |   |-- backup_nextTransactionId.txt
|
|-- README.md                         # Hướng dẫn sử dụng
```
