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
  referenceId = "";
  sourceWalletId = 0;
  destinationWalletId = 0;
  type = "deposit";
  // string createdDate = getCurrentDateTimeFormatted();
  // string status = "success";
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

  TransactionManager TransactionMgr;
  bool resultTrans = TransactionMgr.createTransactions(newTransaction_1, newTransaction_2);
  if(resultTrans == false) {
    return false;
  }

  WalletManager WalletMgr;
  //Cap nhat du lieu vi tong va vi nguoi dung
  bool result = WalletMgr.updateBalanceTwoWallets(masterWaletId, amount, "decrement", walletId, amount, "increment"); 
  if(result == false) {
    TransactionMgr.updateStatus(newTransaction_1.getTransactionId(), "failed", newTransaction_2.getTransactionId(), "failed");
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
  referenceId = "";
  sourceWalletId = 0;
  destinationWalletId = 0;
  type = "withdraw";
  // string createdDate = getCurrentDateTimeFormatted();
  // string status = "success";
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

  TransactionManager TransactionMgr;
  bool resultTrans = TransactionMgr.createTransactions(newTransaction_1, newTransaction_2);
  if(resultTrans == false) {
    return false;
  }

  WalletManager WalletMgr;
  //Cap nhat du lieu vi tong va vi nguoi dung
  bool result = WalletMgr.updateBalanceTwoWallets(masterWaletId, amount, "increment", walletId, amount, "decrement"); 
  if(result == false) {
    TransactionMgr.updateStatus(newTransaction_1.getTransactionId(), "failed", newTransaction_2.getTransactionId(), "failed");
    return false;
  }
  return true;
};


bool UserWallet::transfer(int destinationWalletId, int amount) {
   //Tao giao dich chuyen diem tu vi nguon sang vi dich
  // MasterWallet mstWallet; 
  // int masterWaletId = mstWallet.getWalletId();
  string referenceId = "";
  int sourceWalletId = walletId;
  // int destinationWalletId = destinationWalletId;
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
  // referenceId = "";
  // sourceWalletId = 0;
  // destinationWalletId = 0;
  type = "receive";
   // string createdDate = getCurrentDateTimeFormatted();
   // string status = "success";
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

  TransactionManager TransactionMgr;
  bool resultTrans = TransactionMgr.createTransactions(newTransaction_1, newTransaction_2);
  if(resultTrans == false) {
    return false;
  }

  WalletManager WalletMgr;
  //Cap nhat du lieu vi nguon va vi dich
  bool result = WalletMgr.updateBalanceTwoWallets(walletId, amount, "decrement", destinationWalletId, amount, "increment"); 
  if(result == false) {
    TransactionMgr.updateStatus(newTransaction_1.getTransactionId(), "failed", newTransaction_2.getTransactionId(), "failed");
    return false;
  }
  return true;
};
