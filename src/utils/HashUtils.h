#ifndef HashUtils_H //Neu chua duoc dinh nghia
#define HashUtils_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>

//include file header noi bo khac
#include "../libraries/sha256.h"

using namespace std;

class HashUtils {
  public:
    //Methods
    static string generateHash(string password, string salt); //Ham ma hoa bam
    static string generateSalt(); //Ham tao salt
};

#endif
