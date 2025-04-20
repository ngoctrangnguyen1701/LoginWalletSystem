#ifndef CreateWalletMenu_H //Neu chua duoc dinh nghia
#define CreateWalletMenu_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien


//include file header noi bo khac
#include "Menu.h"
#include "../Application.h"

class CreateWalletMenu : public Menu
{
	private:		
	protected:
	public:		
		CreateWalletMenu();
		void display() override;
		void handleInput() override;
};

#endif
