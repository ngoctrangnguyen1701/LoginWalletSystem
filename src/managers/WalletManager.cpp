//include file .h tuong ung voi .cpp
#include "WalletManager.h"


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
    //TODO
    //hien thi dau cham ngan cach cac chu so

    cout << "|" << setw(idWidth-1) << right << item.getWalletId() << " |";
    cout << " " << setw(usernameWidth-1) << left << username << "|";
    cout << setw(balanceWidth-1) << right << item.getBalance() << " |";
    cout << " " << setw(isMasterWidth-1) << left << isMaster << "|";
    cout << endl;
  }
  
  // Print footer
  cout << "+------+-------------------------+---------------+----------+\n";
  cout << "Tong so vi: " << walletList.size() << endl;
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
      // return Wallet(); //tra ve Wallet rong
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


void WalletManager::writeItemToFile(fstream& file, Wallet& item) {
  file << item.getWalletId() << ","
       << item.getWalletId() << ","
       << item.getBalance() << ","
       << item.getIsMaster() << endl;      
}
