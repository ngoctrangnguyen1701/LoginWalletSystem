//include file .h tuong ung voi .cpp
#include "UserWalletMenu.h"

//Contructors
//goi truc tiep contructor cua lop Menu
UserWalletMenu::UserWalletMenu() : Menu("Menu thao tac vi") {
  options = vector<string>(6); //Tao vector co 6 phan tu
  options[0] = "1. Nap";
  options[1] = "2. Rut";
  options[2] = "3. Chuyen khoan";
  options[3] = "4. Xem so du";
  options[4] = "5. Lich su giao dich";
  options[5] = "6. Quay ve menu truoc";
}

//Methods
void UserWalletMenu::display() {
  cout << endl;
  printHeader();
  
  for (int i = 0; i < options.size(); i++) {
    cout << "   " << options[i] << endl;
  }
  cout << endl;
  cout << "> Chon mot thao tac: ";
}

void UserWalletMenu::handleInput() {
  cin >> selectedOption;
  cin.ignore();

  Application& app = Application::getInstance();
  if (selectedOption == "1") {
    handleDeposit();
  } else if (selectedOption == "2") {
    handleWithdraw();
  } else if (selectedOption == "3") {
    handleTransfer();
  } else if (selectedOption == "4") {
    handleCheckBalance();
  } else if (selectedOption == "5") {
    handleDisplayTransaction();
  } else if (selectedOption == "6") {
    app.setCurrentMenu("UserMenu");
    return;
  } else {
    cout << "Lua chon khong hop le! Vui long chon lai!" << endl;
    return;
  }
  
  backToMenu("UserWalletMenu"); // Chuyen sang menu vi nguoi dung thong thuong
}

void UserWalletMenu::handleDeposit() {
  //Tinh nang nap diem vao vi nguoi dung
  Application& app = Application::getInstance();

  cout << endl;
  console.task("Nap diem vao vi");
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
    cout << "> Xac nhan NAP '" << formatWithDotSeparator(amount) << "' diem vao vi? (y/n): ";
    cin >> choice;
    cin.ignore();
  } while (choice != 'y' && choice != 'n');

  if(choice == 'n') {
    return;
  }

  //Xac thuc OTP truoc khi thao tac
  // int userId = app.getCurrentUser()->getUserId();
  // OTPManager otpMgr;
  // bool isValidOTP = otpMgr.verifyOTP(userId, "deposit");
  // if(isValidOTP == false) {
  //   console.notify("Nap diem that bai!");
  //   return;
  // }

  //Xac thuc TOTP truoc khi thao tac
  int userId = app.getCurrentUser()->getUserId();
  OTPManager otpMgr;
  bool isValidOTP = otpMgr.verifyTOTP(userId, "deposit");
  if(isValidOTP == false) {
    console.notify("Nap diem that bai!");
    return;
  }

  UserWallet wallet;
  bool result = wallet.deposit(amount);
  if(result == true) {
    console.notify("Nap diem thanh cong!");
  }
  else {
    console.notify("Nap diem that bai!");
  }
}

void UserWalletMenu::handleWithdraw() {
  //Tinh nang rut diem o vi nguoi dung
  cout << endl;
  console.task("Rut diem o vi");
  int amount;
  int isValid;
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
    cout << "> Xac nhan RUT '" << formatWithDotSeparator(amount) << "' diem o vi? (y/n): ";
    cin >> choice;
    cin.ignore();
  } while (choice != 'y' && choice != 'n');

  if(choice == 'n') {
    return;
  }

  //Xac thuc OTP truoc khi thao tac
  // Application& app = Application::getInstance();
  // int userId = app.getCurrentUser()->getUserId();
  // OTPManager otpMgr;
  // bool isValidOTP = otpMgr.verifyOTP(userId, "withdraw");
  // if(isValidOTP == false) {
  //   console.notify("Rut diem that bai!");
  //   return;
  // }

  //Xac thuc TOTP truoc khi thao tac
  Application& app = Application::getInstance();
  int userId = app.getCurrentUser()->getUserId();
  OTPManager otpMgr;
  bool isValidOTP = otpMgr.verifyTOTP(userId, "withdraw");
  if(isValidOTP == false) {
    
    console.notify("Rut diem that bai!");
    return;
  }

  UserWallet wallet;
  bool result = wallet.withdraw(amount);
  if(result == true) {
    console.notify("Rut diem thanh cong!");
  }
  else {
    console.notify("Rut diem that bai!");
  }
}

