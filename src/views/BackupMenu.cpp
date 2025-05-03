//include file .h tuong ung voi .cpp
#include "BackupMenu.h"

//Contructors
//goi truc tiep contructor cua lop Menu
BackupMenu::BackupMenu() : Menu("Menu sao luu du lieu") {
  options = vector<string>(4); //Tao vector co 4 phan tu
  options[0] = "1. Sao luu ngay bay gio";
  options[1] = "2. Sao luu khi thoat chuong trinh"; // (hien thi trang thai dang bat/tat)";
  options[2] = "3. Xoa ban sao luu"; // (hien thi va cho chon ban sao luu muon xoa)";
  options[3] = "4. Quay ve menu truoc";
}

//Methods
void BackupMenu::display() {
  cout << endl;
  cout << "+--------------------------------+" << endl;
  cout << "       " << title << endl;
  cout << "+--------------------------------+" << endl;
  
  for (int i = 0; i < options.size(); i++) {
    cout << "   " << options[i] << endl;
  }
  cout << endl;
  cout << "> Chon mot thao tac: ";
}

void BackupMenu::handleInput() {
  cin >> selectedOption;
  cin.ignore();

  Application& app = Application::getInstance();
  if (selectedOption == "1") {
    cout << "Processing backup now..." << endl;
    //TODO: logic sao luu du lieu
  } else if (selectedOption == "2") {
    cout << "Processing backup when exit program..." << endl;
    //TODO: logic sao luu du lieu khi thoat chuong trinh
  }
  else if (selectedOption == "3") {
    cout << "Processing delete version backup..." << endl;
    //TODO: logic xoa ban sao luu du lieu
  } else if (selectedOption == "4") {
    app.setCurrentMenu("BackupRestoreMenu"); // Chuyen sang menu sao luu va khoi phuc du lieu
    return;
  } else {
    cout << "Lua chon khong hop le! Vui long chon lai" << endl;
    return;
  }
}