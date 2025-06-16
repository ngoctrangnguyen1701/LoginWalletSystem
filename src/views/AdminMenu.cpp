//include file .h tuong ung voi .cpp
#include "AdminMenu.h"

//Contructors
//goi truc tiep contructor cua lop Menu
AdminMenu::AdminMenu() : Menu("Menu danh cho Admin") {
  options = vector<string>(7);
  options[0] = "1. Doc danh sach nguoi dung";
  // options[1] = "2. Tim kiem nguoi dung";
  options[1] = "2. Them nguoi dung";
  options[2] = "3. Thay doi thong tin nguoi dung";
  // options[4] = "5. Xoa nguoi dung";
  options[3] = "4. Doc danh sach vi";
  options[4] = "5. Vi tong";
  options[5] = "6. Sao luu va khoi phuc du lieu";
  options[6] = "7. Dang xuat";
}

//Methods
void AdminMenu::display() {
  cout << endl;
  printHeader();
  
  for (int i = 0; i < options.size(); i++) {
    cout << "   " << options[i] << endl;
  }
  cout << endl;
  cout << "> Chon mot thao tac: ";
}

void AdminMenu::handleInput() {
  cin >> selectedOption;
  cin.ignore();

  Application& app = Application::getInstance();
  if (selectedOption == "1") {
    handleReadUserList();
  // } else if (selectedOption == "2") {
  //   //TODO: logic for searching user
  //   cout << "Processing searching user..." << endl;
  }
  else if (selectedOption == "2") {
    handleCreateUser();
  } else if (selectedOption == "3") {
    handleUpdateUser();
  // } else if (selectedOption == "5") {
  //   handleDeleteUser();
  } else if (selectedOption == "4") {
    handleReadWalletList();
  } else if (selectedOption == "5") {
    app.setCurrentMenu("MasterWalletMenu"); // Chuyen sang menu cua vi tong
    return;
  } else if (selectedOption == "6") {
    app.setCurrentMenu("BackupRestoreMenu"); // Chuyen sang menu sao luu va khoi phuc du lieu
    return;
  } else if (selectedOption == "7") {
    handleBeforeLogout();
    app.setCurrentMenu("LoginMenu"); // Chuyen sang menu login
    return;
  } else {
    cout << "Lua chon khong hop le! Vui long chon lai!" << endl;
    return;
  }

  if(isReloadMenu == true) {
    app.setCurrentMenu("AdminMenu"); // Chuyen sang menu admin
    return;
  }

  backToMenu("AdminMenu"); // Chuyen sang menu admin
}

void AdminMenu::handleReadUserList() {
  Application& app = Application::getInstance();
  app.getUserMgr().displayList();
}

void AdminMenu::handleCreateUser() {
  //Nhap thon tin user tu ban phim
  string username;
  string fullName;
  string email;
  bool isAdmin = false;
  bool isAutoGenPassword = true;

  cout << endl;
  console.task("Tao nguoi dung moi");
  cout << "> Ten dang nhap: ";
  getline(cin, username);  
  cout << "> Ho va ten: ";
  getline(cin, fullName);
  cout << "> Email: ";
  getline(cin, email);

  User temp;
  string autoGenPassword = temp.autoGeneratePassword();
  console.notify("Mat khau tu sinh: " + autoGenPassword);

  User newUser(username, autoGenPassword, fullName, email, isAdmin, isAutoGenPassword);

  Application& app = Application::getInstance();
  bool resultCreate = app.getUserMgr().createUser(newUser);
  if(resultCreate == true) {
    console.notify("Tao user thanh cong!");
  } else {
    console.notify("Tao user that bai!");
  }
}

