#include <iostream>
#include <string>

//include file tu dinh nghia
#include "Application.h"
#include "./models/User.h"
#include "./views/LoginMenu.h"
#include "./views/UserMenu.h"
#include "./views/AdminMenu.h"
#include "./utils/FileUtils.h"


using namespace std;

//Contructors
// Application::Application(){
//   cout << "Application::Application" << endl;  
// }

Application& Application::getInstance() {
  static Application instance;
  return instance;
}

//Destructor
Application::~Application(){  
  cout << "Application destructor" << endl;
  if(currentMenu != NULL) {
    delete currentMenu; // Giai phong bo nho sau khi xong
  }
  if(currentUser != NULL) {
    delete currentUser; // Giai phong bo nho sau khi xong
  }

  exit(0); // Thoat chuong trinh
}

//Getters
User* Application::getCurrentUser(){
  return currentUser;
}
Menu* Application::getCurrentMenu(){
  return currentMenu;
}
UserManager Application::getUserMgr(){
  return userMgr;
}

//Setters
void Application::setCurrentMenu(string menuName) {
  //Reset lai currentMenu ve NULL
  if(currentMenu != NULL) {
    delete currentMenu;    
    currentMenu = NULL;
  }
  if(menuName == "LoginMenu") {
    //Reset lai currentUser ve NULL
    if(currentUser != NULL) {
      delete currentUser;
      currentUser = NULL;
    }
    currentMenu = new LoginMenu(); // Khoi tao menu dang nhap
  } else if(menuName == "AdminMenu") {
    currentMenu = new AdminMenu(); // Khoi tao menu admin
  } else if(menuName == "UserMenu") {
    currentMenu = new UserMenu(); // Khoi tao menu user
  }
}

//Methods
void Application::initialize(){
  cout << "Application is initializing..." << endl;
  
  FileUtils fileUtils(userMgr.filename, userMgr.filenameNextId);
  bool isEmpty = fileUtils.isEmptyFile(); 
  if(isEmpty == true) {
    //Tao file userData.csv voi danh sach user ban dau va file chua thong tin useerNextId
    userMgr.createSampleData();   
  }
}

void Application::login(){
  string username, password;
  cout << "Ten dang nhap: ";
  getline(cin, username);  
  cout << "Mat khau: ";
  getline(cin, password);
  
  //authenticate user
  User user;
  User* result = user.authenticate(username, password);
  if(result != NULL) {
    cout << "Dang nhap thanh cong" << endl;
    delete currentUser; // Giai phong bo nho currentUser truoc khi gan lai
    currentUser = NULL;
    currentUser = new User(*result); // Gan user dang nhap thanh cong cho currentUser
  } else {
    cout << "Dang nhap that bai" << endl;
    currentUser = NULL;
  }  
}

bool Application::signup(){
  //TODO
  bool result = false;
  //neu dang ky thanh cong tra ra true, khong thanh cong tra ra false
  return result;
}
 
bool Application::logout(){
  //TODO
  //neu dang xuat thanh cong tra ra true, khong thanh cong tra ra false
  bool result = false;
  return result;
}

void Application::run(){  
  cout << "Application is running..." << endl;

  currentMenu = new LoginMenu();  // Khoi tao menu dang nhap
  currentMenu->display();
  currentMenu->handleInput();
  while (currentMenu && currentMenu->getIsRunning()) {    
    currentMenu->display();
    currentMenu->handleInput();
  }
}
