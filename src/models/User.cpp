//include file .h tuong ung voi .cpp
#include "User.h"

//include thu vien
#include <iostream>

//include file tu dinh nghia
#include "../managers/UserManager.h"

using namespace std;

//Contructors
User::User(string username, string password, string fullName, string email, bool isAdmin, bool isAutoGenPassword){
  this->username = username;
  this->password = password;
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

string User::getPassword() {
  return password;
}

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
void User::setPassword(string password) {
  this->password = password; 
}
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
