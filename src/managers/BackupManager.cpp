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

void BackupManager::generateBackupFolderName() {
  time_t now = time(NULL);
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
  directory = ss.str(); //luu ten thu muc voi dinh dang yyyyMMdd_HHmmss vao bien
}

bool BackupManager::createBackupFolder(){   
  // string directoryName = BACKUP_DIRECTORY + generateBackupFolderName();  
  string directoryName = BACKUP_DIRECTORY + directory;  
  int result = MKDIR(directoryName.c_str());
  
  //result = 0 la tao thu muc thanh cong, result = -1 la xay ra loi
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

  return result == 0 ? true : false;
}

bool BackupManager::backupData(){
  bool result = createBackupFolder();
  if(result == false) {
    return false;
  }

  console.notify("Dang thuc hien qua trinh sao luu...");

  //Sao chep file du lieu nguoi dung  
  FileUtils userFile(userMgr.filename, userMgr.filenameNextId);
  userFile.setBackupPath(directory);
  userFile.setBackupNextIdPath(directory);
  bool resultUser = userFile.copyFile();
  if(resultUser == false) {
    console.notify("Sao luu that bai du lieu nguoi dung!");
    return false;
  }
  console.notify("Sao luu thanh cong du lieu nguoi dung!");


  //Sao chep file du lieu vi  
  FileUtils walletFile(walletMgr.filename, walletMgr.filenameNextId);
  walletFile.setBackupPath(directory);
  walletFile.setBackupNextIdPath(directory);
  bool resultWallet = walletFile.copyFile();
  if(resultWallet == false) {
    console.notify("Sao luu that bai du lieu vi!");
    return false;
  }
  console.notify("Sao luu thanh cong du lieu vi!");


  //Sao chep file du lieu nguoi dung  
  FileUtils transactionFile(transactionMgr.filename, transactionMgr.filenameNextId);
  transactionFile.setBackupPath(directory);
  transactionFile.setBackupNextIdPath(directory);
  bool resultTransaction = transactionFile.copyFile();
  if(resultTransaction == false) {
    console.notify("Sao luu that bai du lieu lich su giao dich!");
    return false;
  }
  console.notify("Sao luu thanh cong du lieu lich su giao dich!");

  console.notify("Hoan tat sao luu!");
}

bool BackupManager::restoreData(){
  return false;
}

bool BackupManager::deleteBackupData(string backupVersion){
  return false;
}
