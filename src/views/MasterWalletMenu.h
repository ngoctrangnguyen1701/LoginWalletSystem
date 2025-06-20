#ifndef MasterWalletMenu_H //Neu chua duoc dinh nghia
#define MasterWalletMenu_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien


//include file header noi bo khac
#include "Menu.h"
#include "../Application.h"
#include "../utils/Utils.h"
#include "../models/MasterWallet.h"

class MasterWalletMenu : public Menu
{
	private:		
	protected:
	public:		
		MasterWalletMenu();
		void display() override;
		void handleInput() override;
		void handleDeposit();
		void handleWithdraw();
		void handleCheckBalance();
		void handleDisplayTransaction();
		bool checkValidDecrement(int amount);
};

#endif
