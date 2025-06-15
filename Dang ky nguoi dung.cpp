#include <iostream>
#include <vector>

using namespace std;

class User {
    private:
        int userId;
        string username;
        string password;
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
        int getUserId() {
            return this->userId;
        };
        string getUsername() {
            return this->username;
        };
        string getPassword() {
            return this->password;
        };
};

//Ham tao du lieu
void createUserList(vector<User> &userList) {
    User user_1;
    user_1.setUserId(1);
    user_1.setUsername("user_1");
    user_1.setPassword("123");
    userList.push_back(user_1);

    User user_2;
    user_2.setUserId(2);
    user_2.setUsername("user_2");
    user_2.setPassword("123");
    userList.push_back(user_2);

    User user_3;
    user_3.setUserId(3);
    user_3.setUsername("user_3");
    user_3.setPassword("123");
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
    }
}

int main() {
    vector<User> userList;
    createUserList(userList);

    string usernameInput;
    string passwordInput;
    cout << "Nhap username: ";
    getline(cin, usernameInput);
    cout << "Nhap password: ";
    getline(cin, passwordInput);

    // Kiem tra username da ton tai chua
    int isExist = 0;
    for(int i = 0; i < userList.size(); i++) {
        string username = userList[i].getUsername();
        if(username == usernameInput) {
            isExist = 1;
            break;
        }
    }

    if(isExist == 1) {
        cout << "username da duoc su dung" << endl;
    } else {
        // Neu username chua ton tai, them nguoi dung moi
        User user;
        int userId = userList.size() + 1;
        user.setUserId(userId);
        user.setUsername(usernameInput);
        user.setPassword(passwordInput);
        userList.push_back(user);
    }
    
    printList(userList);

    return 0;
}
