#ifndef BackupRestoreMenu_H //Neu chua duoc dinh nghia
#define BackupRestoreMenu_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include file header noi bo khac
#include "../Application.h"
#include "Menu.h"

class BackupRestoreMenu : public Menu
{
	private:		
	protected:
	public:
		BackupRestoreMenu();
		void display() override;
		void handleInput() override;
		void handleRestoreData();
};

#endif
