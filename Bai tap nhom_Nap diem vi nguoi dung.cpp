#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

// ------------------- KHAI BÁO HÀM GI? L?P (DUMMY) -------------------
// Nh?ng hàm này c?n b?n tri?n khai th?t, t?m th?i mình cho giá tr? gi? d?nh d? ch?y du?c
int getWalletBalance(const std::string& walletID) {
    if (walletID == "WALLET_TONG") return 10000; // ví t?ng có 10000 di?m
    return 100; // ví user có 100 di?m
}

void updateWalletBalance(const std::string& walletID, int newBalance) {
    std::cout << "[LOG] Cap nhat vi " << walletID << " voi so du moi: " << newBalance << "\n";
}

bool verifyOTP(const std::string& username) {
    std::string otp;
    std::cout << "Nhap ma OTP cho " << username << ": ";
    std::cin >> otp;
    return otp == "123456"; // OTP gi? d?nh là 123456
}

void writeTransaction(const std::string& walletID, const std::string& type,
                      int amount, const std::string& relatedWalletID = "") {
    std::ofstream file("transactions.txt", std::ios::app);
    if (!file) {
        std::cout << "Không the mo file giao dich.\n";
        return;
    }

    time_t now = time(0);
    std::string timestamp = ctime(&now);
    if (!timestamp.empty() && timestamp.back() == '\n') {
        timestamp = timestamp.substr(0, timestamp.size() - 1);
    }

    file << walletID << "|" << type << "|" << amount << "|"
         << relatedWalletID << "|" << timestamp << "\n";
    file.close();
}
// -------------------------------------------------------------------

const std::string MASTER_WALLET_ID = "WALLET_TONG";

struct UserAccount {
    std::string username;
    std::string role;
    std::string walletID;
};

void depositToUserWallet(UserAccount& user) {
    int amount;
    std::cout << "Nhap so diem can nap: ";
    std::cin >> amount;

    if (amount <= 0) {
        std::cout << "So diem phai lon hon 0.\n";
        return;
    }

    int masterBalance = getWalletBalance(MASTER_WALLET_ID);
    if (amount > masterBalance) {
        std::cout << "Vi tong khong du diem de nap. So du hien tai: " << masterBalance << "\n";
        return;
    }

    std::cout << "Xac thuc OTP...\n";
    if (!verifyOTP(user.username)) {
        std::cout << "OTP khong hop le. Giao dich bi huy.\n";
        return;
    }

    int userBalance = getWalletBalance(user.walletID);
    updateWalletBalance(user.walletID, userBalance + amount);
    updateWalletBalance(MASTER_WALLET_ID, masterBalance - amount);

    writeTransaction(user.walletID, "deposit", amount, MASTER_WALLET_ID);
    writeTransaction(MASTER_WALLET_ID, "transfer", amount, user.walletID);

    std::cout << "Nap diem thanh cong!\n";
}

int main() {
    UserAccount user;
    user.username = "user01";
    user.role = "user";
    user.walletID = "WALLET_USER01";

    depositToUserWallet(user);
    return 0;
}

