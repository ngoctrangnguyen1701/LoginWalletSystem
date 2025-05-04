//include file .h tuong ung voi .cpp
#include "FileUtils.h"

//include thu vien
#include <iostream>
#include <string>
#include <fstream>
#include <cerrno>   // For errno
#include <cstring>  // For strerror

//include file header noi bo khac
//...

using namespace std;

// Constructors
FileUtils::FileUtils(const string& filename, const string& filenameNextId) {
  this->filename = filename;
  this->filenameNextId = filenameNextId;
  fullPath = DATA_DIRECTORY + filename + ".csv";
  nextIdFilePath = DATA_DIRECTORY + filenameNextId + ".txt";
  tempFilePath = DATA_DIRECTORY + "temp_" + filename + ".csv";
}

//Setters
void FileUtils::setBackupPath(string backupFolderName){
  backupPath = BACKUP_DIRECTORY + backupFolderName + "/backup_" + filename + ".csv";
};

void FileUtils::setBackupNextIdPath(string backupFolderName){
  backupNextIdPath = BACKUP_DIRECTORY + backupFolderName + "/backup_" + filenameNextId + ".txt";
};

//Getters
string FileUtils::getBackupPath(){
  return backupPath;
};

string FileUtils::getBackupNextIdPath(){
  return backupNextIdPath;
};

//Methods
bool FileUtils::isExistFileWithPath(string path) {
  fstream file(path);
  if(!file.is_open()) {
    file.close();
    return false;
  }
  file.close();
  return true;
}

bool FileUtils::isEmptyFile() {
  //Kiem tra file co ton tai
  ifstream file(fullPath);
  if (!file.is_open()) {
    string text = "Khong ton tai file '" + fullPath;
    console.log(text);
    file.close();
    return FileUtils::createFile();
  }
  
  //Kiem tra kich thuoc file
  file.seekg(0, ios::end);
  streampos fileSize = file.tellg();                
  //Truong hop file bi loi, khong doc duoc
  if (fileSize == -1 || file.fail()) {
    string text = "Co the file bi loi, khong the xac dinh kich thuoc file '" + fullPath;
    console.log(text);
    file.close();
    return FileUtils::createFile();
  }
  
  if (fileSize == 0) {
    string text = "Chua co du lieu trong file '" + fullPath;
    console.log(text);
    file.close();
    return FileUtils::createFile();
  }
  
  file.close();
  return false; // File ton tai va khong rong
}

bool FileUtils::isEmptyFileWithPath(string path) {
  //Kiem tra kich thuoc file
  fstream file(path);
  file.seekg(0, ios::end);
  streampos fileSize = file.tellg();                
  //Truong hop file bi loi, khong doc duoc
  if (fileSize == -1 || file.fail()) {
    string text = "Co the file bi loi, khong the xac dinh kich thuoc file '" + path;
    console.log(text);
    file.close();
    return false;
  }
  
  if (fileSize != 0) {
    file.close();
    return false;
  }

  return true; // File ton tai va khong rong
}

bool FileUtils::createFile() {
  //Tao file data
  ofstream file(fullPath);
  if (!file.is_open()) {
    cerr << "Khong the tao file '" << fullPath << endl;           
    exit(1);
    return false;
  }
  file.close();
  string text = "Da tao file '" + fullPath + "'";
  console.log(text);

  // Tao file nextId
  ofstream nextIdFile(nextIdFilePath);
  if (!nextIdFile.is_open()) {
    cerr << "Khong the tao file '" << nextIdFilePath << endl;
    exit(1);
    return false;
  }
  nextIdFile.close();
  text = "Da tao file '" + nextIdFilePath + "'";
  console.log(text);
  return true;
}

bool FileUtils::createFileWithPath(string path) {
  //Kiem tra file co ton tai
  if(isExistFileWithPath(path) == true) {
    string text = "Da ton tai file '" + path;
    console.log(text);
    return false;
  }

  //Tao file voi duong dan tuong ung, ofstream khong tim thay file se tu dong tao file
  ofstream file(path);
  if (!file.is_open()) {
    cerr << "Khong the tao file '" << path << endl;           
    exit(1);
    return false;
  }
  file.close();
  string text = "Da tao file '" + path + "'";
  console.log(text);

  return true;
}

bool FileUtils::copyFile() {
  //Sao chep file du lieu
  bool result = copyFileWithPath(fullPath, backupPath);
  if(result == false) {
    return false;
  }

  //Sao chep file nextId
  result = copyFileWithPath(nextIdFilePath, backupNextIdPath);
  if(result == false) {
    return false;
  }
  return true;
}

bool FileUtils::copyFileWithPath(string sourceFilePath, string destinationFilePath) {
  //Dam bao ca file nguon va file dich ton tai, va file dich chua co du lieu
  //Mo file de doc (file nguon), kiem tra file nguon co ton tai
  //Mo file de sao chep (file dich), kiem tra file dich co ton tai
  //Thuc hien sao chep tung dong du lieu tu file nguon sang file dich
  //Dong file nguon va file dich

  //Kiem tra file nguon co ton tai
  if(isExistFileWithPath(sourceFilePath) == false) {
    string text = "Khong ton tai file '" + sourceFilePath;
    console.log(text);
    return false;
  }

  // kiem tra file dich co ton tai
  if(isExistFileWithPath(destinationFilePath) == false) {
    string text = "Khong ton tai file '" + destinationFilePath;
    console.log(text);
    return false;
  }

  //Kiem tra file dich dang co du lieu hay khong
  if(!isEmptyFileWithPath(destinationFilePath)) {
    string text = "Sao chep se lam mat du lieu hien co trong file '" + destinationFilePath;
    console.notify(text);
    return false;
  }
    
  
  //Thuc hien sao chep tung dong du lieu tu file nguon sang file dich
  console.log("Dang thuc hien sao chep file '" + sourceFilePath + "' sang file '" + destinationFilePath + "'...");
  ifstream sourceFile(sourceFilePath);
  ofstream destinationFile(destinationFilePath);

  string line;
  while (getline(sourceFile, line)) {
    destinationFile << line << '\n';
  }

  console.log("Da sao chep thanh cong file '" + sourceFilePath + "' sang file '" + destinationFilePath);
  return true;
}
