#include <iostream>

#include "AdminMenu.h"
#include "../Application.h"
using namespace std;

//Contructors
//goi truc tiep contructor cua lop Menu
AdminMenu::AdminMenu() : Menu("Menu danh cho Admin") {
  options = vector<string>(7); //Tao vector co 7 phan tu
  options[0] = "1. Doc danh sach user";
  options[1] = "2. Them user";
  options[2] = "3. Thay doi thong tin user";
  options[3] = "4. Xoa user";
  options[4] = "5. Vi tong";
  options[5] = "6. Sao luu va khoi phuc du lieu";
  options[6] = "7. Dang xuat";
}

//Methods
void AdminMenu::display() {
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

void AdminMenu::handleInput() {
  cin >> selectedOption;
  cin.ignore();

  Application& app = Application::getInstance();
  switch (selectedOption) {
    case 1:
      handleReadUserList();
      break;
    case 2:
      handleCreateUser();
      break;
    case 3:
      handleUpdateUser();
      break;
    case 4:
      handleDeleteUser();
      break;
    case 5:
      cout << "Processing wallet summary..." << endl;
      // TODO: logic for wallet summary
      break;
    case 6:
      cout << "Processing backup and restore data..." << endl;
      // TODO: logic for backup and restore data
      break;
    case 7:
      app.setCurrentMenu("LoginMenu"); // Chuyen sang menu login
      return;
    default:
      cout << "Lua chon khong hop le! Vui long chon lai" << endl;
      break;
  }
  // cout << endl;
  char choice;
  do
  {    
    cout << "> Quay tro ve menu? (y): ";
    cin >> choice;
    cin.ignore();
  } while (choice != 'y');
  app.setCurrentMenu("AdminMenu"); // Chuyen sang menu admin
}

void AdminMenu::handleReadUserList() {
  Application& app = Application::getInstance();
  app.getUserMgr().displayList();
}

void AdminMenu::handleCreateUser() {
  //Nhap thon tin user tu ban phim
  string username;
  string password = "123"; //TODO: mat khau tu sinh
  string fullName;
  string email;
  bool isAdmin = false;
  bool isAutoGenPassword = true; //TODO: mat khau tu sinh
  cout << endl;
  cout << "===== Tao nguoi dung moi =====" << endl;
  cout << "Ten dang nhap: ";
  getline(cin, username);  
  // cout << "Mat khau: ";
  // getline(cin, password);
  cout << "Ho va ten: ";
  getline(cin, fullName);
  cout << "Email: ";
  getline(cin, email);

  User newUser(username, password, fullName, email, isAdmin, isAutoGenPassword);

  Application& app = Application::getInstance();
  bool resultCreate = app.getUserMgr().createUser(newUser);
  if(resultCreate == true) {
    cout << "Tao user thanh cong!" << endl;
  } else {
    cout << "Tao user that bai!" << endl;
  }
}

void AdminMenu::handleUpdateUser() {
  // cout << endl;
  char choice;
  do
  {    
    cout << "> Hien thi danh sach nguoi dung de chon cap nhat? (y/n): ";
    cin >> choice;
    cin.ignore();
  } while (choice != 'y' && choice != 'n');

  int userId;
  string fullName = "";
  string email = "";
  Application& app = Application::getInstance();

  if(choice == 'y') {
    app.getUserMgr().displayList();
  }
  cout << "> Nhap ID nguoi dung muon thay doi: ";
  cin >> userId;
  cin.ignore();
  
  cout << endl;
  int choice_2 = 0;
  do
  { 
    if(choice_2 != 0 && choice_2 != 1 && choice_2 != 2 && choice_2 != 3 && choice_2 != 4) {
      cout << "Lua chon khong hop le! Vui long chon lai" << endl;
    }
    cout << "===== Thay doi thong tin =====" << endl;
    cout << "   " << "1. Ho va ten" << endl;
    cout << "   " << "2. Email" << endl;
    cout << "   " << "3. Thay doi [1] va [2]" << endl;
    cout << "   " << "4. Quay tro ve menu" << endl;
    cout << "> Chon mot thao tac: ";
    cin >> choice_2;
    cin.ignore();
  } while (choice_2 != 1 && choice_2 != 2 && choice_2 != 3 && choice_2 != 4);

  // cin.ignore(); // Bo qua ki tu xuong dong
  if(choice_2 == 1) {
    cout << "Nhap ho va ten moi: ";
    getline(cin, fullName);
  } else if(choice_2 == 2) {
    cout << "Nhap email moi: ";
    getline(cin, email);
  } else if(choice_2 == 3) {
    cout << "Nhap ho va ten moi: ";
    getline(cin, fullName);
    cout << "Nhap email moi: ";
    getline(cin, email);
  } else if(choice_2 == 4) {
    app.setCurrentMenu("AdminMenu"); // Chuyen sang menu admin
    return;
  }

  bool resultUpdate = app.getUserMgr().updateUser(userId, fullName, email);
  if(resultUpdate == true) {
    cout << "Cap nhat user thanh cong!" << endl;
  } else {
    cout << "Cap nhat user that bai!" << endl;
  }
}

void AdminMenu::handleDeleteUser() {
  // cout << endl;
  char choice;
  do
  {    
    cout << "> Hien thi danh sach nguoi dung de xoa? (y/n): ";
    cin >> choice;
    cin.ignore();
  } while (choice != 'y' && choice != 'n');

  int userId;
  string fullName = "";
  string email = "";
  Application& app = Application::getInstance();

  if(choice == 'y') {
    app.getUserMgr().displayList();
  }
  cout << "> Nhap ID nguoi dung muon xoa: ";
  cin >> userId;
  cin.ignore(); 
  
  cout << endl;
  int choice_2 = 0;
  do
  { 
    if(choice_2 != 0 && choice_2 != 1 && choice_2 != 2) {
      cout << "Lua chon khong hop le! Vui long chon lai" << endl;
    }
    cout << "===== XAC NHAN XOA USER_ID '" << userId << "' =====" << endl;
    cout << "   " << "1. Dong y xoa" << endl;
    cout << "   " << "2. Huy bo xoa" << endl;
    cout << "> Chon mot thao tac: ";
    cin >> choice_2;
    cin.ignore();
  } while (choice_2 != 1 && choice_2 != 2);

  if(choice_2 == 2) {
    app.setCurrentMenu("AdminMenu"); // Chuyen sang menu admin
    return;
  }

  bool resultDelete = app.getUserMgr().deleteUser(userId);
  //TODO: Xoa vi cua user bi xoa, diem trong vi bi xoa se tra ve vi tong
  if(resultDelete == true) {
    cout << "Xoa user thanh cong!" << endl;
  } else {
    cout << "Xoa user that bai!" << endl;
  }
}
