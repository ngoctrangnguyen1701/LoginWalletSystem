//include thu vien
#include <iostream>
#include <fstream>

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
  try {
    //Kiem tra file co ton tai
    ifstream file(fullPath);
    if (!file.is_open()) {
      cerr << "Khong ton tai file '" << fullPath << "'" << endl;
      file.close();
      return FileUtils::createFile();
    }
    
    // Kiểm tra kích thước file
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
  catch(const std::exception& e) {
    cerr << "Error: " << e.what() << endl;
    exit(1); // Thoat chuong trinh neu co loi
  }
}

bool FileUtils::createFile() {
  try {
    ofstream file(fullPath);
    if (!file.is_open()) {
      cerr << "Khong the tao file '" << fullPath << "'" << endl;
      file.close();
      exit(1); // Thoat chuong trinh neu co loi
      return false; 
    }        
    file.close();
    cout << "Da tao file '" << fullPath << "'" << endl;

    // Tao file nextId
    ofstream nextIdFile(nextIdFilePath);
    if(!nextIdFile.is_open()) {
      cerr << "Khong the tao file '" << nextIdFilePath << "'" << endl;
      nextIdFile.close();
      exit(1); // Thoat chuong trinh neu co loi
      return false; 
    }    

    return true;
  } catch(const exception& e) {
    cerr << "Error: " << e.what() << endl;        
    exit(1);
    return false;
  }
}
