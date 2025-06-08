//include file .h tuong ung voi .cpp
#include "LoginMenu.h"

//include thu vien
#include <iostream>
#include <string>

//include file header noi bo khac
#include "../Application.h"

using namespace std;

//Contructors
//goi truc tiep contructor cua lop Menu
LoginMenu::LoginMenu() : Menu("Man hinh dang nhap") {
  options = vector<string>(3); //Tao vector co 3 phan tu
  options[0] = "1. Dang nhap";
  options[1] = "2. Dang ky";
  options[2] = "3. Thoat chuong trinh";
}

//Methods
void LoginMenu::display() {
  cout << endl;
  cout << "+--------------------------------+" << endl;
  cout << "       " << title << endl;
  cout << "+--------------------------------+" << endl;
  
  for (int i = 0; i < options.size(); i++) {
    cout << "   " << options[i] << endl;
  }
  cout << endl;
  cout << "> Chon mot thao tac: ";
}

void LoginMenu::handleInput() {
  cin >> selectedOption;
  cin.ignore();

  if (selectedOption == "1") {
    handleLogin();
  } else if (selectedOption == "2") {
    handleSignup();
  } else if (selectedOption == "3") {
    isRunning = false;
  } else {
    cout << "Lua chon khong hop le! Vui long chon lai" << endl;
    return;
  }
}

void LoginMenu::handleLogin() {  
  Application& app = Application::getInstance();
  app.login();
  User* currentUser = app.getCurrentUser(); // Lay nguoi dung hien tai dang nhap thanh cong
  if(currentUser != NULL) {
    if(currentUser->getIsAdmin() == true) {
      app.setCurrentMenu("AdminMenu"); // Chuyen sang menu admin
    } else {
      if(currentUser->getIsAutoGenPassword() == true) {
        // Neu la nguoi dung moi dang nhap lan dau tien, yeu cau doi mat khau
        console.important("THONG BAO: Ban can doi mat khau truoc khi su dung he thong!");
        bool result = currentUser->changePassword();
        if(result == true) {
          // Cap nhat lai bien isAutoGenPassword
          result = app.getUserMgr().updateUser(currentUser->getUserId(), "", "", "", "false");
          if(result == true) {
            console.notify("Thay doi mat khau thanh cong! Vui long dang nhap lai!");
            app.setCurrentMenu("LoginMenu"); // Chuyen sang menu login
            return;
          } else {
            console.notify("Cap nhat mat khau that bai!");
          }
        } else {
          console.notify("Thay doi mat khau that bai!");
        }
      }
      string text = "Xin chao " + currentUser->getFullName() + " den voi he thong!";
      console.important(text);
      app.setCurrentMenu("UserMenu"); // Chuyen sang menu user
    }      
  }
}

void LoginMenu::handleSignup() {
  //Nhap thon tin user tu ban phim
  string username;
  string password;
  string fullName;
  string email;
  bool isAdmin = false;
  bool isAutoGenPassword = false;
  cout << endl;
  cout << "===== Thong tin dang ky =====" << endl;
  bool isExistUsername = false;
  do
  {
    cout << "> Ten dang nhap: ";
    getline(cin, username);
    isExistUsername = checkIsExistUsername(username);
  } while (isExistUsername == true); //Kiem tra ten dang nhap da ton tai hay chua
  
  cout << "> Ho va ten: ";
  getline(cin, fullName);
  cout << "> Email: ";
  getline(cin, email);

  User temp;
  bool isValidPassword = false;
  do
  {
    cout << "> Mat khau: ";
    getline(cin, password);
    isValidPassword = temp.checkIsValidPassword(password);    
  } while (isValidPassword == false); //Kiem tra mat khau hop le

  User newUser(username, password, fullName, email, isAdmin, isAutoGenPassword);
  Application& app = Application::getInstance();
  bool resultCreate = app.getUserMgr().createUser(newUser);
  if(resultCreate == true) {
    console.notify("Dang ky thanh cong!");
  } else {
    console.notify("Dang ky that bai!");
  }
  app.setCurrentMenu("LoginMenu"); // Chuyen sang menu dang nhap
}


bool LoginMenu::checkIsExistUsername(string username) {
  Application& app = Application::getInstance();
  vector<User> userList = app.getUserMgr().getList_2();
  for(int i = 0; i < userList.size(); i++) {
    if(userList[i].getUsername() == username) {
      console.notify("Ten dang nhap da ton tai, vui long chon ten khac!");
      return true;
    }
  }
  return false;
}
