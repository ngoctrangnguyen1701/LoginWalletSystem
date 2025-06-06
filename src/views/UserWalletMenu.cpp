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
  cout << "+--------------------------------+" << endl;
  cout << "       " << title << endl;
  cout << "+--------------------------------+" << endl;
  
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
    cout << "Processing deposit..." << endl;      
    //TODO
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
