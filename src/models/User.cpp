//include file .h tuong ung voi .cpp
#include "User.h"

//include file header noi bo khac
#include "../managers/UserManager.h"

//Contructors
User::User(string username, string password, string fullName, string email, bool isAdmin, bool isAutoGenPassword){
  this->username = username;
  // this->password = password;
  this->fullName = fullName;
  this->email = email;
  this->isAdmin = isAdmin;
  this->isAutoGenPassword = isAutoGenPassword;
  //TODO
  // this->createdAt.date = "2023-10-01"; //mac dinh la ngay hien tai
  // this->createdAt.time = "12:00:00"; //mac dinh la thoi gian hien tai

  //Hash password
  this->passwordSalt = HashUtils::generateSalt();
  this->passwordHash = HashUtils::generateHash(password, this->passwordSalt);
}

User::User(string username, string passwordHash, string passwordSalt, string fullName, string email, bool isAdmin, bool isAutoGenPassword){
  this->username = username;
  // this->password = password;
  this->passwordHash = passwordHash;
  this->passwordSalt = passwordSalt;
  this->fullName = fullName;
  this->email = email;
  this->isAdmin = isAdmin;
  this->isAutoGenPassword = isAutoGenPassword;
  
  //TODO
  // this->createdAt.date = "2023-10-01"; //mac dinh la ngay hien tai
  // this->createdAt.time = "12:00:00"; //mac dinh la thoi gian hien tai
}

//Destructor
User::~User(){
  //TODO
  //Xoa user
  // cout << "User destructor" << endl;
}

//Getters
int User::getUserId() {
  return userId;
}

string User::getUsername() {
  return username;
}

// string User::getPassword() {
//   return password;
// }

string User::getPasswordHash(){
  return passwordHash;
};

string User::getPasswordSalt(){
  return passwordSalt;
};

string User::getFullName() {
  return fullName;
}

string User::getEmail() {
  return email;
}

bool User::getIsAdmin() {
  return isAdmin;
}

bool User::getIsAutoGenPassword() {
  return isAutoGenPassword;
}

//Setters
void User::setUserId(int userId) {
  this->userId = userId;
}
void User::setUsername(string username) {
  this->username = username;
}
// void User::setPassword(string password) {
//   this->password = password; 
// }
void User::setPasswordHash(string passwordHash) {
  this->passwordHash = passwordHash;
};
void User::setPasswordSalt(string passwordSalt) {
  this->passwordSalt = passwordSalt;
};
void User::setFullName(string fullName) {
  this->fullName = fullName;
}
void User::setEmail(string email) {
  this->email = email;
}
void User::setIsAdmin(bool isAdmin) {
  this->isAdmin = isAdmin;
}
void User::setIsAutoGenPassword(bool isAutoGenPassword) {
  this->isAutoGenPassword = isAutoGenPassword;
}

//Methods
User* User::authenticate(string username, string password){
  //Kiem tra co dung thong tin dang nhap khong  
  //Neu co thi tra ve true, khong thi tra ve false
  UserManager userMgr;
  //TODO: su dung ham hash de ma hoa mat khau
  User* user = userMgr.findUserFromFile(username, password);  
  return user;
};
	
bool User::changePassword(string oldPassword, string newPassword){
  //TODO
  bool reuslt = false;
  return reuslt;
};
	
// bool User::updateInfo(UserInfo newInfo){
//   //TODO
//   bool reuslt = false;
//   return reuslt;
// };
	
bool User::requirePasswordChange(){
  //TODO
  //neu la mat khau tu sinh thi phai doi mat khau
  bool reuslt = false;
  return reuslt;
};

string User::autoGeneratePassword() {
  //Do dai toi thieu 7 ky tu
  //Bao gom chu hoa, chu thuong, so va ky tu dac biet
  //ex: A@a1234
  srand(time(NULL)); // Khoi tao bo sinh so ngau nhien
  string upperCharacterStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  string lowerCharacterStr = "abcdefghijklmnopqrstuvwxyz";
  string numberStr = "0123456789";
  string specialCharacterStr = "!@#$%^&*()-_+=[]{}\\|;:,.<>?'\"";

  string result = ""; // Chuoi ket qua
  result += upperCharacterStr[rand() % upperCharacterStr.length()]; // Chon ngau nhien 1 ky tu hoa
  result += lowerCharacterStr[rand() % lowerCharacterStr.length()]; // Chon ngau nhien 1 ky tu thuong
  result += numberStr[rand() % numberStr.length()]; // Chon ngau nhien 1 ky tu so
  result += numberStr[rand() % numberStr.length()]; // Chon ngau nhien 1 ky tu so
  result += numberStr[rand() % numberStr.length()]; // Chon ngau nhien 1 ky tu so
  result += numberStr[rand() % numberStr.length()]; // Chon ngau nhien 1 ky tu so
  result += specialCharacterStr[rand() % specialCharacterStr.length()]; // Chon ngau nhien 1 ky tu dac biet
  return result;
}

bool User::checkIsValidPassword(string password) {
  //Mat khau hop le la mat khau co do dai toi thieu 7 ky tu,
  //bao gom chu hoa, chu thuong, so va ky tu dac biet va khong duoc chua khoang trang
  //ex: A@a1234
  
  if(password.length() < 7) {
    // cout << "Mat khau phai co do dai toi thieu 7 ky tu" << endl;
    console.notify("Mat khau phai co do dai toi thieu 7 ky tu");
    return false;
  }  

  bool hasUpper = false;
  bool hasLower = false;
  bool hasNumber = false;
  bool hasSpecialCharacter = false;
  for(int i = 0; i < password.length(); i++) {
    if(password[i] == ' ') {
      // cout << "Mat khau khong duoc chua khoang trang" << endl;
      console.notify("Mat khau khong duoc chua khoang trang");
      return false;
    }
    if(password[i] >= 'A' && password[i] <= 'Z') {
      hasUpper = true;
    } else if(password[i] >= 'a' && password[i] <= 'z') {
      hasLower = true;
    } else if(password[i] >= '0' && password[i] <= '9') {
      hasNumber = true;
    } else {
      hasSpecialCharacter = true;
    }
  }

  if(hasUpper == false) {
    console.notify("Mat khau phai co it nhat 1 ky tu hoa");
    return false;
  }
  if(hasUpper == false) {
    console.notify("Mat khau phai co it nhat 1 ky tu thuong");
    return false;
  }
  if(hasNumber == false) {
    console.notify("Mat khau phai co it nhat 1 ky tu so");
    return false;
  }
  if(hasSpecialCharacter == false) {
    console.notify("Mat khau phai co it nhat 1 ky tu dac biet");
    return false;
  }

  return true;
};
