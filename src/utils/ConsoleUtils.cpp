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
    cout << "#################" << endl;
    cout << text << endl;
    cout << "#################" << endl;
  }
};

void ConsoleUtils::important(string text) {
  int length = text.length();
  string border = "";
  for(int i = 0; i < length; i++) {
    border += "#";
  }
  cout << border << endl;
  cout << text << endl;
  cout << border << endl;
};

void ConsoleUtils::task(string text) {
  cout << "~~~~ " << text << " ~~~~" << endl;
}