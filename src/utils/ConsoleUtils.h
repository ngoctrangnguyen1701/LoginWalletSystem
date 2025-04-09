#pragma once
#include <string>
using namespace std;

class ConsoleUtils {
  private:
    // bool isShowLog = true; //hien thi log khi debug code
    bool isShowLog = false;
  public:
    //Methods
    // In thong bao notify
    void notify(string text);
    // In log binh thuong
    void log(string text);
};
