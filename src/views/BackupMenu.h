#ifndef BackupMenu_H //Neu chua duoc dinh nghia
#define BackupMenu_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include file header noi bo khac
#include "../Application.h"
#include "Menu.h"
#include "../managers/BackupManager.h"

// Khai bao bien toan cuc tu file main.cpp
extern string DATA_DIRECTORY;

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
		// void handleRemoveBackupData(); //Ham xu ly xoa du lieu sao luu
};

#endif
