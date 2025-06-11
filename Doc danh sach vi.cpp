#include <iostream>
#include <vector>

using namespace std;

class User {
    private:
        int userId;
        string username;
        string password;
        string fullName;
        string email;
    public:
        void setUserId(int userId) {
            this->userId = userId;
        };
        void setUsername(string username) {
            this->username = username;
        };
        void setPassword(string password) {
            this->password = password;
        };
        void setFullName(string fullName) {
            this->fullName = fullName;
        };
        void setEmail(string email) {
            this->email = email;
        };
        int getUserId() {
            return this->userId;
        };
        string getUsername() {
            return this->username;
        };
        string getPassword() {
            return this->password;
        };
        string getFullName() {
            return this->fullName;
        };
        string getEmail() {
            return this->email;
        };
};

class Wallet {
    private:
        int walletId;
        int userId; // userId so huu vi
        int balance; // So du trong vi
        bool isMaster; //Co phai la vi tong hay khong
    public:
        void setWalletId(int walletId) {
            this->walletId = walletId;
        };
        void setUserId(int userId) {
            this->userId = userId;
        };
        void setBalance(int balance) {
            this->balance = balance;
        };
        void setIsMaster(bool isMaster) {
            this->isMaster = isMaster;
        };
        int getWalletId() {
            return this->walletId;
        };
        int getUserId() {
            return this->userId;
        };
        int getBalance() {
            return this->balance;
        };
        bool getIsMaster() {
            return this->isMaster;
        };
};

//Ham tao du lieu
void createUserList(vector<User> &userList) {    
    User user_1;
    user_1.setUserId(1);
    user_1.setUsername("user_1");
    user_1.setPassword("123");
    user_1.setFullName("Nguoi dung 1");
    user_1.setEmail("user_1@gmail.com");
    userList.push_back(user_1);

    User user_2;
    user_2.setUserId(2);
    user_2.setUsername("user_2");
    user_2.setPassword("123");
    user_2.setFullName("Nguoi dung 2");
    user_2.setEmail("user_2@gmail.com");
    userList.push_back(user_2);

    User user_3;
    user_3.setUserId(3);
    user_3.setUsername("user_3");
    user_3.setPassword("123");
    user_3.setFullName("Nguoi dung 3");
    user_3.setEmail("user_3@gmail.com");
    userList.push_back(user_3);
}

void createWalletList(vector<Wallet> &walletList) {    
    Wallet wallet_1;
    wallet_1.setWalletId(1);
    wallet_1.setUserId(1);
    wallet_1.setBalance(1000);
    wallet_1.setIsMaster(true); // Vi tong
    walletList.push_back(wallet_1);

    Wallet wallet_2;
    wallet_2.setWalletId(2);
    wallet_2.setUserId(2);
    wallet_2.setBalance(2000);
    wallet_2.setIsMaster(false);
    walletList.push_back(wallet_2);

    Wallet wallet_3;
    wallet_3.setWalletId(3);
    wallet_3.setUserId(3);
    wallet_3.setBalance(3000);
    wallet_3.setIsMaster(false);
    walletList.push_back(wallet_3);
}

//Tim kiem user theo userId tra ve vi tri cua user trong danh sach
int findUserById(vector<User> userList, int userId) {
    for(int i = 0; i < userList.size(); i++) {
        if(userList[i].getUserId() == userId) {
            return i;
        }
    }
    return -1; // Tra ve -1 neu khong tim thay
}

//Ham in danh sach
void printWalletList(vector<Wallet> walletList, vector<User> userList) {
    cout << "==== DANH SACH VI ====" << endl;
    cout << "walletId | username | balance | isMaster" << endl;
    for(int i = 0; i < walletList.size(); i++) {
        Wallet wallet = walletList[i];
        //Tim kiem userId de lay username hien thi
        int userId = wallet.getUserId(); // Lay userId tu wallet
        int index = findUserById(userList, userId);
        string username = "";
        if(index != -1) {
            // Neu tim thay user, lay username tu userList
            username = userList[index].getUsername();
        }
        else {
            // Gan la Unknown neu khong tim thay user
            username = "Unknown";
        }
        
        //Kiem tra xem wallet co la vi tong hay khong, neu laf
        // Neu isMaster la true, hien thi "true", nguoc lai hien thi "false"
        string isMaster = wallet.getIsMaster() == true ? "true" : "false";

        cout << wallet.getWalletId() << "        | ";
        cout << username << "   | ";
        cout << wallet.getBalance() << "    | ";
        cout << isMaster;
        cout << endl;
    }
}


// Ham xac thuc OTP, tra ve true neu xac thuc thanh cong, false neu khong thanh cong
bool verifyOTP(string email) {
    string otp = "123456"; // Gia su OTP la 123456
    cout << "Ma OTP la: " << otp << endl;
    cout << "OTP da duoc gui toi email cua ban: " << email << endl;
    cout << "Nhap OTP de xac thuc: ";
    string otpInput;
    getline(cin, otpInput);
    if(otpInput != otp) {        
        return false; // Xac thuc that bai
    }
    return true; // Xac thuc thanh cong
}

int main() {
    vector<User> userList;
    createUserList(userList);

    vector<Wallet> walletList;
    createWalletList(walletList);
    
    printWalletList(walletList, userList);

    return 0;
}
