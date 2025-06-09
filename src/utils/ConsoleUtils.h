#ifndef ConsoleUtils_H //Neu chua duoc dinh nghia
#define ConsoleUtils_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header


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
    // In thong tin quan trong
    void important(string text);
    //In thao tac dang thuc hien
    void task(string text);
};

#endif
