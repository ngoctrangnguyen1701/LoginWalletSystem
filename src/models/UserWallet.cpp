//include file .h tuong ung voi .cpp
#include "UserWallet.h"

//include file header noi bo khac
#include "../Application.h"

//Contructors
UserWallet::UserWallet(int userId, int balance) : Wallet(userId, balance, false){}
UserWallet::UserWallet() {
  //Tim walletId theo userId
  Application& app = Application::getInstance();
  int userId = app.getCurrentUser()->getUserId();
  Wallet* wallet = app.getWalletMgr().findWalletByUserIdFromFile(userId);
  if(wallet != NULL) {
    this->walletId = wallet->getWalletId();
  }
  this->isMaster = false;
  delete wallet; //Giai phong vung nho
}

//Methods
bool UserWallet::deposit(int amount) {
  //Tao giao dich chuyen diem tu vi tong sang vi nguoi dung
  MasterWallet mstWallet;
  int masterWaletId = mstWallet.getWalletId();
  string referenceId = "";
  int sourceWalletId = mstWallet.getWalletId();
  int destinationWalletId = walletId;
  string type = "transfer";
  string createdDate = getCurrentDateTimeFormatted();
  string status = "success";
  Transaction newTransaction_1(
    masterWaletId,
    referenceId,
    sourceWalletId,
    destinationWalletId,
    type,
    amount,
    createdDate,
    status
  );

  //Tao giao dich nap diem vao vi nguoi dung
  sourceWalletId = 0;
  destinationWalletId = 0;
  type = "deposit";
  Transaction newTransaction_2(
    walletId,
    referenceId,
    sourceWalletId,
    destinationWalletId,
    type,
    amount,
    createdDate,
    status
  );

  vector<Transaction> list;
  list.push_back(newTransaction_1);
  list.push_back(newTransaction_2);
  TransactionManager TransactionMgr;
  bool resultTrans = TransactionMgr.createTransactionList(list);
  if(resultTrans == false) {
    return false;
  }

  WalletManager WalletMgr;
  //Cap nhat du lieu vi tong va vi nguoi dung
  bool result = WalletMgr.updateBalanceTwoWallets(masterWaletId, amount, "decrement", walletId, amount, "increment"); 
  if(result == false) {
      TransactionMgr.updateStatus(list, "failed");
    return false;
  }
  return true;
};

bool UserWallet::withdraw(int amount) {
  //Tao giao dich chuyen diem tu vi nguoi dung sang vi tong
  MasterWallet mstWallet; 
  int masterWaletId = mstWallet.getWalletId();
  string referenceId = "";
  int sourceWalletId = walletId;
  int destinationWalletId = mstWallet.getWalletId();
  string type = "receive";
  string createdDate = getCurrentDateTimeFormatted();
  string status = "success";
  Transaction newTransaction_1(
    masterWaletId,
    referenceId,
    sourceWalletId,
    destinationWalletId,
    type,
    amount,
    createdDate,
    status
  );

  //Tao giao dich rut diem tu vi nguoi dung
  sourceWalletId = 0;
  destinationWalletId = 0;
  type = "withdraw";
  Transaction newTransaction_2(
    walletId,
    referenceId,
    sourceWalletId,
    destinationWalletId,
    type,
    amount,
    createdDate,
    status
  );

  vector<Transaction> list;
  list.push_back(newTransaction_1);
  list.push_back(newTransaction_2);
  TransactionManager TransactionMgr;
  bool resultTrans = TransactionMgr.createTransactionList(list);
  if(resultTrans == false) {
    return false;
  }

  WalletManager WalletMgr;
  //Cap nhat du lieu vi tong va vi nguoi dung
  bool result = WalletMgr.updateBalanceTwoWallets(masterWaletId, amount, "increment", walletId, amount, "decrement"); 
  if(result == false) {
    TransactionMgr.updateStatus(list, "failed");
    return false;
  }
  return true;
};


bool UserWallet::transfer(int destinationWalletId, int amount) {
   //Tao giao dich chuyen diem tu vi nguon sang vi dich
  string referenceId = "";
  int sourceWalletId = walletId;
  string type = "transfer";
  string createdDate = getCurrentDateTimeFormatted();
  string status = "success";
  Transaction newTransaction_1(
    walletId,
    referenceId,
    sourceWalletId,
    destinationWalletId,
    type,
    amount,
    createdDate,
    status
  );
 
  //Tao giao dich nhan diem tu vi nguon sang vi dich
  type = "receive";
  Transaction newTransaction_2(
    destinationWalletId,
    referenceId,
    sourceWalletId,
    destinationWalletId,
    type,
    amount,
    createdDate,
    status
  );

  vector<Transaction> list;
  list.push_back(newTransaction_1);
  list.push_back(newTransaction_2);
  TransactionManager TransactionMgr;
  bool resultTrans = TransactionMgr.createTransactionList(list);
  if(resultTrans == false) {
    return false;
  }

  WalletManager WalletMgr;
  //Cap nhat du lieu vi nguon va vi dich
  bool result = WalletMgr.updateBalanceTwoWallets(walletId, amount, "decrement", destinationWalletId, amount, "increment"); 
  if(result == false) {
    TransactionMgr.updateStatus(list, "failed");
    return false;
  }
  return true;
};
