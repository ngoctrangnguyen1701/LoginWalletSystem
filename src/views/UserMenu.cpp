#include <iostream>

#include "UserMenu.h"
#include "../Application.h"
using namespace std;
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
  switch (selectedOption) {
    case 1:
      cout << "Processing update info..." << endl;      
      //TODO: logic update info
      break;
    case 2:
      cout << "Processing display wallet menu..." << endl;
      //TODO: logic display wallet menu      
      break;
    case 3:
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
  app.setCurrentMenu("UserMenu"); // Chuyen sang menu admin
}
