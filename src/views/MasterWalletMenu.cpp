//include file .h tuong ung voi .cpp
#include "MasterWalletMenu.h"

//include thu vien
// #include <iostream>
// #include <string>

//include file header noi bo khac
// #include "../Application.h"

//Contructors
//goi truc tiep contructor cua lop Menu
MasterWalletMenu::MasterWalletMenu() : Menu("Menu thao tac vi tien") {
  options = vector<string>(5); //Tao vector co 5 phan tu
  options[0] = "1. Nap";
  options[1] = "2. Rut";    
  options[2] = "3. Xem so du";
  options[3] = "4. Lich su giao dich";
  options[4] = "5. Quay ve menu truoc";
}

//Methods
void MasterWalletMenu::display() {
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

void MasterWalletMenu::handleInput() {
  cin >> selectedOption;
  cin.ignore();

  Application& app = Application::getInstance();
  if (selectedOption == "1") {
    cout << "Processing deposit..." << endl;      
    //TODO
  } else if (selectedOption == "2") {
    cout << "Processing withdraw..." << endl;
    //TODO
  } else if (selectedOption == "3") {
    cout << "Processing check balance..." << endl;
    //TODO
  } else if (selectedOption == "4") {
    app.setCurrentMenu("AdminTransactionMenu"); // Chuyen sang menu lich su giao dich cua admin
    return;
  } else if (selectedOption == "5") {
    app.setCurrentMenu("AdminMenu"); // Chuyen sang menu admin
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
  app.setCurrentMenu("AdminMenu"); // Chuyen sang menu admin
}
