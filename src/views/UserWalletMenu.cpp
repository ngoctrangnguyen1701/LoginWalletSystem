//include file .h tuong ung voi .cpp
#include "UserWalletMenu.h"

//Contructors
//goi truc tiep contructor cua lop Menu
UserWalletMenu::UserWalletMenu() : Menu("Menu thao tac vi tien") {
  options = vector<string>(6); //Tao vector co 6 phan tu
  options[0] = "1. Nap";
  options[1] = "2. Rut";
  options[2] = "3. Chuyen khoan";
  options[3] = "4. Xem so du";
  options[4] = "5. Lich su giao dich";
  options[5] = "6. Quay ve menu truoc";
}

//Methods
void UserWalletMenu::display() {
  cout << endl;
  printHeader();
  
  for (int i = 0; i < options.size(); i++) {
    cout << "   " << options[i] << endl;
  }
  cout << endl;
  cout << "> Chon mot thao tac: ";
}

void UserWalletMenu::handleInput() {
  cin >> selectedOption;
  cin.ignore();

  Application& app = Application::getInstance();
  if (selectedOption == "1") {
    handleDeposit();
  } else if (selectedOption == "2") {
    cout << "Processing withdraw..." << endl;
    //TODO
  } else if (selectedOption == "3") {
    cout << "Processing tranfer..." << endl;
    //TODO
  } else if (selectedOption == "4") {
    cout << "Processing check balance..." << endl;
    //TODO
  } else if (selectedOption == "5") {
    //TODO // Chuyen sang menu lich su giao dich cua admin
    return;
  } else if (selectedOption == "6") {
    //TODO // Chuyen sang menu nguoi dung thong thuong
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
  app.setCurrentMenu("UserMenu"); // Chuyen sang menu nguoi dung thong thuong
}

void UserWalletMenu::handleDeposit() {
  //Tinh nang nap diem vao vi nguoi dung
  cout << endl;
  console.task("Nap diem vao vi");
  int amount;
  do
  {
    cout << "> Nhap so diem can nap: ";
    cin >> amount;
    cin.ignore();
    if (amount <= 0) {
      console.notify("So diem nap phai lon hon 0!");
    }
  } while (amount <= 0);

  char choice;
  do
  {    
    cout << "> Xac nhan NAP '" << amount << "' diem vao vi? (y/n): ";
    cin >> choice;
    cin.ignore();
  } while (choice != 'y' && choice != 'n');

  if(choice == 'n') {
    return;
  }

  UserWallet wallet;
  bool result = wallet.deposit(amount);
  if(result == true) {
    console.notify("Nap diem thanh cong!");
  }
  else {
    console.notify("Nap diem that bai!");
  }
}