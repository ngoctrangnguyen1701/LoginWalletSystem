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
    cout << "Processing signup..." << endl;
    //TODO
    //logic signup...
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
        cout << "Ban can doi mat khau truoc khi su dung he thong!" << endl;
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
      app.setCurrentMenu("UserMenu"); // Chuyen sang menu user
    }      
  }
}
