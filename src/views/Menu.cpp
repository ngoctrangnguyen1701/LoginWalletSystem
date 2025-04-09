#include <string>
using namespace std;
#include "Menu.h"

//Contructors
Menu::Menu(string _title){
  title = _title;
  selectedOption = 0; //mac dinh bang 0 la khong chua chon thao tac nao
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