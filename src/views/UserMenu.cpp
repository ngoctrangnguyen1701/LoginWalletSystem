//include file .h tuong ung voi .cpp
#include "UserMenu.h"

//include thu vien
#include <iostream>
#include <string>

//include file header noi bo khac
#include "../Application.h"

//Contructors
//goi truc tiep contructor cua lop Menu
UserMenu::UserMenu() : Menu("Menu cho nguoi dung") {
  options = vector<string>(4); //Tao vector co 4 phan tu
  options[0] = "1. Thay doi thong tin";
  options[1] = "2. Thay doi mat khau";
  options[2] = "3. Vi cua toi";
  options[3] = "4. Dang xuat";
}

//Methods
void UserMenu::display() {
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

void UserMenu::handleInput() {
  cin >> selectedOption;
  cin.ignore();

  Application& app = Application::getInstance();
  if (selectedOption == "1") {
    handleChangeInfo();
  } else if (selectedOption == "2") {
    handleChangePassword();    
  } else if (selectedOption == "3") {
    int userId = app.getCurrentUser()->getUserId(); //Lay userId cua nguoi dung hien tai
    Wallet* wallet = app.getWalletMgr().findWalletByUserIdFromFile(userId);
    if(wallet == NULL) {
      // Chua co vi, chuyen sang menu tao vi
      app.setCurrentMenu("CreateWalletMenu"); // Chuyen sang menu tao vi
      return;
    } else {
      // Da co vi, chuyen sang menu vi nguoi dung
      app.setCurrentMenu("UserWalletMenu"); // Chuyen sang menu vi nguoi dung
      return;
    }
  } else if (selectedOption == "4") {
    app.setCurrentMenu("LoginMenu"); // Chuyen sang menu login
    return;
  } else {
    cout << "Lua chon khong hop le! Vui long chon lai" << endl;
    return;
  }

  if(isReloadLogin == true) {
    app.setCurrentMenu("LoginMenu"); // Chuyen sang menu login
    return;
  }
  
  // cout << endl;
  char choice;
  do
  {    
    cout << "> Quay tro ve menu? (y): ";
    cin >> choice;
    cin.ignore();
  } while (choice != 'y');    
  app.setCurrentMenu("UserMenu"); // Chuyen sang menu admin
}

void UserMenu::handleChangeInfo() {
  cout << endl;
  int choice = 0;
  do
  { 
    if(choice != 0 && choice != 1 && choice != 2 && choice != 3 && choice != 4) {
      cout << "Lua chon khong hop le! Vui long chon lai" << endl;
    }
    cout << "===== Thay doi thong tin =====" << endl;
    cout << "   " << "1. Ho va ten" << endl;
    cout << "   " << "2. Email" << endl;
    cout << "   " << "3. Thay doi [1] va [2]" << endl;
    cout << "   " << "4. Quay tro ve menu" << endl;
    cout << "> Chon mot thao tac: ";
    cin >> choice;
    cin.ignore();
  } while (choice != 1 && choice != 2 && choice != 3 && choice != 4);

  // cin.ignore(); // Bo qua ki tu xuong dong
  Application& app = Application::getInstance();
  User* currentUser = app.getCurrentUser();
  int userId = currentUser->getUserId();
  string fullName = "";
  string email = "";

  if(choice == 1) {
    cout << "> Nhap ho va ten moi: ";
    getline(cin, fullName);
  } else if(choice == 2) {
    cout << "> Nhap email moi: ";
    getline(cin, email);
  } else if(choice == 3) {
    cout << "> Nhap ho va ten moi: ";
    getline(cin, fullName);
    cout << "> Nhap email moi: ";
    getline(cin, email);
  } else if(choice == 4) {
    app.setCurrentMenu("UserMenu"); // Chuyen sang menu user
    return;
  }

  bool resultUpdate = app.getUserMgr().updateUser(userId, fullName, email);
  string text = "";
  if(resultUpdate == true) {
    if(choice == 1 || choice == 3) {
      text = currentUser->getFullName() + " -> " + fullName;
      console.notify("Thay doi ho va ten: " + text);
    }
    if(choice == 2 || choice == 3) {
      text = currentUser->getEmail() + " -> " + email;
      console.notify("Thay doi thong tin email: " + text);
    }
  } else {
    console.notify("Thay doi thong tin that bai!");
  }
}

void UserMenu::handleChangePassword(){
  Application& app = Application::getInstance();
  User* currentUser = app.getCurrentUser();
  bool result = currentUser->changePassword();
  if(result == true) {
    console.notify("Thay doi mat khau thanh cong! Vui long dang nhap lai!");
    isReloadLogin = true; // Set isReloadLogin to true to reload login menu
  }
  else {
    console.notify("Thay doi mat khau that bai!");
  }
}
