#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

string basePath = "C:\\Users\\ADMIN\\Documents\\";

// Ham kiem tra thong tin dang nhap admin tu file
bool verifyAdminLogin(const string& nameInput, const string& passInput) {
    string line, adminName, adminPass;
    ifstream file(basePath + "Admin.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file Admin.txt!\n";
        return false;
    }

    while (getline(file, line)) {
        if (line.find("Ten Admin: ") == 0) {
            adminName = line.substr(11); // sau "Ten Admin: "
        } else if (line.find("Ma Admin: ") == 0) {
            adminPass = line.substr(10); // sau "Ma Admin: "
        }
    }

    return (nameInput == adminName && passInput == adminPass);
}

// Hien thi Menu Admin (don gian)
void showAdminMenu() {
    cout << "\n===== ÐANG NHAP THANH CONG =====\n";
    cout << ">> Chao mung Admin den voi he thong!\n";
    // Goi menu that su
    adminMenu(); // hoac co the thay the bang noi dung thuc te
}

// Ham dang nhap chinh
void loginAccount() {
    string username;
    cout << "\n====== ÐANG NHAP TAI KHOAN ======\n";
    cout << "Nhap Username: ";
    cin >> username;

    if (username == "Admin") {
        string adminName, adminPass;
        cout << "Ten Admin: ";
        cin.ignore(); // xoa newline tu buffer
        getline(cin, adminName);

        cout << "Ma Admin: ";
        getline(cin, adminPass);

        if (verifyAdminLogin(adminName, adminPass)) {
            showAdminMenu();
        } else {
            cout << "Sai ten hoac ma Admin. Chuong trinh se thoat.\n";
            Sleep(2000);
            exit(0);
        }
    } else {
        // Tam thoi chua xu ly nguoi dung thong thuong
        cout << "Chuc nang dang nhap nguoi dung dang duoc phat trien.\n";
    }
}
