//include file .h tuong ung voi .cpp
#include "HashUtils.h"

//Password hashing
string HashUtils::generateHash(string str){
  string salt = generateSalt();
  // cout << "salt: " << salt << endl;
  string newStr = salt + str;
  string result = picosha2::hash256_hex_string(newStr);
  // cout << "Hash: " << result << endl;
  return result;
}

string HashUtils::generateSalt() {
  std::stringstream ss;
  srand(time(NULL)); // Khoi tao bo sinh so ngau nhien
  
  for (int i = 0; i < 16; i++) {
    int randomValue = rand() % 256; // Gia tri tu 0 den 255 (1 byte)
    ss << std::setfill('0') << std::setw(2) << std::hex << randomValue;
  }
  
  return ss.str();
}
