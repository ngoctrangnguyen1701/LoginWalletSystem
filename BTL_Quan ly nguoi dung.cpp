#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <regex>
#include <windows.h>
#include <vector>
#include <filesystem>
#include <windows.h>

using namespace std;

// Hàm l?y th?i gian th?c
string getCurrentTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[30];
    sprintf(buffer, "%02d:%02d:%02d _%02d/%02d/%04d",
            ltm->tm_hour, ltm->tm_min, ltm->tm_sec,
            ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
    return string(buffer);
}

// T?o file Admin.txt
void createAdminFile() {
    string path = "C:\\Users\\ADMIN\\Documents\\Admin.txt";
    ofstream file(path);
    if (file.is_open()) {
        file << "Tên Admin: Admin12345678\n";
        file << "Mã Admin: 12345678\n";
        file.close();
        cout << "Ðã t?o file Admin.txt t?i: " << path << endl;
    } else {
        cout << "Không th? t?o file Admin.txt!" << endl;
    }
}

// Menu l?ch s? giao d?ch cho Admin
void adminTransactionMenu() {
    int choice;
    do {
        cout << "\n----- MENU L?CH S? GIAO D?CH CHO ADMIN -----\n";
        cout << "1. Danh sách giao d?ch ví t?ng\n";
        cout << "2. Giao d?ch t?t c? ví\n";
        cout << "3. L?c theo Wallet ID\n";
        cout << "4. L?c theo Username\n";
        cout << "5. L?c theo th?i gian\n";
        cout << "6. Tìm theo Reference ID\n";
        cout << "7. Quay v?\n";
        cout << "Ch?n: "; cin >> choice;
        // T?m th?i b? qua x? lý, ch? hi?n th?
    } while (choice != 7);
}

// Menu Admin
void adminMenu() {
    int choice;
    do {
        cout << "\n======== MENU DÀNH CHO ADMIN ========\n";
        cout << "1. Ð?c danh sách ngu?i dùng\n";
        cout << "2. Tìm ki?m ngu?i dùng\n";
        cout << "3. Thêm user\n";
        cout << "4. Thay d?i thông tin user\n";
        cout << "5. Xóa user\n";
        cout << "6. Ð?c danh sách ví\n";
        cout << "7. Xem ví t?ng\n";
        cout << "8. Sao luu & khôi ph?c d? li?u\n";
        cout << "9. Ðang xu?t\n";
        cout << "Ch?n: "; cin >> choice;

        if (choice == 9) break;
        if (choice == 6) adminTransactionMenu();

    } while (true);
}

// Menu user
void userMenu() {
    int choice;
    do {
        cout << "\n======= MENU NGU?I DÙNG =======\n";
        cout << "1. Thay d?i thông tin\n";
        cout << "2. Thay d?i m?t kh?u\n";
        cout << "3. Ví c?a tôi\n";
        cout << "4. Ðang xu?t\n";
        cout << "Ch?n: "; cin >> choice;
    } while (choice != 4);
}

// Hi?n th? th?i gian th?c
void displayCurrentTime() {
    while (true) {
        system("cls");
        cout << "Th?i gian hi?n t?i: " << getCurrentTime() << endl;
        Sleep(1000);
    }
}

// Menu chính
void mainMenu() {
    int choice;
    do {
        cout << "\n==== CHUONG TRÌNH QU?N LÝ ÐI?M THU?NG ====\n";
        cout << "1. Ðang nh?p\n";
        cout << "2. Ðang ký\n";
        cout << "3. Thoát\n";
        cout << "Ch?n: ";
        cin >> choice;

        switch (choice) {
        case 1:
            // G?i hàm dang nh?p
            break;
        case 2:
            // G?i hàm dang ký
            break;
        case 3:
            cout << "Ðã thoát chuong trình.\n";
            break;
        default:
            cout << "L?a ch?n không h?p l?. Th? l?i.\n";
        }

    } while (choice != 3);
}

int main() {
    createAdminFile();        // T?o file admin
    mainMenu();               // Hi?n th? menu chính
    return 0;
}

// Ti?p t?c chuong trinh dang nhap Phan 2
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <filesystem>
#include <ctime>
#include <windows.h>

