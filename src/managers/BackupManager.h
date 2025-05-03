#ifndef BackupManager_H //Neu chua duoc dinh nghia
#define BackupManager_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>

//include file header noi bo khac
#include "../utils/ConsoleUtils.h"

using namespace std;

// Khai bao bien toan cuc tu file main.cpp
extern string BACKUP_DIRECTORY;

#ifdef _WIN32
	#include <direct.h>    // _mkdir tren Windows
	#define MKDIR(dir) _mkdir(dir)
#else
	#include <sys/stat.h>  // mkdir tren Linux/macOS
	#include <errno.h>
	#define MKDIR(dir) mkdir(dir, 0755)
#endif

class BackupManager
{
	private:
		vector<string> fileList;
		string directory;
		string createdDate; //format theo yyyy/mm/dd hh:mm:ss
		ConsoleUtils console; // Khai bao doi tuong ConsoleUtils
	protected:
	public:
		string generateBackupFileName(); //Ham tao ten file sao luu
		string generateBackupFolderName(); //Ham tao ten thu muc sao luu
		bool createBackupFolder(); //Ham tao thu muc sao luu
		bool backupData(); //Ham sao luu tat ca cac file du lieu
		bool restoreData(); //Ham khoi phuc tat ca du lieu trong cac file sao luu
		bool deleteBackupData(string backupVersion); //xoa phien ban cua ban sao luu nao do
};

#endif
