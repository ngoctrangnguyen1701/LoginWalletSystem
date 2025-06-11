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

//Ham in danh sach
void printList(vector<User> userList) {
    for(int i = 0; i < userList.size(); i++) {
        User user = userList[i];
        cout << "--------" << endl;
        cout << "userId: " << user.getUserId() << endl;
        cout << "username: " << user.getUsername() << endl;
        cout << "password: " << user.getPassword() << endl;
        cout << "fullName: " << user.getFullName() << endl;
        cout << "email: " << user.getEmail() << endl;
    }
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

    int userIdInput;
    string fullNameInput;
    string emailInput;
    cout << "Nhap userId can thay doi thong tin: ";
    cin >> userIdInput;
    cin.ignore(); // Bo qua ki tu '\n' con lai trong bo dem
    cout << "Nhap fullName moi: ";
    getline(cin, fullNameInput);
    cout << "Nhap email moi: ";
    getline(cin, emailInput);

    //Tim kiem user theo userId sau do cap nhat thong tin moi
    int index = findUserById(userList, userIdInput);
    if(index != -1) {
        //Xac thuc OTP truoc khi cap nhat thong tin
        string email = userList[index].getEmail();
        bool isSuccess = verifyOTP(email);
        if(isSuccess == false) {
            cout << "Xac thuc that bai. Khong the cap nhat thong tin." << endl;
            return 0; // Ket thuc chuong trinh neu xac thuc that bai
        }
        cout << "Xac thuc thanh cong!" << endl;
        
        //Cap nhat thong tin cho user sau khi xac thuc thanh cong
        userList[index].setFullName(fullNameInput);
        userList[index].setEmail(emailInput);
        cout << "Da cap nhat thong tin cho userId: " << userIdInput << endl;
    }
    else {
        cout << "Khong tim thay user voi userId: " << userIdInput << endl;
        return 0; // Ket thuc chuong trinh neu khong tim thay user
    }   
    
    printList(userList);

    return 0;
}
