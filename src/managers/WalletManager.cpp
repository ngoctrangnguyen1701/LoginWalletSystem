//include file .h tuong ung voi .cpp
#include "WalletManager.h"

//include thu vien
#include <iostream>
#include <fstream>
#include <iomanip> 

//include file header noi bo khac
#include "../models/Wallet.h"
#include "../models/UserWallet.h"
#include "../models/MasterWallet.h"
#include "../utils/FileUtils.h"

using namespace std;

//Contructors
//WalletMenu::WalletMenu(){}

//Destructor
WalletManager::~WalletManager(){
  //TODO
  //Giai phong bo nho
  // cout << "WalletManager destructor" << endl;
  if(walletList.size() > 0) {
    walletList.clear(); 
  }  
}

//Methods
bool WalletManager::createSampleData() {
  vector<Wallet> walletList;  
  walletList.push_back(MasterWallet(1, 100000));
  walletList.push_back(UserWallet(2, 1000));
  walletList.push_back(UserWallet(3, 700));
  walletList.push_back(UserWallet(4, 500));
  walletList.push_back(UserWallet(5, 100));
  walletList.push_back(UserWallet(6, 0));

  for (int i = 0; i < walletList.size(); i++) {
    walletList[i].setWalletId(i + 1);
  }
  int nextWalletId = walletList.size() + 1;
  FileUtils fileUtils(filename, filenameNextId);
  bool result = fileUtils.saveDataByList(*this, walletList, nextWalletId);
  return result;
}

void WalletManager::writeItemToFile(fstream& file, Wallet& item) {
  file << item.getWalletId() << ","
       << item.getUserId() << ","
       << item.getBalance() << ","
       << item.getIsMaster() << endl;      
}
