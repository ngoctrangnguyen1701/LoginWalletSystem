//include file .h tuong ung voi .cpp
#include "WalletMenu.h"

//include thu vien
// #include <iostream>
// #include <string>

//include file header noi bo khac
// #include "../Application.h"

//Contructors
//goi truc tiep contructor cua lop Menu
WalletMenu::WalletMenu() : Menu("Menu thao tac vi tien") {
  Application& app = Application::getInstance();
  bool isAdmin = app.getCurrentUser()->getIsAdmin(); // Kiem tra xem nguoi dung co phai la admin hay khong
  if(isAdmin == true) {
    //Menu vi tong
    options = vector<string>(6); //Tao vector co 6 phan tu
    options[0] = "1. Nap";
    options[1] = "2. Rut";    
    options[3] = "3. Xem so du";
    options[4] = "4. Lich su giao dich (hien thi giao dich theo vi, neu la admin thi hien thi giao dich cua vi tong)";
    options[5] = "6. Quay ve menu truoc";
  } else {
    //Menu vi cua nguoi dung thong thuong
  }
}

//Methods
void WalletMenu::display() {
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

void WalletMenu::handleInput() {
  cin >> selectedOption;
  cin.ignore();

  Application& app = Application::getInstance();
  if (selectedOption == "1") {
    cout << "Processing update info..." << endl;      
    //TODO: logic update info
  } else if (selectedOption == "2") {
    cout << "Processing display wallet menu..." << endl;
    //TODO: logic display wallet menu      
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
  app.setCurrentMenu("WalletMenu"); // Chuyen sang menu admin
}
