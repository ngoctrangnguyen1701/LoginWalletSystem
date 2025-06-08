//include file .h tuong ung voi .cpp
#include "BackupManager.h"
//#include <algorithm>

//Contructors
//BackupManager::BackupManager(){}


//Methods
string BackupManager::generateBackupFileName(){
  return "";
}

string BackupManager::generateBackupFolderName() {
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
  return ss.str();
}

bool BackupManager::createBackupFolder(){   
  string directoryPath = BACKUP_DIRECTORY + generateBackupFolderName();
  int result = MKDIR(directoryPath.c_str());
  
  //result = 0 la tao thu muc thanh cong, result = -1 la xay ra loi
  if (result == 0) {
    console.log("Da tao thu muc '" + directoryPath + "'");
  } else {
    console.log("Khong the tao thu muc '" + directoryPath + "'");
    
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

  //Sao luu file du lieu nguoi dung  
  bool resultUser = processBackupData(userMgr.filename, userMgr.filenameNextId, "du lieu nguoi dung");
  if(resultUser == false) {
    return false;
  }

  //Sao luu file du lieu vi 
  bool resulWallet = processBackupData(walletMgr.filename, walletMgr.filenameNextId, "du lieu vi");
  if(resulWallet == false) {
    return false;
  }

  //Sao luu file du lieu lich su giao dich
  bool resulTransaction = processBackupData(transactionMgr.filename, transactionMgr.filenameNextId, "du lieu lich su giao dich");
  if(resulTransaction == false) {
    return false;
  }
  console.notify("Hoan tat sao luu!");
  return true;
}

bool BackupManager::processBackupData(string filename, string filenameNextId, string title){
  FileUtils fileUtils(filename, filenameNextId);
  fileUtils.setBackupPath(directory);
  fileUtils.setBackupNextIdPath(directory);

  //tao file sao luu truoc khi sao chep
  fileUtils.createFileWithPath(fileUtils.getBackupPath());
  fileUtils.createFileWithPath(fileUtils.getBackupNextIdPath());

  bool result = fileUtils.copyFile();
  if(result == false) {
    console.notify("Sao luu that bai " + title + "!");
    return false;
  }
  console.notify("Sao luu thanh cong " + title + "!");
  return true;
};

bool BackupManager::restoreData(string backupVersion){
  //Kiem tra xem phien ban sao luu co ton tai
  string* backupVersionPtr = findBackupVersion(backupVersion);
  if(backupVersionPtr == NULL) {
    console.notify("Khong tim thay phien ban sao luu '" + backupVersion + "'");
    return false;
  }

  console.notify("Dang thuc hien qua trinh khoi phuc...");

  //Khoi phuc file du lieu nguoi dung 
  string title = "du lieu nguoi dung";
  bool resultUser = processRestoreData(userMgr.filename, userMgr.filenameNextId, backupVersion);
  if(resultUser == false) {
    console.notify("Khoi phuc that bai " + title + "!");
    return false;
  }
  console.notify("Khoi phuc thanh cong " + title + "!");

  //Khoi phuc file du lieu vi
  title = "du lieu vi";
  bool resulWallet = processRestoreData(walletMgr.filename, walletMgr.filenameNextId, backupVersion);
  if(resulWallet == false) {
    console.notify("Khoi phuc that bai " + title + "!");
    return false;
  }
  console.notify("Khoi phuc thanh cong " + title + "!");

  //Khoi phuc file du lieu lich su giao dich
  title = "du lieu lich su giao dich";
  bool resulTransaction = processRestoreData(transactionMgr.filename, transactionMgr.filenameNextId, backupVersion);
  if(resulTransaction == false) {
    console.notify("Khoi phuc that bai " + title + "!");
    return false;
  }
  console.notify("Khoi phuc thanh cong " + title + "!");

  console.notify("Hoan tat khoi phuc!");
  return true;
}

bool BackupManager::processRestoreData(string filename, string filenameNextId,string backupVersion) {
  //Tao 1 file moi trong thu muc data
  //Sao chep du lieu cho file moi tu file backup
  //Xoa file du lieu hien tai
  //Doi ten file moi thanh ten file hien tai

  FileUtils fileUtils(filename, filenameNextId);
  fileUtils.setBackupPath(backupVersion);
  fileUtils.setBackupNextIdPath(backupVersion);

  string tempFile = fileUtils.getTempFilePath();
  string tempNextIdFile = fileUtils.getTempNextIdFilePath();
  string backupFile = fileUtils.getBackupPath();
  string backupNextIdFile = fileUtils.getBackupNextIdPath();
  string dataFile = fileUtils.getFullPath();
  string nextIdFile = fileUtils.getNextIdFilePath();

  //Tao file moi de sao chep du lieu
  bool resultCreate = fileUtils.createFileWithPath(tempFile);
  if(resultCreate == false) {
    return false;
  }
  resultCreate = fileUtils.createFileWithPath(tempNextIdFile);
  if(resultCreate == false) {
    return false;
  }

  //Sao chep du lieu tu file backup sang file moi
  bool resultCopy = fileUtils.copyFileWithPath(backupFile, tempFile);
  if(resultCopy == false) {
    return false;
  }
  resultCopy = fileUtils.copyFileWithPath(backupNextIdFile, tempNextIdFile);
  if(resultCopy == false) {
    return false;
  }

  //Xoa file du lieu hien tai
  bool resultRemove = fileUtils.removeFileWithPath(dataFile);
  if(resultRemove == false) {
    return false;
  }
  resultRemove = fileUtils.removeFileWithPath(nextIdFile);
  if(resultRemove == false) {
    return false;
  }

  //Doi ten file moi thanh ten file hien tai
  bool resultRename = fileUtils.renameFileWithPath(tempFile, dataFile);
  if(resultRename == false) {
    return false;
  }
  resultRename = fileUtils.renameFileWithPath(tempNextIdFile, nextIdFile);
  if(resultRename == false) {
    return false;
  }
  return true; 
}

bool BackupManager::deleteBackupData(string backupVersion){
  return false;
}

bool BackupManager::getList() {
  string path = BACKUP_DIRECTORY;
  #ifdef _WIN32
    string searchPath = path + "\\*";
    WIN32_FIND_DATAA fd;
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &fd);

    if (hFind != INVALID_HANDLE_VALUE) {
      do {
        string name = fd.cFileName;
        if ((fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
          name != "." && name != "..") {
          backupList.push_back(name);
        }
      } while (FindNextFileA(hFind, &fd));
      FindClose(hFind);
    }
  #else
    DIR* dir = opendir(path.c_str());
    if (dir) {
      struct dirent* entry;
      while ((entry = readdir(dir)) != NULL) {
        string name = entry->d_name;
        if (entry->d_type == DT_DIR && name != "." && name != "..") {
          cout << name << endl;
          backupList.push_back(name);
        }
      }
      closedir(dir);
    }
  #endif
  return true;
}

vector<string> BackupManager::displayList() {
  bool resultGetList = getList(); 
  if(resultGetList == false) {
    console.notify("Khong the doc danh sach sao luu");
    return backupList;
  }
  // Check if list is empty
  if (backupList.empty()) {
    cout << "\n===== Danh sach sao luu dang trong =====\n";    
  } else {
    cout << "\n===== Danh sach sao luu =====\n";
    for (int i = 0; i < backupList.size(); i++) {      
      cout << i + 1 << ". "<< backupList[i] << endl;
    }
    cout << endl;
    cout << "Tong so ban sao luu: " << backupList.size() << endl;
  }
  return backupList;
}

string* BackupManager::findBackupVersion(string backupVersion) {
  bool resultGetList = getList(); 
  if(resultGetList == false) {
    console.notify("Khong the doc danh sach sao luu");
    return NULL;
  }
  for (int i = 0; i < backupList.size(); i++) {
    if (backupList[i] == backupVersion) {
      return &backupList[i]; // Tra ve con tro den phien ban sao luu tim thay
    }
  }
  return NULL;
}
