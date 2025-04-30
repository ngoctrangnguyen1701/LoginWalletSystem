//include file .h tuong ung voi .cpp
#include "HashUtils.h"

//Methods
string HashUtils::generateHash(string password, string salt){
  string newStr = salt + password;
  string hash = picosha2::hash256_hex_string(newStr);
  return hash;
}

string HashUtils::generateSalt() {
  stringstream ss;
  
  for (int i = 0; i < 16; i++) {
    int randomValue = rand() % 256; // Gia tri tu 0 den 255 (1 byte)
    ss << std::setfill('0') << std::setw(2) << std::hex << randomValue;
  }
  return ss.str();
}
