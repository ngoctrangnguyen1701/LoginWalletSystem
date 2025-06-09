#ifndef MasterWalletMenu_H //Neu chua duoc dinh nghia
#define MasterWalletMenu_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien


//include file header noi bo khac
#include "Menu.h"
#include "../Application.h"

class MasterWalletMenu : public Menu
{
	private:		
	protected:
	public:		
		MasterWalletMenu();
		void display() override;
		void handleInput() override;
		void handleDeposit();
};

#endif
