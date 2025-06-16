//include file .h tuong ung voi .cpp
#include "OTPManager.h"

//Getters
int OTPManager::getExpiredTime() {
  return expiredTime;
}

//Methods
string OTPManager::generateOTP(int userId, string type){
  this->userId = userId;
  this->type = type;
  this->createdTime = time(NULL); // Thoi diem hien tai

  // Gen ra ma ngau nhien 6 chu so
  string randomStr = "";
  for (int i = 0; i < 5; i++)
  {
    int num = rand() % 10; // Chon ngau nhien tu 0 den 9
    randomStr += to_string(num);
  }
  this->code = randomStr;
  cout << "Ma OTP gui den email: " << randomStr << endl;  
  return randomStr;
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
  generateOTP(userId, type);
  cout << "> Nhap ma OTP (hieu luc trong vong " << getExpiredTime() << " giay): ";
  string otpInput;
  getline(cin, otpInput);
  bool isValidOTP = checkIsValid(userId, type, otpInput);
  return isValidOTP;
}
