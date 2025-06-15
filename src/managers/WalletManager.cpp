//include file .h tuong ung voi .cpp
#include "WalletManager.h"

//include file header noi bo khac
#include "../Application.h"

//Methods
bool WalletManager::createWallet(Wallet newWallet){
  //Lay danh sach wallet va nextWalletId moi nhat
  bool resultGetList = getList();
  if(resultGetList == false) {
    return false;
  }

  //kiem tra xem wallet_id va user_id da ton tai, moi user_id chi duoc tao duy nhat 1 vi
  int walletId = nextWalletId;
  Wallet* walletExist = findWalletById(walletId); 
  if(walletExist != NULL) {
    if(walletExist->getWalletId() == walletId) {
      string text = "Da ton tai walletId '" + to_string(walletId) + "'";
      console.notify(text);
      return false;
    }
  }

  //kiem tra xem user_id co ton tai trong danh sach user khong
  int userId = newWallet.getUserId();
  Wallet* userWallet = findWalletByUserId(userId);
  if(userWallet != NULL) {
    string text = "Da ton tai vi cua userId '" + to_string(userId) + "'";
    console.notify(text);
    return false;
  }

  newWallet.setWalletId(nextWalletId); //gan id cho wallet
  nextWalletId++; //tang nextWalletId len 1

  FileUtils fileUtils(filename, filenameNextId); 
  bool resultSave = fileUtils.appendItem(*this, newWallet, nextWalletId); 
  if(resultSave == true) {
    string text = "Luu thanh cong wallet_id '" + to_string(walletId) + "'";
    console.log(text);
    return true;
  } else {
    string text = "Luu that bai wallet_id '" + to_string(walletId) + "'";
    console.log(text);
    return false; 
  }
}

bool WalletManager::getList(){
  FileUtils fileUtils(filename, filenameNextId); 
  bool result = fileUtils.loadFile(*this, walletList, nextWalletId);
  return result;
}

void WalletManager::displayList() {
  bool resultGetList = getList(); //Doc danh sach wallet tu file
  if(resultGetList == false) {
    console.notify("Khong the doc danh sach vi");
    return;
  }
  // Check if list is empty
  if (walletList.empty()) {
    cout << "\n===== Danh sach vi dang trong =====\n";
    return;
  }
  
  // Calculate the width of each column to display
  const int idWidth = 6;
  const int usernameWidth = 25;
  const int balanceWidth = 15;
  const int isMasterWidth = 10;
  
  // Print header with nice formatting
  cout << "\n+-----------------------------------------------------------+\n";
  cout << "|                      DANH SACH VI                         |\n";
  cout << "+------+-------------------------+---------------+----------+\n";
  cout << "| " << setw(idWidth - 1) << left << "ID" << "|";
  cout << " " << setw(usernameWidth - 1) << left << "Chu so huu" << "|";
  cout << " " << setw(balanceWidth - 1) << left << "So du" << "|";
  cout << " " << setw(isMasterWidth - 1) << left << "Vi tong?" << "|\n";
  cout << "+------+-------------------------+---------------+----------+\n";
  
  // Print each wallet
  for (int i = 0; i < walletList.size(); i++) {
    Wallet item = walletList[i];

    //find username by userId
    string username;
    UserManager userMgr;
    User* user = userMgr.findUserByConditionFromFile("userId", to_string(item.getUserId()));
    if(user == NULL) {
      console.notify("Khong the doc toan bo danh sach vi");
      return;
    }

    username = user->getUsername();
    string isMaster = item.getIsMaster() == 1 ? "Co" : "Khong";

    cout << "|" << setw(idWidth-1) << right << item.getWalletId() << " |";
    cout << " " << setw(usernameWidth-1) << left << username << "|";
    cout << setw(balanceWidth-1) << right << item.getBalance() << " |";
    cout << " " << setw(isMasterWidth-1) << left << isMaster << "|";
    cout << endl;

    delete user; //Giai phong vung nho
  }
  
  // Print footer
  cout << "+------+-------------------------+---------------+----------+\n";
  cout << "Tong so vi: " << walletList.size() << endl;
}

