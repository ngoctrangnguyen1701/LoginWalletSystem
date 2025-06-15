### Dữ liệu cho sẵn trong chương trình

**1. Dữ liệu người dùng**
| ID | Tên đăng nhập  | Mật khẩu       | Tên hiển thị        | Email                       | Là admin? | Mật khẩu tự sinh? |
|----|----------------|----------------|-------------------- |-----------------------------|-----------|-------------------|
| 1  | admin          | 123            | Administrator       | admin@example.com           | Có        | Không             |
| 2  | binhduong      | binhduong123   | Binh Duong          | binhduong@example.com       | Không     | Không             |
| 3  | vungtau        | vungtau123     | Vung Tau            | vungtau@example.com         | Không     | Không             |
| 4  | trian          | trian123       | Tri An              | trian@example.com           | Không     | Không             |
| 5  | vinhhy         | vinhhy123      | Vinh Hy             | vinhhy@example.com          | Không     | Không             |
| 6  | nuicam         | nuicam123      | Thien Cam Son       | nuicam@example.com          | Không     | Không             |

---

**2. Dữ liệu ví**
| ID  | Chủ sở hữu  | Số dư    | Ví tổng? |
|-----|-------------|----------|----------|
| 1   | admin       |   97.600 | Có       |
| 2   | binhduong   |    1.000 | Không    |
| 3   | vungtau     |      800 | Không    |
| 4   | trian       |      500 | Không    |
| 5   | vinhhy      |      100 | Không    |

---

**3. Dữ liệu lịch sử giao dịch**
| ID  | ID ví phát sinh | Mã tham chiếu | ID ví nguồn | ID ví đích | Loại giao dịch | Số điểm   | Thời gian           | Trạng thái  | Số dư    |
|-----|-----------------|---------------|-------------|------------|----------------|-----------|---------------------|-------------|----------|
| 1   | 1               |               |             |            | Nạp điểm       |   100.000 | 2025/01/01 20:12:00 | Thành công  |  100.000 |
| 2   | 2               | REQ2_3        |             |            | Nạp điểm       |     1.200 | 2025/01/02 20:12:00 | Thành công  |    1.200 |
| 3   | 1               | REQ2_3        | 1           | 2          | Chuyển điểm    |     1.200 | 2025/01/02 20:12:00 | Thành công  |   98.800 |
| 4   | 3               | REQ4_5        |             |            | Nạp điểm       |       700 | 2025/01/03 20:12:00 | Thành công  |      700 |
| 5   | 1               | REQ4_5        | 1           | 3          | Chuyển điểm    |       700 | 2025/01/03 20:12:00 | Thành công  |   98.100 |
| 6   | 4               | REQ6_7        |             |            | Nạp điểm       |       500 | 2025/01/04 20:12:00 | Thành công  |      500 |
| 7   | 1               | REQ6_7        | 1           | 4          | Chuyển điểm    |       500 | 2025/01/04 20:12:00 | Thành công  |   97.600 |
| 8   | 5               | REQ8_9        |             |            | Nạp điểm       |       100 | 2025/01/05 20:12:00 | Thành công  |      100 |
| 9   | 1               | REQ8_9        | 1           | 5          | Chuyển điểm    |       100 | 2025/01/05 20:12:00 | Thành công  |   97.500 |
| 10  | 2               | REQ10_11      | 2           | 3          | Chuyển điểm    |       100 | 2025/01/06 12:01:00 | Thành công  |    1.100 |
| 11  | 3               | REQ10_11      | 2           | 3          | Nhận điểm      |       100 | 2025/01/06 12:01:00 | Thành công  |      800 |
| 12  | 2               | REQ12_13      |             |            | Rút điểm       |       100 | 2025/01/07 13:13:00 | Thành công  |    1.000 |
| 13  | 1               | REQ12_13      | 2           | 1          | Nhận điểm      |       100 | 2025/01/07 13:13:00 | Thành công  |   97.600 |
