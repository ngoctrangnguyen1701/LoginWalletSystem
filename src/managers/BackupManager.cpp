//include file .h tuong ung voi .cpp
#include "BackupManager.h"

//Contructors
//BackupManager::BackupManager(){}

// backup/
// └── 20250101_12:00:00/
//         └── userData_backup.csv
//         └── nextUserId_backup.txt
//         └── walletData_backup.csv
//         └── nextWalletId_backup.txt
//         └── transactionData_backup.csv
//         └── nextTransactionId_backup.txt

//Methods
string BackupManager::generateBackupFileName(){
  return "";
}

string BackupManager::generateBackupFolderName() {
  time_t now = time(NULL);
  cout << "now: " << now << "\n";
  tm* local_time = localtime(&now);
  int year = 1900 + local_time->tm_year;
  int month = 1 + local_time->tm_mon;
  int day = local_time->tm_mday;
  int hour = local_time->tm_hour;
  int minute = local_time->tm_min;
  int second = local_time->tm_sec;
  stringstream ss;
  ss << year;
  //Them so 0 vao truoc neu thang, ngay, gio, phut, giay nho hon 10
  ss << (month < 10 ? "0" : "") << month;
  ss << (day < 10 ? "0" : "") << day;
  ss << "_"; //them dau "_" giua ngay va gio
  ss << (hour < 10 ? "0" : "") << hour;
  ss << (minute < 10 ? "0" : "") << minute;
  ss << (second < 10 ? "0" : "") << second;
  return ss.str(); //tra ve chuoi dang yyyyMMdd_HHmmss
}

bool BackupManager::createBackupFolder(){   
  string directoryName = BACKUP_DIRECTORY + generateBackupFolderName();  
  int result = MKDIR(directoryName.c_str());
  
  if (result == 0) {
    console.log("Da tao thu muc '" + directoryName + "'");
  } else {
    console.log("Khong the tao thu muc '" + directoryName + "'");
    
    #ifdef _WIN32
      cerr << "Ma loi: " << errno << endl;
    #else
      cerr << "Ma loi: " << errno << " - " << strerror(errno) << endl;
    #endif
  }

  return false;
}

bool BackupManager::backupData(){
  bool result = createBackupFolder();
  return false;
}

bool BackupManager::restoreData(){
  return false;
}

bool BackupManager::deleteBackupData(string backupVersion){
  return false;
}
