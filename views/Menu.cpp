//include file .h tuong ung voi .cpp
#include "Menu.h"

//include thu vien
#include <string>

//include file header noi bo khac
//...

using namespace std;

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