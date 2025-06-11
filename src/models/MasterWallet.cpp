//include file .h tuong ung voi .cpp
#include "MasterWallet.h"

//include thu vien
#include <string>

//include file header noi bo khac
//...

//Contructors
//goi truc tiep contructor cua lop Wallet
MasterWallet::MasterWallet(int userId, int balance) : Wallet(userId, balance, true){}
MasterWallet::MasterWallet() {
  this->walletId = 1; //Vi tong co id mac dinh = 1
  this->isMaster = true;
}

//Methods
bool MasterWallet::deposit(int amount) {
  //Tao giao dich nap diem vao vi tong
  string referenceId = "";
  int sourceWalletId = 0;
  int destinationWalletId = 0;
  string type = "deposit";
  string createdDate = getCurrentDateTimeFormatted();
  string status = "success";
  Transaction newTransaction(
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
  bool resultTrans = TransactionMgr.createTransaction(newTransaction);
  if(resultTrans == false) {
    return false;
  }

  //Cap nhat du lieu vi
  WalletManager WalletMgr;
  bool result = WalletMgr.updateBalance(walletId, amount, "increment"); //Vi tong co id mac dinh = 1
  if(result == false) {
    TransactionMgr.updateStatus(newTransaction.getTransactionId(), "failed");
    return false;
  }
  return true;
};

bool MasterWallet::withdraw(int amount) {
  // //Tao giao dich rut diem o vi tong
  string referenceId = "";
  int sourceWalletId = 0;
  int destinationWalletId = 0;
  string type = "withdraw";
  string createdDate = getCurrentDateTimeFormatted();
  string status = "success";
  Transaction newTransaction(
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
  bool resultTrans = TransactionMgr.createTransaction(newTransaction);
  if(resultTrans == false) {
    return false;
  }

  //Cap nhat du lieu vi
  WalletManager WalletMgr;
  bool result = WalletMgr.updateBalance(1, amount, "decrement"); //Vi tong co id mac dinh = 1
  if(result == false) {
    TransactionMgr.updateStatus(newTransaction.getTransactionId(), "failed");
    return false;
  }
  return true;
};
