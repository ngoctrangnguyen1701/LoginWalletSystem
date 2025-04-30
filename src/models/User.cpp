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
  cout << "this->passwordSalt: " << this->passwordSalt << endl;
  cout << "this->passwordHash: " << this->passwordHash << endl;
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