bool WalletManager::updateBalance(int walletId, int amount, string type) {
  //type la 'increment' hoac la 'decrement'
  //Lay danh sach wallet va nextWalletId moi nhat
  bool resultGetList = getList();
  if(resultGetList == false) {
    return false;
  }

  //kiem tra xem wallet_id co ton tai
  Wallet* walletExist = findWalletById(walletId);
  if(walletExist == NULL) {
    string text = "Khong ton tai walletId '" + to_string(walletId) + "'";
    console.notify(text);
    return false;
  }
  bool result = updateBalanceNotSave(walletExist, amount, type);
  if(result == false) {
    return false;
  }

  //Save walletList vao file, do file van ban thao tac ghi de 1 dong se de bi pha cau truc cua file trong truong hop do dai chuoi thay doi
  //nen phai ghi lai toan bo file
  bool resultSave = saveList();
  return resultSave;
}

bool WalletManager::updateBalanceTwoWallets(int walletId_1, int amount_1, string type_1, int walletId_2, int amount_2, string type_2) {
  //type la 'increment' hoac la 'decrement'
  //Lay danh sach wallet va nextWalletId moi nhat
  bool resultGetList = getList();
  if(resultGetList == false) {
    return false;
  }

  int size = walletList.size();
  Wallet* wallet_1;
  Wallet* wallet_2;
  for (int i = 0; i < size; i++) {
    if(walletList[i].getWalletId() == walletId_1) {
      wallet_1 = &walletList[i];
      bool result = updateBalanceNotSave(wallet_1, amount_1, type_1);
      if(result == false) {
        return false;
      }
    }

    if(walletList[i].getWalletId() == walletId_2) {
      wallet_2 = &walletList[i];
      bool result = updateBalanceNotSave(wallet_2, amount_2, type_2);
      if(result == false) {
        return false;
      }
    }
  }

  if(wallet_1 == NULL) {
    string text = "Khong ton tai walletId '" + to_string(walletId_1) + "'";
    console.notify(text);
    return false;
  }

  if(wallet_2 == NULL) {
    string text = "Khong ton tai walletId '" + to_string(walletId_2) + "'";
    console.notify(text);
    return false;
  }
  
  //Save walletList vao file, do file van ban thao tac ghi de 1 dong se de bi pha cau truc cua file trong truong hop do dai chuoi thay doi
  //nen phai ghi lai toan bo file
  bool resultSave = saveList();
  return resultSave;
}

bool WalletManager::updateBalanceNotSave(Wallet* wallet, int amount, string type){
  int balance;
  if(type == "increment") {
    balance = wallet->getBalance() + amount;
  }
  else if(type == "decrement") {
    //Doi voi thao tac giam so du phai kiem tra so tien sau khi tru khong duoc nho hon 0
    balance = wallet->getBalance() - amount;
    if(balance < 0) {
      //chi hien thong so du khong du khi la chu so huu vi
      Application& app = Application::getInstance();
      if(wallet->getUserId() == app.getCurrentUser()->getUserId()) {
        console.notify("So du hien tai khong du!");
      }
      return false;
    }
  }
  wallet->setBalance(balance);
  return true;
}

bool WalletManager::checkValidDecrement(int userId, int amount) {
  //Kiem tra balance co hop le, chi check truong hop giam diem
  //Doi voi thao tac giam so du phai kiem tra so tien sau khi tru khong duoc nho hon 0
  Wallet* wallet = findWalletByUserIdFromFile(userId);
  if(wallet == NULL) {
    return false;
  }
  int balance = wallet->getBalance() - amount;
  if(balance < 0) {
    //chi hien thong so du khong du khi la chu so huu vi
    Application& app = Application::getInstance();
    if(wallet->getUserId() == app.getCurrentUser()->getUserId()) {
      console.notify("So du hien tai khong du!");
    }
    return false;
  }
  delete wallet; //Giai phong vung nho
  return true;
}

bool WalletManager::saveList() {
  FileUtils fileUtils(filename, filenameNextId);
  bool resultSave = fileUtils.saveDataByList(*this, walletList, nextWalletId);
  return resultSave;
}

int WalletManager::loadBalanceFromFile(int walletId) {
  Wallet* wallet = findWalletByIdFromFile(walletId);
  if(wallet != NULL) {
    return wallet->getBalance();
  }
  delete wallet; //Giai phong vung nho
  return -1;
}

Wallet* WalletManager::findWalletById(int walletId) {
  int size = walletList.size();
  for (int i = 0; i < size; i++) {
    if(walletList[i].getWalletId() == walletId) {
      return &walletList[i]; //tra ve con tro den wallet
    }
  }
  return NULL;
}

