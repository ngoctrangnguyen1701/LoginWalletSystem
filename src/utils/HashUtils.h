#ifndef HashUtils_H //Neu chua duoc dinh nghia
#define HashUtils_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien
#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <iomanip>

//include file header noi bo khac
#include "../libraries/picosha2.h"

using namespace std;

class HashUtils {
  public:
    static string generateHash(string str); //static de khong can khoi tao doi tuong khi su dung ham
    static string generateSalt(); //Ham tao salt
};

#endif
