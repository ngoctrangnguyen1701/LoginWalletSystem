//include file .h tuong ung voi .cpp
#include "MasterWallet.h"

//include thu vien
#include <string>

//include file header noi bo khac
//...

//Contructors
//goi truc tiep contructor cua lop Wallet
MasterWallet::MasterWallet(int userId, int balance) : Wallet(userId, balance) {}

//Methods
bool MasterWallet::deposit(int amount) {
  //TODO
  //Thanh cong tra ve true, nguoc lai tra ve false
  return false;
};
bool MasterWallet::withdraw(int amount) {
  //TODO
  //Thanh cong tra ve true, nguoc lai tra ve false
  return false;
};
