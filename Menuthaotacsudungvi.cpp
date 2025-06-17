void adminWalletUsageMenu() {
    int choice;
    do {
        system("cls");
        cout << "====== MENU THAO TAC SU DUNG VI TIEN ======\n";
        cout << "1. Nap\n";
        cout << "2. Rut\n";
        cout << "3. Chuyen khoan\n";
        cout << "4. Xem so du\n";
        cout << "5. Lich su giao dich\n";
        cout << "6. Quay ve menu truoc\n";
        cout << "==========================================\n";
        cout << "Nhap lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
            case 1:
                napTienChoUser();
                break;
            case 2:
                rutTienCuaUser();
                break;
            case 3:
                cout << "Admin khong co tinh nang nay.\n";
                system("pause");
                break;
            case 4:
                hienThiSoDuViTong();
                break;
            case 5:
                menuLichSuGiaoDichChoAdmin();
                break;
            case 6:
                return;
            default:
                cout << "Lua chon khong hop le! Vui long nhap lai.\n";
                Sleep(1500);
        }
    } while (true);
}
