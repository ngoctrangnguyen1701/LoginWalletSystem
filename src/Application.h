#ifndef Application_H //Neu chua duoc dinh nghia
#define Application_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien
#include <iostream>
#include <string>

//include file header noi bo khac
#include "./models/User.h"
#include "./views/Menu.h"
#include "./views/LoginMenu.h"
#include "./views/UserMenu.h"
#include "./views/AdminMenu.h"
#include "./views/MasterWalletMenu.h"
#include "./views/UserWalletMenu.h"
#include "./views/CreateWalletMenu.h"
#include "./views/AdminTransactionMenu.h"
#include "./managers/UserManager.h"
#include "./managers/WalletManager.h"
#include "./managers/TransactionManager.h"
#include "./utils/ConsoleUtils.h"

using namespace std;

class Application
{
	private:
		User* currentUser = NULL; // Con tro tro den nguoi dung hien tai dang su dung he thong (neu co)
		Menu* currentMenu = NULL;  // Con tro tro den menu hien tai		
		UserManager userMgr; // Khai bao doi tuong UserManager
		WalletManager walletMgr; // Khai bao doi tuong WalletManager
		TransactionManager transactionMgr; // Khai bao doi tuong TransactionManager
		ConsoleUtils console; // Khai bao doi tuong ConsoleUtils
	public:
		//Destructor
		~Application();
		
		//Getters
		User* getCurrentUser();
		Menu* getCurrentMenu(); 
		UserManager getUserMgr();	
		WalletManager getWalletMgr();
		TransactionManager getTransactionMgr();
		ConsoleUtils getConsole();	

		//Setters
		void setCurrentMenu(string menuName);

		//Methods
		static Application& getInstance();
		void initialize();
		void login();
		bool signup();
		bool logout();
		void run();
};

#endif
