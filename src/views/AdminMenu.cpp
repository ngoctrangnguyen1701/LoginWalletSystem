//include file .h tuong ung voi .cpp
#include "AdminMenu.h"

//Contructors
//goi truc tiep contructor cua lop Menu
AdminMenu::AdminMenu() : Menu("Menu danh cho Admin") {
  options = vector<string>(8); //Tao vector co 9 phan tu
  options[0] = "1. Doc danh sach nguoi dung";
  options[1] = "2. Tim kiem nguoi dung";
  options[2] = "3. Them nguoi dung";
  options[3] = "4. Thay doi thong tin nguoi dung";
  // options[4] = "5. Xoa nguoi dung";
  options[4] = "5. Doc danh sach vi";
  options[5] = "6. Vi tong";
  options[6] = "7. Sao luu va khoi phuc du lieu";
  options[7] = "8. Dang xuat";
}

//Methods
void AdminMenu::display() {
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

void AdminMenu::handleInput() {
  cin >> selectedOption;
  cin.ignore();

  Application& app = Application::getInstance();
  if (selectedOption == "1") {
    handleReadUserList();
  } else if (selectedOption == "2") {
    //TODO: logic for searching user
    cout << "Processing searching user..." << endl;
  }
  else if (selectedOption == "3") {
    handleCreateUser();
  } else if (selectedOption == "4") {
    handleUpdateUser();
  // } else if (selectedOption == "5") {
  //   handleDeleteUser();
  } else if (selectedOption == "5") {
    handleReadWalletList();
  } else if (selectedOption == "6") {
    app.setCurrentMenu("MasterWalletMenu"); // Chuyen sang menu cua vi tong
    return;
  } else if (selectedOption == "7") {
    app.setCurrentMenu("BackupRestoreMenu"); // Chuyen sang menu sao luu va khoi phuc du lieu
    return;
  } else if (selectedOption == "8") {
    handleBeforeLogout();
    app.setCurrentMenu("LoginMenu"); // Chuyen sang menu login
    return;
  } else {
    cout << "Lua chon khong hop le! Vui long chon lai" << endl;
    return;
  }
  // cout << endl;
  char choice;
  do
  {    
    cout << "> Quay tro ve menu? (y): ";
    cin >> choice;
    cin.ignore();
  } while (choice != 'y');
  app.setCurrentMenu("AdminMenu"); // Chuyen sang menu admin
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
  bool isAutoGenPassword = true; //TODO: mat khau tu sinh, yeu cau doi mat khau khi dang nhap lan dau tien
  cout << endl;
  cout << "===== Tao nguoi dung moi =====" << endl;
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
  // cout << endl;
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
  //TODO
  //check userId co ton tai truoc khi lua chon thay doi thong tin
  
  cout << endl;
  int choice_2 = 0;
  do
  { 
    if(choice_2 != 0 && choice_2 != 1 && choice_2 != 2 && choice_2 != 3 && choice_2 != 4) {
      cout << "Lua chon khong hop le! Vui long chon lai" << endl;
    }
    cout << "===== Thay doi thong tin =====" << endl;
    cout << "   " << "1. Ho va ten" << endl;
    cout << "   " << "2. Email" << endl;
    cout << "   " << "3. Thay doi [1] va [2]" << endl;
    cout << "   " << "4. Quay tro ve menu" << endl;
    cout << "> Chon mot thao tac: ";
    cin >> choice_2;
    cin.ignore();
  } while (choice_2 != 1 && choice_2 != 2 && choice_2 != 3 && choice_2 != 4);

  // cin.ignore(); // Bo qua ki tu xuong dong
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
    app.setCurrentMenu("AdminMenu"); // Chuyen sang menu admin
    return;
  }

  bool resultUpdate = app.getUserMgr().updateUser(userId, fullName, email);
  if(resultUpdate == true) {
    console.notify("Cap nhat user thanh cong!");
  } else {
    console.notify("Cap nhat user that bai!");
  }
}

void AdminMenu::handleDeleteUser() {
  // cout << endl;
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

  //TODO
  //check userId co ton tai truoc khi xac nhan xoa
  
  cout << endl;
  int choice_2 = 0;
  do
  { 
    if(choice_2 != 0 && choice_2 != 1 && choice_2 != 2) {
      cout << "Lua chon khong hop le! Vui long chon lai" << endl;
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
