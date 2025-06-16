#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <regex>
#include <windows.h>

using namespace std;

// Ham lay thoi gian thuc
string getCurrentTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[30];
    sprintf(buffer, "%02d:%02d:%02d _%02d/%02d/%04d",
            ltm->tm_hour, ltm->tm_min, ltm->tm_sec,
            ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
    return string(buffer);
}

// Tao file Admin.txt
void createAdminFile() {
    string path = "C:\\Users\\ADMIN\\Documents\\Admin.txt";
    ofstream file(path);
    if (file.is_open()) {
        file << "Tên Admin: Admin12345678\n";
        file << "Mã Admin: 12345678\n";
        file.close();
        cout << "Ða tao file Admin.txt t?i: " << path << endl;
    } else {
        cout << "Khong the tao file Admin.txt!" << endl;
    }
}

// Menu lich su giao dich cho Admin
void adminTransactionMenu() {
    int choice;
    do {
        cout << "\n----- MENU LiCH Su GIAO DiCH CHO ADMIN -----\n";
        cout << "1. Danh sach giao dich vi tong\n";
        cout << "2. Giao dich tat ca vi\n";
        cout << "3. Loc theo Wallet ID\n";
        cout << "4. Loc theo Username\n";
        cout << "5. Loc theo thoi gian\n";
        cout << "6. Tim theo Reference ID\n";
        cout << "7. Quay ve\n";
        cout << "Ch?n: "; cin >> choice;
        // Tam thoi bo qua xu ly, chi hien thi
    } while (choice != 7);
}

// Menu Admin
void adminMenu() {
    int choice;
    do {
        cout << "\n======== MENU DANH CHO ADMIN ========\n";
        cout << "1. Ðoc danh sach nguoi dung\n";
        cout << "2. Tim kiem nguoi dung\n";
        cout << "3. Thêm user\n";
        cout << "4. Thay doi thong tin user\n";
        cout << "5. Xoa user\n";
        cout << "6. Ðoc danh sach vi\n";
        cout << "7. Xem vi tong\n";
        cout << "8. Sao luu & khoi phuc du lieu\n";
        cout << "9. Ðang xuat\n";
        cout << "Chon: "; cin >> choice;

        if (choice == 9) break;
        if (choice == 6) adminTransactionMenu();

    } while (true);
}

// Menu user
void userMenu() {
    int choice;
    do {
        cout << "\n======= MENU NGUOI DUNG =======\n";
        cout << "1. Thay doi thong tin\n";
        cout << "2. Thay doi mat khau\n";
        cout << "3. Vi cua toi\n";
        cout << "4. Ðang xuat\n";
        cout << "Chon: "; cin >> choice;
    } while (choice != 4);
}

// Hien thi thoi gian thuc
void displayCurrentTime() {
    while (true) {
        system("cls");
        cout << "Thoi gian hien tai: " << getCurrentTime() << endl;
        Sleep(1000);
    }
}

// Menu chinh
void mainMenu() {
    int choice;
    do {
        cout << "\n==== CHUONG TRINH QUAN LY ÐIEM THUONG ====\n";
        cout << "1. Ðang nhap\n";
        cout << "2. Ðang ky\n";
        cout << "3. Thoat\n";
        cout << "Chon: ";
        cin >> choice;

        switch (choice) {
        case 1:
            // Goi ham dang nhap
            break;
        case 2:
            // Goi ham dang ky
            break;
        case 3:
            cout << "Ða thoat chuong trinh.\n";
            break;
        default:
            cout << "Lua chon khong hop le. Thu lai.\n";
        }

    } while (choice != 3);
}

int main() {
    createAdminFile();        // Tao file admin
    mainMenu();               // Hien thi menu chinh
    return 0;
}
