#include <iostream>
#include <fstream>
#include <string>

//Duong dan thu muc du lieu theo he dieu hanh
#ifdef _WIN32
  #include <windows.h>
  std::string getAbsolutePath(const std::string& relativePath) {
    wchar_t absolutePath[MAX_PATH];
    std::wstring wideRelativePath(relativePath.begin(), relativePath.end());
    GetFullPathNameW(wideRelativePath.c_str(), MAX_PATH, absolutePath, NULL);
    return std::string(absolutePath, absolutePath + wcslen(absolutePath));
  }
#else
  #include <limits.h>
  #include <unistd.h>
  #include <cstdlib>
  std::string getAbsolutePath(const std::string& relativePath) {
  char absolutePath[PATH_MAX];
    realpath(relativePath.c_str(), absolutePath);
    return std::string(absolutePath);
  }
#endif

using namespace std;

#include "./utils/HashUtils.h"

// #include "./libraries/picosha2.h"

//bien toan cuc
string DATA_DIRECTORY = getAbsolutePath("../data/");

#include "Application.h"

int main() {
  cout << endl;
  // Get the singleton instance instead of creating a new one
  Application& app = Application::getInstance();
  app.initialize();
  app.run();

  // cin.get(); //ngung chuong trinh

  return 0;
}
