#ifndef UserWalletMenu_H //Neu chua duoc dinh nghia
#define UserWalletMenu_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien


//include file header noi bo khac
#include "Menu.h"
#include "../Application.h"
#include "../models/UserWallet.h"

class UserWalletMenu : public Menu
{
	private:		
	protected:
	public:		
		UserWalletMenu();
		void display() override;
		void handleInput() override;
		void handleDeposit();
		void handleWithdraw();
};

#endif
