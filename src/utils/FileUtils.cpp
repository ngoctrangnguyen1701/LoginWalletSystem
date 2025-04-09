//include thu vien
#include <iostream>
#include <fstream>
#include <cerrno>   // For errno
#include <cstring>  // For strerror

//include file tu dinh nghia
#include "FileUtils.h"

using namespace std;

// Constructors
FileUtils::FileUtils(const string& filename, const string& filenameNextId) {
  this->filename = filename;
  fullPath = DATA_DIRECTORY + filename + ".csv";
  nextIdFilePath = DATA_DIRECTORY + filenameNextId + ".txt";
  tempFilePath = DATA_DIRECTORY + "temp_" + filename + ".csv";
}

//Methods
bool FileUtils::isEmptyFile() {
  //Kiem tra file co ton tai
  ifstream file(fullPath);
  if (!file.is_open()) {
    cerr << "Khong ton tai file '" << fullPath << "'" << endl;
    file.close();
    return FileUtils::createFile();
  }
  
  //Kiem tra kich thuoc file
  file.seekg(0, ios::end);
  streampos fileSize = file.tellg();                
  //Truong hop file bi loi, khong doc duoc
  if (fileSize == -1 || file.fail()) {
    cerr << "Khong the xac dinh kich thuoc file '" << fullPath << "'" << endl;
    cerr << "Co the file bi loi" << endl;
    file.close();
    return FileUtils::createFile();
  }
  
  if (fileSize == 0) {
    cerr << "Chua co du lieu trong file '" << fullPath << "'" << endl;
    file.close();
    return FileUtils::createFile();
  }
  
  file.close();
  return false; // File ton tai va khong rong
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
  cout << "Da tao file '" << fullPath << "'" << endl;

  // Tao file nextId
  ofstream nextIdFile(nextIdFilePath);
  if (!nextIdFile.is_open()) {
    cerr << "Khong the tao file '" << nextIdFilePath << endl;
    exit(1);
    return false;
  }
  nextIdFile.close();
  cout << "Da tao file '" << nextIdFilePath << "'" << endl;
  return true;
}
