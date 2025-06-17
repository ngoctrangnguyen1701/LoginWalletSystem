//include file .h tuong ung voi .cpp
#include "HashUtils.h"

//Methods
string HashUtils::generateSalt() {
  //Tao 16 byte ngay nhien thanh 2 ky tu hex -> ket qua la chuoi 32 ky tu hex
  stringstream ss;
  
  for (int i = 0; i < 16; i++) {
    int randomValue = rand() % 256; // Gia tri tu 0 den 255 (1 byte)
    //bien doi sang he hex, voi nhung ky tu khong du 2 chu ky tu thi them so 0 vao truoc
    //vd: 0x0A -> 0A, 0x0F -> 0F, 0x10 -> 10
    ss << std::setfill('0') << std::setw(2) << std::hex << randomValue;
  }
  return ss.str();
}

string HashUtils::generateHash(string password, string salt){
  // Noi chuoi salt va password
  string newStr = salt + password;
  
  // Tao buffer cho chuoi dau vao
  char* strPtr = new char[newStr.length() + 1];
  strcpy(strPtr, newStr.c_str());
  
  // Xu ly hash
  SHA256_CTX ctx;
  MY_BYTE hash[SHA256_BLOCK_SIZE];
  
  sha256_init(&ctx);
  sha256_update(&ctx, (MY_BYTE*)strPtr, strlen(strPtr));
  sha256_final(&ctx, hash);
  
  // Tao buffer rieng cho hex string (65 bytes)
  char* hexBuffer = new char[65];
  
  // Chuyen binary hash thanh hex string
  for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
    sprintf(hexBuffer + (i * 2), "%02x", hash[i]);
  }
  hexBuffer[64] = '\0';
  
  // Tao string result tu hex buffer
  string result(hexBuffer);
  
  // Giai phong bo nho
  delete[] strPtr;
  delete[] hexBuffer;
  
  return result;
}
