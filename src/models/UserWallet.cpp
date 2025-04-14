//include file .h tuong ung voi .cpp
#include "UserWallet.h"

//include thu vien
#include <string>

//include file header noi bo khac
//...

//Contructors
UserWallet::UserWallet(int userId, int balance) : Wallet(userId, balance, false){}

//Methods
bool UserWallet::deposit(int amount) {
  //TODO
  //Thanh cong tra ve true, nguoc lai tra ve false
  return false;
};
bool UserWallet::withdraw(int amount) {
  //TODO
  //Thanh cong tra ve true, nguoc lai tra ve false
  return false;
};


bool UserWallet::transfer(int walletIdDestination, int amount) {
  //TODO
  //Thanh cong tra ve true, nguoc lai tra ve false
  return false;
};
