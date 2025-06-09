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
  cout << "+--------------------------------+" << endl;
  cout << "       " << title << endl;
  cout << "+--------------------------------+" << endl;
  
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
    cout << "Processing create..." << endl;      
    //TODO
  } else if (selectedOption == "2") {
    //TODO // Chuyen sang menu nguoi dung thong thuong
    return;
  } else {
    cout << "Lua chon khong hop le! Vui long chon lai" << endl;
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
