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
  options = vector<string>(3); //Tao vector co 3 phan tu
  options[0] = "1. Thay doi thong tin";
  options[1] = "2. Vi cua toi";
  options[2] = "3. Dang xuat";
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
    // cout << "Processing update info..." << endl;      
    //TODO: logic update info
  } else if (selectedOption == "2") {
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
  } else if (selectedOption == "3") {
    app.setCurrentMenu("LoginMenu"); // Chuyen sang menu login
    return;
  } else {
    cout << "Lua chon khong hop le! Vui long chon lai" << endl;
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

// void UserMenu::handleShowWalletMenu() {
//   Application& app = Application::getInstance();
//   int userId = app.getCurrentUser()->getUserId(); //Lay userId cua nguoi dung hien tai
//   Wallet* wallet = app.getWalletMgr().findWalletByUserIdFromFile(userId);
//   if(wallet == NULL) {
//     // Chua co vi, chuyen sang menu tao vi
//     app.setCurrentMenu("CreateWalletMenu"); // Chuyen sang menu tao vi
//     return;
//   } else {
//     // Da co vi, chuyen sang menu vi nguoi dung
//     app.setCurrentMenu("UserWalletMenu"); // Chuyen sang menu vi nguoi dung
//     return;
//   }
// }

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
    cout << "   " << "3. Thay doi mat khau" << endl;
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
  } else if(choice == 4) {
    app.setCurrentMenu("UserMenu"); // Chuyen sang menu user
    return;
  }

  if(choice == 1 || choice == 2) {
    bool resultUpdate = app.getUserMgr().updateUser(userId, fullName, email);
    if(resultUpdate == true) {
      if(choice == 1) {
        string text = currentUser->getFullName() + " -> " + fullName;
        console.notify("Thay doi thong tin ho va ten: " + text);
      }
      if(choice == 2) {
        string text = currentUser->getEmail() + " -> " + email;
        console.notify("Thay doi thong tin email: " + text);
      }
    } else {
      console.notify("Thay doi thong tin that bai!");
    }
  }
  else if(choice == 3) {
    string newPassord;
    bool isValidPassword = false;
    bool isDuplicateOldPassword = false;
    do
    {
      cout << "> Nhap mat khau moi: ";
      getline(cin, newPassord);
      isDuplicateOldPassword = currentUser->checkIsDuplicatePassword(newPassord);
      if(isDuplicateOldPassword == false) {
        isValidPassword = currentUser->checkIsValidPassword(newPassord);
      }
    } while (isValidPassword == false || isDuplicateOldPassword == true);
    string passwordHash = HashUtils::generateHash(newPassord, currentUser->getPasswordSalt());
    bool resultUpdate = app.getUserMgr().updateUser(userId, fullName, email, passwordHash);
    if(resultUpdate == true) {
      console.notify("Thay doi mat khau thanh cong!");
    } else {
      console.notify("Thay doi mat khau that bai!");
    }
  }
  return;
}
