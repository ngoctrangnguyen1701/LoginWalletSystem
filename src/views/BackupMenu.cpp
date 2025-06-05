//include file .h tuong ung voi .cpp
#include "BackupMenu.h"

//Contructors
//goi truc tiep contructor cua lop Menu
BackupMenu::BackupMenu() : Menu("Menu sao luu du lieu") {
  Application& app = Application::getInstance();
  bool isBackupDataWhenExit = app.getIsBackupDataWhenExit();

  options = vector<string>(3);
  options[0] = "1. Sao luu ngay bay gio";
  options[1] = "2. Sao luu khi thoat chuong trinh";
  // options[2] = "3. Xoa ban sao luu"; // (hien thi va cho chon ban sao luu muon xoa)";
  options[2] = "4. Quay ve menu truoc"; 
}

//Methods
void BackupMenu::display() {
  cout << endl;
  cout << "+--------------------------------+" << endl;
  cout << "       " << title << endl;
  cout << "+--------------------------------+" << endl;
  
  for (int i = 0; i < options.size(); i++) {
    cout << "   " << i + 1 << ". " << options[i] << endl;
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
  // } else if (selectedOption == "3") {
    // handleRemoveBackupData();
  } else if (selectedOption == "3") {
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

  string onOrOff = isBackupDataWhenExit ? "BAT" : "TAT";
  string reverseOnOrOff = !isBackupDataWhenExit ? "BAT" : "TAT";
  cout << "Chuong trinh dang '" << onOrOff << "' tinh nang sao luu khi thoat chuong trinh." << endl;
  string text = "> Ban co muon '" + reverseOnOrOff + "' tinh nang nay? (y/n): ";
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
    string text_2 = "Da '" + reverseOnOrOff + "' sao luu khi thoat chuong trinh!";
    cout << text_2 << endl;
  }
}

// void BackupMenu::handleRemoveBackupData() {
//   BackupManager backupMgr;
//   vector<string> backupList = backupMgr.displayList();
//   if (backupList.empty()) {
//     return;
//   }

//   string backupVersion;
//   cout << "> Chon phien ban ban sao luu muon xoa: ";
//   getline(cin, backupVersion);

//   char choice;
//   do
//   {
//     cout << "> Xac nhan xoa phien ban '" << backupVersion << "'? (y/n): ";
//     cin >> choice;
//     cin.ignore();
//   } while (choice != 'y' && choice != 'n');

//   if(choice == 'y') {
//     bool result = backupMgr.deleteBackupData(backupVersion);
//     if(result == true) {
//       console.notify("Xoa ban sao luu thanh cong!");
//     }
//     else {
//       console.notify("Xoa ban sao luu that bai!");
//     }    
//   }
  
// }
