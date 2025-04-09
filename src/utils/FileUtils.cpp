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
  try {
    //Tao file data
    ofstream file(fullPath);
    file.exceptions(ios::failbit | ios::badbit);     
    file.close();
    cout << "Da tao file '" << fullPath << "'" << endl;

    // Tao file nextId
    ofstream nextIdFile(nextIdFilePath);
    nextIdFile.exceptions(ios::failbit | ios::badbit);
    nextIdFile.close();
    cout << "Da tao file '" << nextIdFilePath << "'" << endl;
    return true;    
  } catch(const exception& e) {
    cerr << "File processing error: " << e.what() << endl;
    cerr << "System error info: " << strerror(errno) 
         << " (Error code: " << errno << ")" << endl;
    exit(1); //Thoat chuong trinh
    return false;
  }
}
