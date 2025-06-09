//include file .h tuong ung voi .cpp
#include "CreateWalletMenu.h"

//Contructors
//goi truc tiep contructor cua lop Menu
CreateWalletMenu::CreateWalletMenu() : Menu("Menu thao tac vi tien") {
  options = vector<string>(2); //Tao vector co 2 phan tu
  options[0] = "1. Tao vi";
  options[1] = "2. Quay ve menu truoc";
}

//Methods
void CreateWalletMenu::display() {
  cout << endl;
  printHeader();
  
  for (int i = 0; i < options.size(); i++) {
    cout << "   " << options[i] << endl;
  }
  cout << endl;
  cout << "> Chon mot thao tac: ";
}

void CreateWalletMenu::handleInput() {
  cin >> selectedOption;
  cin.ignore();

  Application& app = Application::getInstance();
  if (selectedOption == "1") {
    handleCreateWallet();
  } else if (selectedOption == "2") {
    app.setCurrentMenu("UserMenu"); // Chuyen sang menu nguoi dung thong thuong
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

void CreateWalletMenu::handleCreateWallet() {
  char choice;
  do
  {    
    cout << "> Xac nhan tao vi tien? (y/n): ";
    cin >> choice;
    cin.ignore();
  } while (choice != 'y' && choice != 'n');

  if(choice == 'n') {
    return;
  }

  Application& app = Application::getInstance();
  WalletManager walletMgr = app.getWalletMgr();
  int userId = app.getCurrentUser()->getUserId();
  Wallet newWallet(userId, 0, false);

  bool result = walletMgr.createWallet(newWallet);
  if (result == true) {
    console.notify("Tao vi thanh cong!");
  } else {
    console.notify("Tao vi that bai!");
  }
}
