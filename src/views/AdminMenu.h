#ifndef AdminMenu_H //Neu chua duoc dinh nghia
#define AdminMenu_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien
#include <iostream>
#include <string>

//include file header noi bo khac
#include "../Application.h"
#include "Menu.h"
#include "../models/User.h"

using namespace std;

class AdminMenu : public Menu
{
	private:
		bool isReloadMenu = false;
	protected:
	public:
		AdminMenu();
		void display() override;
		void handleInput() override;
		void handleReadUserList();
		void handleCreateUser();
		void handleUpdateUser();
		void handleDeleteUser();
		void handleReadWalletList();
		void handleBeforeLogout();
};

#endif
