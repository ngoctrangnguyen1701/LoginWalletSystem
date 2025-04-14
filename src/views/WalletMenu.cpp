//include file .h tuong ung voi .cpp
#include "WalletMenu.h"

//include thu vien
#include <iostream>
#include <fstream>
#include <iomanip> 

//include file header noi bo khac
#include "../models/Wallet.h"
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
  walletList.push_back(Wallet("admin", "123", "Administrator", "admin@gmail.com", true, false));
  walletList.push_back(Wallet("binhduong", "binhduong123", "Binh Duong 68", "binhduong123@example.com", false, false));
  walletList.push_back(Wallet("tamgiac", "tamgiac123", "Tam giac mach", "tamgiac@example.com", false, false));
  walletList.push_back(Wallet("trian", "trian123", "Tri An", "trian@example.com", false, false));
  walletList.push_back(Wallet("vinhhy", "vinhhy123", "Vinh Hy", "vinhhy@example.com", false, false));
  walletList.push_back(Wallet("nuicam", "nuicam123", "Thien Cam Son", "nuicam@example.com", false, false));  

  for (int i = 0; i < walletList.size(); i++) {
    walletList[i].setWalletId(i + 1);
  }
  int nextWalletId = walletList.size() + 1;
  FileUtils fileUtils(filename, filenameNextId);
  bool result = fileUtils.saveDataByList(*this, walletList, nextWalletId);
  return result;
}