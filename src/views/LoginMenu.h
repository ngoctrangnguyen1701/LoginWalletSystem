#ifndef LoginMenu_H //Neu chua duoc dinh nghia
#define LoginMenu_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include file header noi bo khac
#include "Menu.h"

//include thu vien
#include <iostream>
#include <string>

using namespace std;

class LoginMenu : public Menu
{
	private:		
		// int loginAttempts = 0; // So lan dang nhap sai
		// const int maxLoginAttempts = 3; // So lan dang nhap toi da, dang nhap sai 3 lan se thoat chuong trinh
	protected:
	public:
		LoginMenu();
		void display() override;
		void handleInput() override;
		void handleLogin();
		void handleSignup();
		bool checkIsExistUsername(string username);
};

#endif
