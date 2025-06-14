//include file .h tuong ung voi .cpp
#include "MasterWalletMenu.h"

//Contructors
//goi truc tiep contructor cua lop Menu
MasterWalletMenu::MasterWalletMenu() : Menu("Menu thao tac vi tong") {
  options = vector<string>(5); //Tao vector co 5 phan tu
  options[0] = "1. Nap";
  options[1] = "2. Rut";    
  options[2] = "3. Xem so du";
  options[3] = "4. Lich su giao dich";
  options[4] = "5. Quay ve menu truoc";
}

//Methods
void MasterWalletMenu::display() {
  cout << endl;
  printHeader();
  
  for (int i = 0; i < options.size(); i++) {
    cout << "   " << options[i] << endl;
  }
  cout << endl;
  cout << "> Chon mot thao tac: ";
}

void MasterWalletMenu::handleInput() {
  cin >> selectedOption;
  cin.ignore();

  Application& app = Application::getInstance();
  if (selectedOption == "1") {
    handleDeposit();
  } else if (selectedOption == "2") {
    handleWithdraw();
  } else if (selectedOption == "3") {
    handleCheckBalance();
  } else if (selectedOption == "4") {
    handleDisplayTransaction();
    //TODO
    // app.setCurrentMenu("AdminTransactionMenu"); // Chuyen sang menu lich su giao dich cua admin
    // return;
  } else if (selectedOption == "5") {
    app.setCurrentMenu("AdminMenu"); // Chuyen sang menu admin
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
  app.setCurrentMenu("MasterWalletMenu"); // Chuyen sang menu vi tong
}

void MasterWalletMenu::handleDeposit() {
  //Tinh nang nap diem vao vi tong
  cout << endl;
  console.task("Nap diem vao vi tong");
  int amount;
  do
  {
    cout << "> Nhap so diem can nap: ";
    cin >> amount;
    cin.ignore();
    if (amount <= 0) {
      console.notify("So diem nap phai lon hon 0!");
    }
  } while (amount <= 0);

  char choice;
  do
  {    
    cout << "> Xac nhan NAP '" << formatWithDotSeparator(amount) << "' diem vao vi tong? (y/n): ";
    cin >> choice;
    cin.ignore();
  } while (choice != 'y' && choice != 'n');

  if(choice == 'n') {
    return;
  }

  //Xac thuc OTP truoc khi thao tac
  Application& app = Application::getInstance();
  int userId = app.getCurrentUser()->getUserId();
  OTPManager otpMgr;
  bool isValidOTP = otpMgr.verifyOTP(userId, "deposit");
  if(isValidOTP == false) {
    console.notify("Nap diem that bai!");
    return;
  }

  MasterWallet wallet;
  bool result = wallet.deposit(amount);
  if(result == true) {
    console.notify("Nap diem thanh cong!");
  }
  else {
    console.notify("Nap diem that bai!");
  }
}

void MasterWalletMenu::handleWithdraw() {
  //Tinh nang nap diem vao vi tong
  cout << endl;
  console.task("Rut diem o vi tong");
  int amount;
  bool isValid;
  do
  {
    cout << "> Nhap so diem can rut: ";
    cin >> amount;
    cin.ignore();
    if (amount <= 0) {
      console.notify("So diem rut phai lon hon 0!");
    }
    else {
      isValid = checkValidDecrement(amount);
    }
  } while (amount <= 0 || isValid == false);

  char choice;
  do
  {    
    cout << "> Xac nhan RUT '" << formatWithDotSeparator(amount) << "' diem o vi tong? (y/n): ";
    cin >> choice;
    cin.ignore();
  } while (choice != 'y' && choice != 'n');

  if(choice == 'n') {
    return;
  }

  //Xac thuc OTP truoc khi thao tac
  Application& app = Application::getInstance();
  int userId = app.getCurrentUser()->getUserId();
  OTPManager otpMgr;
  bool isValidOTP = otpMgr.verifyOTP(userId, "withdraw");
  if(isValidOTP == false) {
    console.notify("Rut diem that bai!");
    return;
  }

  MasterWallet wallet;
  bool result = wallet.withdraw(amount);
  if(result == true) {
    console.notify("Rut diem thanh cong!");
  }
  else {
    console.notify("Rut diem that bai!");
  }
}

void MasterWalletMenu::handleCheckBalance() {
  Application& app = Application::getInstance();
  Wallet* wallet =  app.getWalletMgr().findWalletByIdFromFile(1); //Vi tong co id mac dinh = 1
  if(wallet != NULL) {
    cout << "So du hien tai la: " << formatWithDotSeparator(wallet->getBalance()) << endl;
  }
  else {
    cout << "Khong the doc so du hien tai!" << endl;
  }
}

void MasterWalletMenu::handleDisplayTransaction() {
  Application& app = Application::getInstance();
  app.getTransactionMgr().displayList(1); //Vi tong co id mac dinh = 1
}

bool MasterWalletMenu::checkValidDecrement(int amount) {
  Application& app = Application::getInstance();
  int userId = app.getCurrentUser()->getUserId();
  bool result = app.getWalletMgr().checkValidDecrement(userId, amount);
  return result;
}
