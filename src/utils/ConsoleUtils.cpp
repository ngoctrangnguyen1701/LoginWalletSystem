//include file .h tuong ung voi .cpp
#include "ConsoleUtils.h"

//include thu vien
#include <iostream>
#include <string>

using namespace std;

//Methods
void ConsoleUtils::notify(string text){
  cout << text << endl;
};
void ConsoleUtils::log(string text) {
  if(isShowLog == true) {
    cout << "#" << text << endl;
  }
};
