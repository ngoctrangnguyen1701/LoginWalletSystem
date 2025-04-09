#ifndef Application_H //Neu chua duoc dinh nghia
#define Application_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include file tu dinh nghia
#include "./views/Menu.h"
#include "./managers/UserManager.h"
// #include "WalletManger.h"
// #include "TransactionManger.h"
#include "./utils/ConsoleUtils.h"

class Application
{
	private:
		User* currentUser = NULL; // Con tro tro den nguoi dung hien tai (neu co)
		Menu* currentMenu = NULL;  // Con tro tro den menu hien tai		
		UserManager userMgr; // Khai bao doi tuong UserManager
		ConsoleUtils console; // Khai bao doi tuong ConsoleUtils
	public:
		//Destructor
		~Application();
		
		//Getters
		User* getCurrentUser();
		Menu* getCurrentMenu();
		UserManager getUserMgr();	
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
