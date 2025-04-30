#ifndef User_H //Neu chua duoc dinh nghia
#define User_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien
#include <iostream>
#include <string>

//include file header noi bo khac
#include "../utils/HashUtils.h"

using namespace std;

struct DateTime
{
	string date; //format: YYYY-MM-DD
	string time; //format: HH:MM:SS
};
class User
{
	private:
		int userId; //(auto increase and unique)
		string username; //(unique)
		// string password; //(hash) //(unique) //TODO
		string passwordHash; //ma bam cua mat khau (hash)
		string passwordSalt; //muoi bam cua mat khau
		string fullName;
		string email;
		bool isAdmin;
		bool isAutoGenPassword;
		// DateTime createdAt; //TODO
	protected:
	public:
		// Constructors
		User() = default;
		User(string username, string password, string fullName, string email, bool isAdmin = false, bool isAutoGenPassword = false);
		User(string username, string passwordHash, string passwordSalt, string fullName, string email, bool isAdmin = false, bool isAutoGenPassword = false);

		//Destructor
		~User(); 

		//Getters 
		int getUserId();
		string getUsername();
		// string getPassword();
		string getPasswordHash();
		string getPasswordSalt();
		string getFullName();
		string getEmail();
		bool getIsAdmin();
		bool getIsAutoGenPassword();

		//Setters
		void setUserId(int userId);
		void setUsername(string username);
		// void setPassword(string password);
		void setPasswordHash(string passwordHash);
		void setPasswordSalt(string passwordSalt);
		void setFullName(string fullName);
		void setEmail(string email);
		void setIsAdmin(bool isAdmin);
		void setIsAutoGenPassword(bool isAutoGenPassword);

		//Methods
		User* authenticate(string username, string password);
		bool changePassword(string oldPassword, string newPassword);
		// bool updateInfo(UserInfo newInfo); //TODO
		bool requirePasswordChange(); //với mật khẩu tự sinh khi lần đầu tiên đăng nhập
};

#endif
