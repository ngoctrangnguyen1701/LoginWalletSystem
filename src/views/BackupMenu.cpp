//include file .h tuong ung voi .cpp
#include "BackupMenu.h"

//Contructors
//goi truc tiep contructor cua lop Menu
BackupMenu::BackupMenu() : Menu("Menu sao luu du lieu") {
  Application& app = Application::getInstance();
  bool isBackupDataWhenExit = app.getIsBackupDataWhenExit();

  options = vector<string>(4); //Tao vector co 4 phan tu  
  options[0] = "1. Sao luu ngay bay gio";
  string onOrOff = isBackupDataWhenExit ? "TAT" : "BAT";
  options[1] = "2. " + onOrOff + " sao luu khi thoat chuong trinh"; 
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
    handleBackupNow();
  } else if (selectedOption == "2") {
    handleBackupWhenExitProgram();
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

  char choice;
  do
  {
    cout << "> Quay tro ve menu? (y): ";
    cin >> choice;
    cin.ignore();
  } while (choice != 'y');
  app.setCurrentMenu("BackupMenu"); // Chuyen sang menu sao luu du lieu
}

void BackupMenu::handleBackupNow() {
  BackupManager backupMgr;
  bool result = backupMgr.backupData();
  if(result == true) {
    console.notify("Sao luu du lieu thanh cong!");
  }
  else {
    console.notify("Sao luu du lieu that bai!");
  }
}

void BackupMenu::handleBackupWhenExitProgram() {
  //Neu dang bat thi chuyen sang tat va nguoc lai
  Application& app = Application::getInstance();
  bool isBackupDataWhenExit = app.getIsBackupDataWhenExit();

  string onOrOff = isBackupDataWhenExit ? "TAT" : "BAT";
  string text = "> Xac nhan " + onOrOff + " sao luu khi thoat chuong trinh? (y/n): ";
  char choice;
  do
  {
    cout << text;
    cin >> choice;
    cin.ignore();
  } while (choice != 'y' && choice != 'n');

  if(choice == 'y') {
    if(isBackupDataWhenExit == true) {
      app.setIsBackupDataWhenExit(false);      
    }
    else {
      app.setIsBackupDataWhenExit(true);
    }
    string text_2 = "Da " + onOrOff + " sao luu khi thoat chuong trinh!";
    cout << text_2 << endl;
  }
}