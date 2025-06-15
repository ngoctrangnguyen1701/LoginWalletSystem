//include file .h tuong ung voi .cpp
#include "Wallet.h"

//include file header noi bo khac
#include "../managers/WalletManager.h"

//Contructors
Wallet::Wallet(int userId, int balance, bool isMaster){
  this->userId = userId;
  this->balance = balance;
  this->isMaster = isMaster;
}

//Setters
void Wallet::setWalletId(int walletId) {
  this->walletId = walletId;
}
void Wallet::setBalance(int balance) {
  this->balance = balance;
}

//Getters
int Wallet::getWalletId() {
  return walletId;
}
int Wallet::getUserId() {
  return userId;
}
int Wallet::getBalance() {
  return balance;
}
bool Wallet::getIsMaster() {
  return isMaster;
}
