//include file .h tuong ung voi .cpp
#include "Application.h"

//Destructor
Application::~Application(){  
  console.notify("Chuong trinh dang dung lai...");
  if(currentMenu != NULL) {
    delete currentMenu; // Giai phong bo nho sau khi xong
  }
  if(currentUser != NULL) {
    delete currentUser; // Giai phong bo nho sau khi xong
  }

  exit(0); // Thoat chuong trinh
}

//Getters
User* Application::getCurrentUser(){
  return currentUser;
}
Menu* Application::getCurrentMenu(){
  return currentMenu;
}
UserManager Application::getUserMgr(){
  return userMgr;
}
WalletManager Application::getWalletMgr(){
  return walletMgr;
}
TransactionManager Application::getTransactionMgr(){
  return transactionMgr;
}
ConsoleUtils Application::getConsole(){
  return console;
}

//Setters
void Application::setCurrentMenu(string menuName) {
  //Reset lai currentMenu ve NULL
  if(currentMenu != NULL) {
    delete currentMenu;    
    currentMenu = NULL;
  }
  if(menuName == "LoginMenu") {
    //Reset lai currentUser ve NULL
    if(currentUser != NULL) {
      delete currentUser;
      currentUser = NULL;
    }
    currentMenu = new LoginMenu(); // Khoi tao menu dang nhap
  } else if(menuName == "AdminMenu") {
    currentMenu = new AdminMenu(); // Khoi tao menu admin
  } else if(menuName == "UserMenu") {
    currentMenu = new UserMenu(); // Khoi tao menu user
  } else if(menuName == "MasterWalletMenu") {
    currentMenu = new MasterWalletMenu(); // Khoi tao menu master wallet
  } else if(menuName == "UserWalletMenu") {
    currentMenu = new UserWalletMenu(); // Khoi tao menu vi nguoi dung thong thuong
  } else if(menuName == "CreateWalletMenu") {
    currentMenu = new CreateWalletMenu(); // Khoi tao menu tao vi cho nguoi dung thong thuong
  } else if(menuName == "AdminTransactionMenu") {
    currentMenu = new AdminTransactionMenu(); // Khoi tao menu lich su giao dich cho admin
  }
}

//Methods
Application& Application::getInstance() {
  static Application instance;
  return instance;
}

void Application::initialize(){
  srand(time(NULL)); // Khoi tao bo sinh so ngau nhien
  console.notify("Chuong trinh dang duoc khoi tao...");
  
  FileUtils userFile(userMgr.filename, userMgr.filenameNextId);
  bool isEmptyUserFile = userFile.isEmptyFile(); 
  //Kiem tra da co file du lieu nguoi dung
  if(isEmptyUserFile == true) {
    //Tao file userData.csv voi danh sach user ban dau va file chua thong tin userNextId
    userMgr.createSampleData();   
  }

  FileUtils walletFile(walletMgr.filename, walletMgr.filenameNextId);
  bool isEmptyWalletFile = walletFile.isEmptyFile(); 
  //Kiem tra da co file du lieu cua vi
  if(isEmptyWalletFile == true) {
    //Tao file walletData.csv voi danh sach wallet ban dau va file chua thong tin walletNextId
    walletMgr.createSampleData();   
  }

  FileUtils transactionFile(transactionMgr.filename, transactionMgr.filenameNextId);
  bool isEmptyTransactionFile = transactionFile.isEmptyFile(); 
  //Kiem tra da co file du lieu cua giao dich
  if(isEmptyTransactionFile == true) {
    //Tao file transactiontData.csv voi danh sach transaction ban dau va file chua thong tin transactionNextId
    transactionMgr.createSampleData();   
  }
}

void Application::login(){
  cout << endl;
  cout << "===== Thong tin dang nhap =====" << endl;

  string username, password;
  cout << "> Ten dang nhap: ";
  getline(cin, username);  
  cout << "> Mat khau: ";
  getline(cin, password);  
  
  //authenticate user
  User user;
  User* result = user.authenticate(username, password);
  if(result != NULL) {
    console.notify("Dang nhap thanh cong!");
    delete currentUser; // Giai phong bo nho currentUser truoc khi gan lai
    currentUser = NULL;
    currentUser = new User(*result); // Gan user dang nhap thanh cong cho currentUser
  } else {
    console.notify("Dang nhap that bai!");
    currentUser = NULL;
  }
}

bool Application::signup(){
  //TODO
  bool result = false;
  //neu dang ky thanh cong tra ra true, khong thanh cong tra ra false
  return result;
}
 
bool Application::logout(){
  //TODO
  //neu dang xuat thanh cong tra ra true, khong thanh cong tra ra false
  bool result = false;
  return result;
}

void Application::run(){  
  console.notify("Chuong trinh dang chay...");

  currentMenu = new LoginMenu();  // Khoi tao menu dang nhap
  currentMenu->display();
  currentMenu->handleInput();
  while (currentMenu && currentMenu->getIsRunning()) {    
    currentMenu->display();
    currentMenu->handleInput();
  }
}
