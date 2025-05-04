#ifndef BackupMenu_H //Neu chua duoc dinh nghia
#define BackupMenu_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include file header noi bo khac
#include "../Application.h"
#include "Menu.h"
#include "../managers/BackupManager.h"

class BackupMenu : public Menu
{
	private:		
	protected:
	public:
		BackupMenu();
		void display() override;
		void handleInput() override;
		void handleBackupNow(); //Ham xu ly sao luu du lieu ngay thoi diem hien tai
		void handleBackupWhenExitProgram(); //Ham xu ly sao luu du lieu khi thoat chuong trinh
};

#endif
