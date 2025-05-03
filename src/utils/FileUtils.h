#ifndef FileUtils_H //Neu chua duoc dinh nghia
#define FileUtils_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>

//include file header noi bo khac
#include "../utils/ConsoleUtils.h"

using namespace std;

// Khai bao bien toan cuc tu file main.cpp
extern string DATA_DIRECTORY;

class FileUtils {
  private:
    string filename;
    string fullPath;
    string nextIdFilePath;
    string tempFilePath;
		ConsoleUtils console; // Khai bao doi tuong ConsoleUtils
  public:
    // Constructors
    FileUtils(const string& filename, const string& filenameNextId);
    
    // Methods
    bool isEmptyFile();
    bool createFile();
    
    // Template methods    
    template <typename T, typename M>
    bool saveDataByList(M &classManager, vector<T> data, int nextId);
    
    template <typename T, typename M>
    bool loadFile(M &classManager, vector<T> &data, int &nextId);
    
    template <typename T, typename M>
    bool appendItem(M &classManager, const T& item, int nextId);
};

// Include the implementation file at the end of the header
#include "FileUtils.tpp"

#endif
