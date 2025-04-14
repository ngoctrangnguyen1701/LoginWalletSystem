//include file .h tuong ung voi .cpp
#include "Wallet.h"

//include thu vien
#include <string>

//include file header noi bo khac
//...

//Contructors
Wallet::Wallet(int userId, int balance){
  this->userId = userId;
  this->balance = balance;
}

//Setters
void Wallet::setWalletId(int walletId) {
  this->walletId = walletId;
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