using namespace std;
namespace fs = std::filesystem;

string basePath = "C:\\Users\\ADMIN\\Documents\\";

// Tr? v? th?i gian hi?n t?i du?i d?ng chu?i
string getCurrentTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[30];
    sprintf(buffer, "%02d:%02d:%02d _%02d/%02d/%04d",
            ltm->tm_hour, ltm->tm_min, ltm->tm_sec,
            ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
    return string(buffer);
}

// Ki?m tra username h?p l?
bool isValidUsername(const string& username) {
    return regex_match(username, regex("^[A-Za-z0-9_]+$"));
}

// Ki?m tra password h?p l?
bool isValidPassword(const string& password) {
    bool hasUpper = false, hasLower = false, hasDigit = false;
    for (char c : password) {
        if (isupper(c)) hasUpper = true;
        else if (islower(c)) hasLower = true;
        else if (isdigit(c)) hasDigit = true;
    }
    return hasUpper && hasLower && hasDigit;
}

// Ki?m tra username dã t?n t?i chua (gi? s? luu ? "users.txt")
bool isUsernameTaken(const string& username) {
    ifstream file(basePath + "users.txt");
    string line;
    while (getline(file, line)) {
        if (line == username) return true;
    }
    return false;
}

// Ghi username vào danh sách
void saveUsername(const string& username) {
    ofstream file(basePath + "users.txt", ios::app);
    file << username << endl;
}

// T?o file wallet_n.txt và transaction_n.txt
void createWalletFiles(const string& username, int index) {
    string walletFile = basePath + "wallet_" + to_string(index) + ".txt";
    string transactionFile = basePath + "transaction_" + to_string(index) + ".txt";
    string now = getCurrentTime();

    ofstream wf(walletFile);
    wf << "Th?i gian: " << now << "\n";
    wf << "Tên ngu?i dùng: " << username << "\n";
    wf << "S? du tài kho?n: 50000 VNÐ\n";
    wf << "Ði?m ví t?ng: 10000 di?m\n";
    wf << "Ði?m ví user: 5 di?m\n";
    wf.close();

    ofstream tf(transactionFile);
    tf << "Th?i gian: " << now << "\n";
    tf << "Tên ngu?i dùng: " << username << "\n";
    tf << "Giao d?ch: [Tr?ng ban d?u]\n";
    tf.close();
}

// Ð?m s? file wallet_n.txt hi?n có
int getNextIndex() {
    int maxIndex = 0;
    for (const auto& entry : fs::directory_iterator(basePath)) {
        string filename = entry.path().filename().string();
        if (filename.find("wallet_") == 0) {
            int idx = stoi(filename.substr(7, filename.find(".txt") - 7));
            if (idx > maxIndex) maxIndex = idx;
        }
    }
    return maxIndex + 1;
}

// Giao di?n dang ký tài kho?n
void registerAccount() {
    string username, password;

    // Nh?p username h?p l?
    do {
        cout << "Ðang ký Username: ";
        cin >> username;

        if (!isValidUsername(username)) {
            cout << "Username ch? g?m ch? Latin, s? và d?u g?ch du?i (_). Vui lòng nh?p l?i.\n";
            continue;
        }
        if (isUsernameTaken(username)) {
            cout << "Tên tài kho?n dã du?c s? d?ng. Vui lòng ch?n tên khác.\n";
            continue;
        }
        break;
    } while (true);

    // Nh?p password h?p l?
    do {
        cout << "Ch?n Password: ";
        cin >> password;

        if (!isValidPassword(password)) {
            cout << "Password ph?i có ít nh?t 1 ch? in hoa, 1 ch? thu?ng và 1 ch? s?. Vui lòng nh?p l?i.\n";
            continue;
        }
        break;
    } while (true);

    // Luu tài kho?n và t?o file
    saveUsername(username);
    int index = getNextIndex();
    createWalletFiles(username, index);

    cout << "Ðang ký thành công tài kho?n qu?n lý di?m thu?ng!\n";
}
? Hu?ng d?n tích h?p:
Trong hàm mainMenu() b?n g?i nhu sau:

cpp
Sao chép
Ch?nh s?a
case 2:
    registerAccount();
    break;
    

