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

  // Gen ra ma ngau nhien 5 chu so
  string randomStr = "";
  for (int i = 0; i < 5; i++)
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
