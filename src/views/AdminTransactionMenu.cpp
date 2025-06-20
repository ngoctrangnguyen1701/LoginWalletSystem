//include file .h tuong ung voi .cpp
#include "AdminTransactionMenu.h"

//Contructors
//goi truc tiep contructor cua lop Menu
AdminTransactionMenu::AdminTransactionMenu() : Menu("Menu lich su giao dich cho admin") {
  options = vector<string>(2); // Tao vector co 2 phan tu
  options[0] = "1. Doc danh sach tat ca giao dich"; 
  options[1] = "2. Quay ve menu truoc";
}

//Methods
void AdminTransactionMenu::display() {
  cout << endl;
  printHeader();
  
  for (int i = 0; i < options.size(); i++) {
    cout << "   " << options[i] << endl;
  }
  cout << endl;
  cout << "> Chon mot thao tac: ";
}

void AdminTransactionMenu::handleInput() {
  cin >> selectedOption;
  cin.ignore();

  Application& app = Application::getInstance();
  if (selectedOption == "1") {
    handleReadTransactionList();
  } else if (selectedOption == "2") {
    app.setCurrentMenu("MasterWalletMenu"); // Chuyen sang menu cua vi tong
    return;
  } else {
    cout << "Lua chon khong hop le! Vui long chon lai!" << endl;
    return;
  }
  
  backToMenu("MasterWalletMenu"); // Chuyen sang menu cua vi tong
}

void AdminTransactionMenu::handleReadTransactionList() {
  Application& app = Application::getInstance();
  app.getTransactionMgr().displayList();
}
