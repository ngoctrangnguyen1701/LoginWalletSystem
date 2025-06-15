#ifndef User_H //Neu chua duoc dinh nghia
#define User_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime> 

//include file header noi bo khac
#include "../utils/HashUtils.h"
#include "../utils/ConsoleUtils.h"
#include "../managers/OTPManager.h"

using namespace std;

class User
{
	private:
		int userId; //(auto increase and unique)
		string username; //(unique)
		string passwordHash; //ma bam cua mat khau (hash)
		string passwordSalt; //muoi bam cua mat khau
		string fullName;
		string email;
		bool isAdmin;
		bool isAutoGenPassword;
		ConsoleUtils console; // Khai bao doi tuong ConsoleUtils
		OTPManager otpMgr; // Khai bao doi tuong OTPManager
	protected:
	public:
		// Constructors
		User() = default;
		User(string username, string password, string fullName, string email, bool isAdmin = false, bool isAutoGenPassword = false); //Contructor voi mat khau chua duoc bam
		User(string username, string passwordHash, string passwordSalt, string fullName, string email, bool isAdmin = false, bool isAutoGenPassword = false); //Contructor voi mat khau da duoc bam

		//Getters 
		int getUserId();
		string getUsername();
		string getPasswordHash();
		string getPasswordSalt();
		string getFullName();
		string getEmail();
		bool getIsAdmin();
		bool getIsAutoGenPassword();

		//Setters
		void setUserId(int userId);
		void setUsername(string username);
		void setPasswordHash(string passwordHash);
		void setPasswordSalt(string passwordSalt);
		void setFullName(string fullName);
		void setEmail(string email);
		void setIsAdmin(bool isAdmin);
		void setIsAutoGenPassword(bool isAutoGenPassword);

		//Methods
		User* authenticate(string username, string password);
		bool changePassword();
		bool changePasswordHash(string newPasswordHash);
		string autoGeneratePassword(); //Ham tao mat khau tu sinh
		bool checkIsValidPassword(string password); //Ham kiem tra mat khau co hop le hay khong
};

#endif