void UserWalletMenu::handleTransfer() {
  //Tinh nang chuyen diem o vi nguoi dung
  cout << endl;
  console.task("Chuyen diem cho vi");
  int walletId;
  Application& app = Application::getInstance();
  Wallet* destinationWallet;
  do
  {
    cout << "> Nhap id cua vi can chuyen: ";
    cin >> walletId;
    cin.ignore();

    //Kiem tra vi dich co ton tai
    destinationWallet = app.getWalletMgr().findWalletByIdFromFile(walletId);
    if(destinationWallet == NULL) {
      console.notify("Vi nhan diem khong ton tai!");
    }
  } while (destinationWallet == NULL);

  int amount;
  bool isValid;
  do
  {
    cout << "> Nhap so diem can chuyen: ";
    cin >> amount;
    cin.ignore();
    if (amount <= 0) {
      console.notify("So diem chuyen phai lon hon 0!");
    }
    else {
      isValid = checkValidDecrement(amount);
    }
  } while (amount <= 0 || isValid == false);

  //hien thi ten nguoi so huu vi nhan diem
  cout << endl;
  console.task("Thong tin chuyen diem");
  User* destinationWalletOwner = app.getUserMgr().findUserByConditionFromFile("userId", to_string(destinationWallet->getUserId()));
  if(destinationWalletOwner != NULL) {
    cout << "   ID vi: " << destinationWallet->getWalletId() << endl;
    cout << "   Nguoi so huu: " << destinationWalletOwner->getFullName() << endl;
    cout << "   So diem: " << formatWithDotSeparator(amount) << endl;
  }

  char choice;
  do
  {    
    cout << "> Xac nhan CHUYEN? (y/n): ";
    cin >> choice;
    cin.ignore();
  } while (choice != 'y' && choice != 'n');

  if(choice == 'n') {
    return;
  }

  //Xac thuc OTP truoc khi thao tac
  // int userId = app.getCurrentUser()->getUserId();
  // OTPManager otpMgr;
  // bool isValidOTP = otpMgr.verifyOTP(userId, "transfer");
  // if(isValidOTP == false) {
  //   console.notify("Chuyen diem that bai!");
  //   return;
  // }

  //Xac thuc TOTP truoc khi thao tac
  int userId = app.getCurrentUser()->getUserId();
  OTPManager otpMgr;
  bool isValidOTP = otpMgr.verifyTOTP(userId, "transfer");
  if(isValidOTP == false) {
    console.notify("Chuyen diem that bai!");
    return;
  }

  UserWallet wallet;
  bool result = wallet.transfer(destinationWallet->getWalletId(), amount);
  if(result == true) {
    console.notify("Chuyen diem thanh cong!");
  }
  else {
    console.notify("Chuyen diem that bai!");
  }

  delete destinationWallet; //Giai phong vung nho
  delete destinationWalletOwner; //Giai phong vung nho
}

void UserWalletMenu::handleCheckBalance() {
  Application& app = Application::getInstance();
  int userId = app.getCurrentUser()->getUserId();
  Wallet* wallet = app.getWalletMgr().findWalletByUserIdFromFile(userId);
  if(wallet != NULL) {
    cout << "So du hien tai la: " << formatWithDotSeparator(wallet->getBalance()) << endl;
  }
  else {
    cout << "Khong the doc so du hien tai!" << endl;
  }
  delete wallet; //Giai phong vung nho
}

void UserWalletMenu::handleDisplayTransaction() {
  Application& app = Application::getInstance();
  int userId = app.getCurrentUser()->getUserId();
  Wallet* wallet = app.getWalletMgr().findWalletByUserIdFromFile(userId);
  if(wallet != NULL) {
    app.getTransactionMgr().displayList(wallet->getWalletId());
  }
  else {
    cout << "Khong the doc lich su giao dich!" << endl;
  }
}

bool UserWalletMenu::checkValidDecrement(int amount) {
  Application& app = Application::getInstance();
  int userId = app.getCurrentUser()->getUserId();
  bool result = app.getWalletMgr().checkValidDecrement(userId, amount);
  return result;
}
