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

// Tra ve thoi gian hien tai duoi dang chuoi
string getCurrentTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[30];
    sprintf(buffer, "%02d:%02d:%02d _%02d/%02d/%04d",
            ltm->tm_hour, ltm->tm_min, ltm->tm_sec,
            ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
    return string(buffer);
}

// Kiem tra username hop le
bool isValidUsername(const string& username) {
    return regex_match(username, regex("^[A-Za-z0-9_]+$"));
}

// Kiem tra password hop le
bool isValidPassword(const string& password) {
    bool hasUpper = false, hasLower = false, hasDigit = false;
    for (char c : password) {
        if (isupper(c)) hasUpper = true;
        else if (islower(c)) hasLower = true;
        else if (isdigit(c)) hasDigit = true;
    }
    return hasUpper && hasLower && hasDigit;
}

// Kiem tra username da ton tai chua (gia su luu o "users.txt")
bool isUsernameTaken(const string& username) {
    ifstream file(basePath + "users.txt");
    string line;
    while (getline(file, line)) {
        if (line == username) return true;
    }
    return false;
}

// Ghi username vao danh sach
void saveUsername(const string& username) {
    ofstream file(basePath + "users.txt", ios::app);
    file << username << endl;
}

// Tao file wallet_n.txt và transaction_n.txt
void createWalletFiles(const string& username, int index) {
    string walletFile = basePath + "wallet_" + to_string(index) + ".txt";
    string transactionFile = basePath + "transaction_" + to_string(index) + ".txt";
    string now = getCurrentTime();

    ofstream wf(walletFile);
    wf << "Thoi gian: " << now << "\n";
    wf << "Tên nguoi dung: " << username << "\n";
    wf << "So du tai khoan: 50000 VNÐ\n";
    wf << "Ðiem vi tong: 10000 diem\n";
    wf << "Ðiem vi user: 5 diem\n";
    wf.close();

    ofstream tf(transactionFile);
    tf << "Thoi gian: " << now << "\n";
    tf << "Ten nguoi dung: " << username << "\n";
    tf << "Giao dich: [Trong ban dau]\n";
    tf.close();
}

// Ðem so file wallet_n.txt hien co
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

// Giao dien dang ky tai khoan
void registerAccount() {
    string username, password;

    // Nhap username hop le
    do {
        cout << "Ðang ky Username: ";
        cin >> username;

        if (!isValidUsername(username)) {
            cout << "Username chi gom chu Latin, so và dau gach duoi (_). Vui lòng nhap lai.\n";
            continue;
        }
        if (isUsernameTaken(username)) {
            cout << "Ten tai khoan da duoc su dung. Vui long chon ten khac.\n";
            continue;
        }
        break;
    } while (true);

    // Nhap password hop le
    do {
        cout << "Chon Password: ";
        cin >> password;

        if (!isValidPassword(password)) {
            cout << "Password phai co it nhat 1 chu in hoa, 1 chu thuong và 1 chu so. Vui long nhap lai.\n";
            continue;
        }
        break;
    } while (true);

    // Luu tai khoan va tao file
    saveUsername(username);
    int index = getNextIndex();
    createWalletFiles(username, index);

    cout << "Ðang ky thanh cong tai khoan quan ly diem thuong!\n";
}
