//include file .h tuong ung voi .cpp
#include "OTPManager.h"

//include file header noi bo khac
#include "../Application.h"

//Getters
int OTPManager::getExpiredTime() {
  return expiredTime;
}

//Methods
bool OTPManager::generateOTP(int userId, string type){
  Application& app = Application::getInstance();
  User* userExist =  app.getUserMgr().findUserByConditionFromFile("userId", to_string(userId));
  if(userExist == NULL) {
    return false;
  }
  this->userId = userId;
  this->type = type;
  this->createdTime = time(NULL); // Thoi diem hien tai

  // Gen ra ma ngau nhien 6 chu so
  string randomStr = "";
  for (int i = 0; i < 6; i++)
  {
    int num = rand() % 10; // Chon ngau nhien tu 0 den 9
    randomStr += to_string(num);
  }
  this->code = randomStr;
  string email = userExist->getEmail();
  cout << "Ma OTP gui den email '" + email + "': " << randomStr << endl;

  delete userExist; //Giai phong vung nho
  return true;
}

bool OTPManager::checkIsValid(int userId, string type, string OTPCode) {
  //Kiem tra OTP dung userId, type, code, va expired
  if(this->userId != userId || this->type != type || this->code != OTPCode) {
    console.notify("Ma OTP khong dung!");
    return false;
  }

  //kiem tra het han OTP trong vong 1 phut ke tu luc tao OTP
  time_t now = time(NULL);
  if(now - this->createdTime > this->expiredTime) {
    console.notify("Ma OTP da het han!");
    return false;
  }
  return true;
}

bool OTPManager::verifyOTP(int userId, string type) {
  bool result = generateOTP(userId, type);
  if(result == false) {
    console.notify("Lay ma OTP that bai!");
    return false;
  }
  cout << "> Nhap ma OTP (hieu luc trong vong " << getExpiredTime() << " giay): ";
  string otpInput;
  getline(cin, otpInput);
  bool isValidOTP = checkIsValid(userId, type, otpInput);
  return isValidOTP;
}

// bool OTPManager::generateTOTP(int userId, string type){
//   Application& app = Application::getInstance();
//   User* userExist =  app.getUserMgr().findUserByConditionFromFile("userId", to_string(userId));
//   if(userExist == NULL) {
//     return false;
//   }
//   this->userId = userId;
//   this->type = type;
//   // this->createdTime = time(NULL); // Thoi diem hien tai

//   //Su dung thuat toan totp
//   uint8_t secretKey[] = "SECRETKEY";
//   uint32_t secretKeyLen = strlen((char*)secretKey);
//   uint8_t totpKey[20];
  
//   // Tao totpKey = secretKey + salt
//   HashUtils hashUtils;
//   // string salt = hashUtils.generateSalt();
//   string salt = "1";
//   generate_user_secret(secretKey, secretKeyLen, salt, totpKey);
//   memcpy(this->totpKey, totpKey, sizeof(totpKey));

//   time_t now = time(NULL);
//   uint32_t interval = this->expiredTime; //thay doi 60 giay 1 lan
//   // uint32_t code = generate_totp(totpKey, strlen((char*)totpKey), now, interval);
//   uint32_t code = generate_totp(totpKey, 20, now, interval);
//   string email = userExist->getEmail();
//   cout << "Ma OTP gui den email '" + email + "': " << code << endl;

//   delete userExist; //Giai phong vung nho
//   return true;
// }

// bool OTPManager::verifyTOTP(int userId, string type) {
//   bool resultGen = generateTOTP(userId, type);
//   if(resultGen == false) {
//     console.notify("Lay ma OTP that bai!");
//     return false;
//   }
//   cout << "> Nhap ma OTP (hieu luc trong vong " << getExpiredTime() << " giay): ";
//   string otpInputStr;
//   getline(cin, otpInputStr);
//   int otpInput = atoi(otpInputStr.c_str()); //Chuyen doi ma tu string sang int
//   time_t now = time(NULL);
//   uint32_t interval = this->expiredTime; //thay doi 60 giay 1 lan
//   // int resultVerify = verify_totp(this->totpKey, strlen((char*)this->totpKey), otpInput, now, interval);
//   // FIX 2: Sử dụng độ dài cố định 20 bytes thay vì strlen() sẽ cho kết quả sai vì có thể gặp byte 0x00 ở giữa
//   int resultVerify = verify_totp(this->totpKey, 20, otpInput, now, interval);
//   return resultVerify == 1 ? true : false;
// }