vector<Wallet> WalletManager::findWalletByIds(int walletId_1, int walletId_2){
  //tim kiem wallet co id = walletId khong  
  vector<Wallet> list;
  int size = walletList.size();
  for (int i = 0; i < size; i++) {
    if (walletList[i].getWalletId() == walletId_1 || walletList[i].getWalletId() == walletId_2) {
      list.push_back(walletList[i]);
    }
  }
  return list;
}

Wallet* WalletManager::findWalletByIdFromFile(int walletId) {
  try {   
    // Mo file de doc
    string fullPath = DATA_DIRECTORY + filename + ".csv"; //lay duong dan file
    ifstream file(fullPath);
    if (!file.is_open()) {
      cerr << "Khong the mo file '" << fullPath << "'" << endl;
      file.close();
      return NULL;
    }  
    string line;
    bool isExist = false;
    Wallet result;
    while (getline(file, line)) {
      stringstream ss(line);          
      result = readItemFromFile(ss);
      if(result.getWalletId() == walletId) {
        isExist = true;
        break;
      }
    }
    file.close();
    if(isExist == false) {
      string text = "Khong tim thay item trong file '" + fullPath + "'";
      console.log(text);
      return NULL;
    }
    else {
      string text = "Da tim thay item trong file '" + fullPath + "'";
      console.log(text);
      Wallet* wallet = new Wallet(result); //tra ve con tro den Wallet tim thay
      return wallet;
    }    
  }
  catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
    return NULL;
  }
}

Wallet* WalletManager::findWalletByUserId(int userId) {
  int size = walletList.size();
  for (int i = 0; i < size; i++) {
    if(walletList[i].getUserId() == userId) {
      return &walletList[i]; //tra ve con tro den wallet
    }
  }
  return NULL;
}

Wallet* WalletManager::findWalletByUserIdFromFile(int userId) {
  try {   
    // Mo file de doc
    string fullPath = DATA_DIRECTORY + filename + ".csv"; //lay duong dan file
    ifstream file(fullPath);
    if (!file.is_open()) {
      cerr << "Khong the mo file '" << fullPath << "'" << endl;
      file.close();
      return NULL;
    }  
    string line;
    bool isExist = false;
    Wallet result;
    while (getline(file, line)) {
      stringstream ss(line);          
      result = readItemFromFile(ss);
      if(result.getUserId() == userId) {
        isExist = true;
        break;
      }
    }
    file.close();
    if(isExist == false) {
      string text = "Khong tim thay item trong file '" + fullPath + "'";
      console.log(text);
      return NULL;
    }
    else {
      string text = "Da tim thay item trong file '" + fullPath + "'";
      console.log(text);
      Wallet* wallet = new Wallet(result); //tra ve con tro den Wallet tim thay
      return wallet;
    }    
  }
  catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
    return NULL;
  }
}

bool WalletManager::createSampleData() {
  vector<Wallet> walletList;  
  walletList.push_back(MasterWallet(1, 97600));
  walletList.push_back(UserWallet(2, 1000));
  walletList.push_back(UserWallet(3, 800));
  walletList.push_back(UserWallet(4, 500));
  walletList.push_back(UserWallet(5, 100));

  for (int i = 0; i < walletList.size(); i++) {
    walletList[i].setWalletId(i + 1);
  }
  int nextWalletId = walletList.size() + 1;
  FileUtils fileUtils(filename, filenameNextId);
  bool result = fileUtils.saveDataByList(*this, walletList, nextWalletId);
  return result;
}

Wallet WalletManager::readItemFromFile(stringstream& ss) {
  int walletId;
  int userId;
  int balance;
  bool isMaster;

  string token; // Declare token for getline
  
  getline(ss, token, ',');
  walletId = stoi(token);
  getline(ss, token, ',');
  userId = stoi(token);
  getline(ss, token, ',');
  balance = stoi(token);  
  getline(ss, token, ',');
  isMaster = (token == "1");
   
  //Tao wallet va set walletId
  Wallet wallet(userId, balance, isMaster);
  wallet.setWalletId(walletId);
  return wallet;
}

void WalletManager::writeItemToFile(fstream& file, Wallet item) {
  file << item.getWalletId() << ","
       << item.getUserId() << ","
       << item.getBalance() << ","
       << item.getIsMaster() << endl;      
}
