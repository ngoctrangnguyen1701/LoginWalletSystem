//include file .h tuong ung voi .cpp
#include "BackupRestoreMenu.h"

//Contructors
//goi truc tiep contructor cua lop Menu
BackupRestoreMenu::BackupRestoreMenu() : Menu("Menu sao luu va khoi phuc du lieu") {
  options = vector<string>(3); // Tao vector co 3 phan tu
  options[0] = "1. Sao luu";
  options[1] = "2. Khoi phuc";
  options[2] = "3. Quay ve menu truoc";
}

//Methods
void BackupRestoreMenu::display() {
  cout << endl;
  cout << "+-------------------------------------+" << endl;
  cout << "   " << title << endl;
  cout << "+-------------------------------------+" << endl;
  
  for (int i = 0; i < options.size(); i++) {
    cout << "   " << options[i] << endl;
  }
  cout << endl;
  cout << "> Chon mot thao tac: ";
}

void BackupRestoreMenu::handleInput() {
  cin >> selectedOption;
  cin.ignore();

  Application& app = Application::getInstance();
  if (selectedOption == "1") {
    app.setCurrentMenu("BackupMenu"); // Chuyen sang menu sao luu du lieu
    return;
  } else if (selectedOption == "2") {
    cout << "Processing restore..." << endl;
    //TODO: logic khoi phuc du lieu, hien thi danh sach cac ban sao luu
  }
  else if (selectedOption == "3") {
    app.setCurrentMenu("AdminMenu"); // Chuyen sang menu danh cho admin
    return;
  } else {
    cout << "Lua chon khong hop le! Vui long chon lai" << endl;
    return;
  }
}