void AdminMenu::handleUpdateUser() {
  char choice;
  do
  {    
    cout << "> Hien thi danh sach nguoi dung de chon cap nhat? (y/n): ";
    cin >> choice;
    cin.ignore();
  } while (choice != 'y' && choice != 'n');

  int userId;
  string fullName = "";
  string email = "";
  Application& app = Application::getInstance();

  if(choice == 'y') {
    app.getUserMgr().displayList();
  }
  cout << "> Nhap ID nguoi dung muon thay doi: ";
  cin >> userId;
  cin.ignore();
  
  cout << endl;
  int choice_2 = 0;
  do
  { 
    if(choice_2 != 0 && choice_2 != 1 && choice_2 != 2 && choice_2 != 3 && choice_2 != 4) {
      cout << "Lua chon khong hop le! Vui long chon lai!" << endl;
    }

    cout << endl;
    console.task("Thay doi thong tin");
    cout << "   " << "1. Ho va ten" << endl;
    cout << "   " << "2. Email" << endl;
    cout << "   " << "3. Thay doi [1] va [2]" << endl;
    cout << "   " << "4. Quay tro ve menu" << endl;
    cout << endl;
    cout << "> Chon mot thao tac: ";
    cin >> choice_2;
    cin.ignore();
  } while (choice_2 != 1 && choice_2 != 2 && choice_2 != 3 && choice_2 != 4);

  if(choice_2 == 1) {
    cout << "> Nhap ho va ten moi: ";
    getline(cin, fullName);
  } else if(choice_2 == 2) {
    cout << "> Nhap email moi: ";
    getline(cin, email);
  } else if(choice_2 == 3) {
    cout << "> Nhap ho va ten moi: ";
    getline(cin, fullName);
    cout << "> Nhap email moi: ";
    getline(cin, email);
  } else if(choice_2 == 4) {
    isReloadMenu = true;
    return;
  }

  //Xac thuc OTP truoc khi cap nhat thong tin
  OTPManager otpMgr;
  bool isValidOTP = otpMgr.verifyOTP(userId, "changeInfo");
  if(isValidOTP == false) {
    console.notify("Thay doi thong tin nguoi dung that bai!");
    return;
  }

  bool resultUpdate = app.getUserMgr().updateUser(userId, fullName, email);
  if(resultUpdate == true) {
    console.notify("Thay doi thong tin nguoi dung thanh cong!");
  } else {
    console.notify("Thay doi thong tin nguoi dung that bai!");
  }
}

void AdminMenu::handleDeleteUser() {
  char choice;
  do
  {    
    cout << "> Hien thi danh sach nguoi dung de xoa? (y/n): ";
    cin >> choice;
    cin.ignore();
  } while (choice != 'y' && choice != 'n');

  int userId;
  string fullName = "";
  string email = "";
  Application& app = Application::getInstance();

  if(choice == 'y') {
    app.getUserMgr().displayList();
  }
  cout << "> Nhap ID nguoi dung muon xoa: ";
  cin >> userId;
  cin.ignore(); 

  cout << endl;
  int choice_2 = 0;
  do
  { 
    if(choice_2 != 0 && choice_2 != 1 && choice_2 != 2) {
      cout << "Lua chon khong hop le! Vui long chon lai!" << endl;
    }
    cout << "===== XAC NHAN XOA USER_ID '" << userId << "' =====" << endl;
    cout << "   " << "1. Dong y xoa" << endl;
    cout << "   " << "2. Huy bo xoa" << endl;
    cout << "> Chon mot thao tac: ";
    cin >> choice_2;
    cin.ignore();
  } while (choice_2 != 1 && choice_2 != 2);

  if(choice_2 == 2) {
    app.setCurrentMenu("AdminMenu"); // Chuyen sang menu admin
    return;
  }

  bool resultDelete = app.getUserMgr().deleteUser(userId);
  //TODO: Xoa vi cua user bi xoa, diem trong vi bi xoa se tra ve vi tong
  if(resultDelete == true) {
    console.notify("Xoa user thanh cong!");
  } else {
    console.notify("Xoa user that bai!");
  }
}

void AdminMenu::handleReadWalletList() {
  Application& app = Application::getInstance();
  app.getWalletMgr().displayList();
}

void AdminMenu::handleBeforeLogout() {
  //Tinh nang danh cho admin
  //Kiem tra yeu cau sao luu du lieu khi dang xuat thoat chuong trinh
  //Neu co hien thi thong tin xac nhan va thuc hien sao luu du lieu
  Application& app = Application::getInstance();
  if(app.getCurrentUser()->getIsAdmin() == true && app.getIsBackupDataWhenExit() == true) {
    cout << endl;
    char choice;
    do
    {
      cout << "> Ban co muon sao luu du lieu truoc khi thoat chuong trinh? (y/n): ";
      cin >> choice;
      cin.ignore();
    } while (choice != 'y' && choice != 'n');
    
    if(choice == 'y') {
      bool result = app.getBackupMgr().backupData();
      if(result == true) {
        console.notify("Sao luu du lieu thanh cong!");
      }
      else {
        console.notify("Sao luu du lieu that bai!");
      }
    }
  }
}