bool OTPManager::generateTOTP(int userId, string type){
  Application& app = Application::getInstance();
  User* userExist =  app.getUserMgr().findUserByConditionFromFile("userId", to_string(userId));
  if(userExist == NULL) {
    return false;
  }
  this->userId = userId;
  this->type = type;

  //Su dung thuat toan totp
  uint8_t secretKey[] = "SECRETKEY";
  uint32_t secretKeyLen = strlen((char*)secretKey);
  uint8_t totpKey[20];
  
  // Tao totpKey = secretKey + salt
  HashUtils hashUtils;
  string salt = hashUtils.generateSalt();
  
  // DEBUG: In salt để kiểm tra
  cout << "[DEBUG generateTOTP] Salt: " << salt << endl;
  
  generate_user_secret(secretKey, secretKeyLen, salt, totpKey);
  memcpy(this->totpKey, totpKey, sizeof(totpKey));

  // DEBUG: In totpKey
  cout << "[DEBUG generateTOTP] totpKey: ";
  for(int i = 0; i < 20; i++) {
    printf("%02x", totpKey[i]);
  }
  cout << endl;

  time_t now = time(NULL);
  uint32_t interval = this->expiredTime;
  
  // DEBUG: In thời gian và interval
  cout << "[DEBUG generateTOTP] Time: " << now << ", Interval: " << interval << endl;
  cout << "[DEBUG generateTOTP] Key length (strlen): " << strlen((char*)totpKey) << endl;
  cout << "[DEBUG generateTOTP] Time counter: " << (now / interval) << endl;
  
  // Thử với độ dài cố định 20 để so sánh
  // uint32_t code1 = generate_totp(totpKey, strlen((char*)totpKey), now, interval);
  uint32_t code2 = generate_totp(totpKey, 20, now, interval);
  
  // cout << "[DEBUG generateTOTP] Code with strlen: " << code1 << endl;
  cout << "[DEBUG generateTOTP] Code with fixed 20: " << code2 << endl;
  
  // uint32_t code = code1;
  uint32_t code = code2;
  string email = userExist->getEmail();
  cout << "Ma OTP gui den email '" + email + "': " << code << endl;

  delete userExist;
  return true;
}

bool OTPManager::verifyTOTP(int userId, string type) {
  bool resultGen = generateTOTP(userId, type);
  if(resultGen == false) {
    console.notify("Lay ma OTP that bai!");
    return false;
  }
  
  cout << "> Nhap ma OTP (hieu luc trong vong " << getExpiredTime() << " giay): ";
  string otpInputStr;
  getline(cin, otpInputStr);
  int otpInput = atoi(otpInputStr.c_str());
  
  // DEBUG: In thông tin verify
  cout << "[DEBUG verifyTOTP] Input OTP: " << otpInput << endl;
  cout << "[DEBUG verifyTOTP] totpKey: ";
  for(int i = 0; i < 20; i++) {
    printf("%02x", this->totpKey[i]);
  }
  cout << endl;
  
  time_t now = time(NULL);
  uint32_t interval = this->expiredTime;
  
  cout << "[DEBUG verifyTOTP] Time: " << now << ", Interval: " << interval << endl;
  cout << "[DEBUG verifyTOTP] Key length (strlen): " << strlen((char*)this->totpKey) << endl;
  cout << "[DEBUG verifyTOTP] Time counter: " << (now / interval) << endl;
  
  // Thử cả 2 cách
  // int result1 = verify_totp(this->totpKey, strlen((char*)this->totpKey), otpInput, now, interval);
  int result2 = verify_totp(this->totpKey, 20, otpInput, now, interval);
  
  // cout << "[DEBUG verifyTOTP] Result with strlen: " << result1 << endl;
  cout << "[DEBUG verifyTOTP] Result with fixed 20: " << result2 << endl;
  
  // int resultVerify = result1;
  int resultVerify = result2;
  
  cout << "[DEBUG verifyTOTP] Verify result: " << resultVerify << endl;
  
  return resultVerify == 1 ? true : false;
}