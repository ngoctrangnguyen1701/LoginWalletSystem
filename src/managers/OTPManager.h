#ifndef OTP_H //Neu chua duoc dinh nghia
#define OTP_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>

//include file header noi bo khac
#include "../utils/ConsoleUtils.h"
#include "../libraries/totp.h"

using namespace std;

class OTPManager
{
	private:
		string code;
		int userId; //user yeu cau OTP;
		string type; //OTP su dung cho muc dich gi ("changePassword", "changeInfo", "deposit", "withdraw", "transfer")
		time_t createdTime;
		int expiredTime = 60; //Thoi gian het han, mac dinh la 60 giay
		ConsoleUtils console;
		uint8_t totpKey[20];
	protected:
	public:
		//Getters
		int getExpiredTime();

		//Methods
		bool generateOTP(int userId, string type);
		bool checkIsValid(int userId, string type, string OTPCode); //-> check correct and expired
		bool verifyOTP(int userId, string type); 
		bool generateTOTP(int userId, string type);
		bool verifyTOTP(int userId, string type); 
};

#endif
