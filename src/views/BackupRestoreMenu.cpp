//include file .h tuong ung voi .cpp
#include "BackupRestoreMenu.h"

//Contructors
//goi truc tiep contructor cua lop Menu
BackupRestoreMenu::BackupRestoreMenu() : Menu("Menu sao luu va khoi phuc du lieu") {
  options = vector<string>(3);
  options[0] = "1. Sao luu";
  options[1] = "2. Khoi phuc";
  options[2] = "3. Quay ve menu truoc";
}

//Methods
void BackupRestoreMenu::display() {
  cout << endl;
  printHeader();
  
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
    handleRestoreData();
  }
  else if (selectedOption == "3") {
    app.setCurrentMenu("AdminMenu"); // Chuyen sang menu danh cho admin
    return;
  } else {
    cout << "Lua chon khong hop le! Vui long chon lai!" << endl;
    return;
  }
  backToMenu("BackupRestoreMenu"); // Chuyen sang menu sao luu va khoi phuc
}

void BackupRestoreMenu::handleRestoreData() {
  BackupManager backupMgr;
  vector<string> backupList = backupMgr.displayList();
  if (backupList.empty()) {
    return;
  }

  string backupVersion;
  cout << "> Nhap phien ban ban sao luu muon xoa: ";
  getline(cin, backupVersion);

  char choice;
  do
  {
    console.important("CANH BAO: Khoi phuc du lieu co the lam mat du lieu hien tai!");
    cout << "> Xac nhan khoi phuc phien ban '" << backupVersion << "'? (y/n): ";
    cin >> choice;
    cin.ignore();
  } while (choice != 'y' && choice != 'n');

  if(choice == 'n') {
    return;
  }
  
  bool result = backupMgr.restoreData(backupVersion);
  if(result == true) {
    console.notify("Khoi phuc du lieu thanh cong!");    
  }
  else {
    console.notify("Khoi phuc du lieu that bai!");
  }
}
