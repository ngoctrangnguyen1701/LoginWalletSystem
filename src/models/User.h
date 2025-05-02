#ifndef User_H //Neu chua duoc dinh nghia
#define User_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien
#include <string>
#include <cstdlib>
#include <ctime> 

//include file header noi bo khac
#include "../utils/ConsoleUtils.h"

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
		string password; //(hash) //(unique) //TODO
		string fullName;
		string email;
		bool isAdmin;
		bool isAutoGenPassword;
		// DateTime createdAt; //TODO
		ConsoleUtils console; // Khai bao doi tuong ConsoleUtils
	protected:
	public:
		// Constructor
		User() = default;
		User(string username, string password, string fullName, string email, bool isAdmin = false, bool isAutoGenPassword = false); 

		//Destructor
		~User(); 

		//Getters 
		int getUserId();
		string getUsername();
		string getPassword();
		string getFullName();
		string getEmail();
		bool getIsAdmin();
		bool getIsAutoGenPassword();

		//Setters
		void setUserId(int userId);
		void setUsername(string username);
		void setPassword(string password);
		void setFullName(string fullName);
		void setEmail(string email);
		void setIsAdmin(bool isAdmin);
		void setIsAutoGenPassword(bool isAutoGenPassword);

		//Methods
		User* authenticate(string username, string password);
		bool changePassword(string oldPassword, string newPassword);
		// bool updateInfo(UserInfo newInfo); //TODO
		bool requirePasswordChange(); // voi mat khau tu sinh khi lan dau tien dang nhap
		string autoGeneratePassword(); //Ham tao mat khau tu sinh
		bool checkIsValidPassword(string password); //Ham kiem tra mat khau co hop le hay khong
};

#endif
