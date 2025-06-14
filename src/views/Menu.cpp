//include file .h tuong ung voi .cpp
#include "Menu.h"

//include file header noi bo khac
#include "../Application.h"

//Contructors
Menu::Menu(string _title){
  title = _title;
  selectedOption = '0'; //mac dinh bang 0 la khong chua chon thao tac nao
  isRunning = true;
}

//Destructor
Menu::~Menu() {}

//Methods
void Menu::setIsRunning(bool x){
  isRunning = x;
};

bool Menu::getIsRunning() {
  return isRunning;
};

void Menu::printHeader() {
  int length = title.length();
  string border = "+-----";
  for(int i = 0; i < length; i++) {
    border += "-";
  }
  border += "-----+";
  cout << border << endl;
  cout << "      " << title << "      " << endl;
  cout << border << endl;
}

void Menu::backToMenu(string menuName) {
  char choice;
  do
  {    
    cout << "> Quay tro ve menu? (y): ";
    cin >> choice;
    cin.ignore();
  } while (choice != 'y');
  Application& app = Application::getInstance();
  app.setCurrentMenu(menuName);
}
