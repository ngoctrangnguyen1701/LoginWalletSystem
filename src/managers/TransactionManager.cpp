//include file .h tuong ung voi .cpp
#include "TransactionManager.h"
using namespace std;


//Destructor
TransactionManager::~TransactionManager(){
  //TODO
  //Giai phong bo nho
  // cout << "TransactionManager destructor" << endl;
  if(transactionList.size() > 0) {
    transactionList.clear(); 
  }  
}

//Methods
bool TransactionManager::getList(int walletId){
  FileUtils fileUtils(filename, filenameNextId);
  bool result;
  if(walletId == 0) {
    result = fileUtils.loadFile(*this, transactionList, nextTransactionId);
  }
  else {
    findTransactionByWalleIdFromFile(walletId);
    return true;
  }
  return result;
}

void TransactionManager::displayList(int walletId) {
  bool resultGetList = getList(walletId); //Doc danh sach transaction tu file
  if(resultGetList == false) {
    console.notify("Khong the doc danh sach lich su giao dich");
    return;
  }
  // Check if list is empty
  if (transactionList.empty()) {
    cout << "\n===== Danh sach lich su giao dich =====\n";
    return;
  }
  
  // Calculate the width of each column to display
  // const int idWidth = 6;
  // const int transactionnameWidth = 25;
  // const int balanceWidth = 15;
  // const int isMasterWidth = 10;
  
  // Print header with nice formatting
  cout << "\n+-----------------------------------------------------+\n";
  cout << "|             DANH SACH LICH SU GIAO DICH             |\n";
  cout << "+-----------------------------------------------------+\n";
  
  // Print each transaction
  for (int i = 0; i < transactionList.size(); i++) {
    Transaction item = transactionList[i];
    //TODO: hien thi giao dich theo mo ta, vd: ngay ..., giao dich chuyen 1000 diem cho vi A thanh cong...
    cout << endl;
    cout << "________ ID: " << item.getTransactionId() << " ________" << endl;
    cout << "ID vi: " << item.getWalletId() << endl;
    if(item.getReferenceId() != "") {
      cout << "ma tham chieu: " << item.getReferenceId() << endl;
    }
    // cout << "ma tham chieu chung: " << item.getReferenceId() << endl;
    if(item.getSourceWalletId() != 0) {
      cout << "ID vi nguon: " << item.getSourceWalletId() << endl;
    }
    if(item.getDestinationWalletId() != 0) {
      cout << "ID vi dich: " << item.getDestinationWalletId() << endl;
    }
    // cout << "ID vi nguon: " << item.getSourceWalletId() << ", ";
    // cout << "ID vi dich: " << item.getDestinationWalletId() << ", ";
    cout << "Loai giao dich: " << item.getType() << endl;
    cout << "So tien: " << item.getAmount() << endl;
    cout << "Thoi gian: " << item.getCreatedDate() << endl;
    cout << "Trang thai: " << item.getStatus() << endl;
  }
  // Print footer
  cout << "---\n";
  cout << "Tong so giao dich: " << transactionList.size() << endl;
}

bool TransactionManager::createSampleData() {
//   Create transaction for master transaction
// 1. Deposit 100.000
// 2. Transfer transactionId 2: 1200, referenceId: REQ2_3
// 3. Transfer transactionId 3: 700, referenceId: REQ4_5
// 4. Transfer transactionId 4: 500, referenceId: REQ6_7
// 5. Transfer transactionId 5: 100, referenceId: REQ8_9
// 6. Receive 100 from transactionId 2, referenceId: REQ12_13
// -> balance: 97.600

// Create transaction for transactionId 2
// 1. Deposit 1200, referenceId: REQ2_3
// 2. Transfer 100 to transactionId 3, referenceId: REQ10_11
// 3. Withdraw 100, referenceId: REQ12_13
// -> balance: 1000

// Create transaction for transactionId 3
// 1. Deposit 700, referenceId: REQ4_5
// 2. Receive 100 from transactionId 2, referenceId: REQ10_11
// -> balance: 800

// Create transaction for transactionId 4
// 1. Deposit 500, referenceId: REQ6_7
// -> balance: 500

// Create transaction for transactionId 5
// 1. Deposit 100, referenceId: REQ8_9
// -> balance: 0
  vector<Transaction> transactionList;
  // master transaction, Deposit 100.000
  Transaction trans_1 = Transaction(1, "", 0, 0, "deposit", 100000, "2025/01/01 20:12:00", "success");
  trans_1.setTransactionId(1);
  transactionList.push_back(trans_1);

  // transactionId 2, Deposit 1200, referenceId: REQ2_3
  Transaction trans_2 = Transaction(2, "REQ2_3", 0, 0, "deposit", 1200, "2025/01/02 20:12:00", "success");
  trans_2.setTransactionId(2);
  transactionList.push_back(trans_2);

  // master transaction, Transfer 1200 to transactionId 2, referenceId: REQ2_3
  Transaction trans_3 = Transaction(1, "REQ2_3", 1, 2, "transfer", 1200, "2025/01/02 20:12:00", "success");
  trans_3.setTransactionId(3);
  transactionList.push_back(trans_3);

  // transactionId 3, Deposit 700, referenceId: REQ4_5
  Transaction trans_4 = Transaction(3, "REQ4_5", 0, 0, "deposit", 700, "2025/01/03 20:12:00", "success");
  trans_4.setTransactionId(4);
  transactionList.push_back(trans_4);

  // master transaction, Transfer 700 to transactionId 3, referenceId: REQ4_5
  Transaction trans_5 = Transaction(1, "REQ4_5", 1, 3, "transfer", 700, "2025/01/03 20:12:00", "success");
  trans_5.setTransactionId(5);
  transactionList.push_back(trans_5);

  // transactionId 4, Deposit 500, referenceId: REQ6_7
  Transaction trans_6 = Transaction(4, "REQ6_7", 0, 0, "deposit", 500, "2025/01/04 20:12:00", "success");
  trans_6.setTransactionId(6);
  transactionList.push_back(trans_6);

  // master transaction, Transfer 500 to transactionId 4, referenceId: REQ6_7
  Transaction trans_7 = Transaction(1, "REQ6_7", 1, 4, "transfer", 500, "2025/01/04 20:12:00", "success");
  trans_7.setTransactionId(7);
  transactionList.push_back(trans_7);

  // transactionId 5, Deposit 100, referenceId: REQ8_9
  Transaction trans_8 = Transaction(5, "REQ8_9", 0, 0, "deposit", 100, "2025/01/05 20:12:00", "success");
  trans_8.setTransactionId(8);
  transactionList.push_back(trans_8);

  // master transaction, Transfer 100 to transactionId 5, referenceId: REQ8_9
  Transaction trans_9 = Transaction(1, "REQ8_9", 1, 5, "transfer", 100, "2025/01/05 20:12:00", "success");
  trans_9.setTransactionId(9);
  transactionList.push_back(trans_9);

  // transactionId 2, Transfer 100 to transactionId 3, referenceId: REQ10_11
  Transaction trans_10 = Transaction(2, "REQ10_11", 2, 3, "transfer", 100, "2025/01/06 12:01:00", "success");
  trans_10.setTransactionId(10);
  transactionList.push_back(trans_10);

  // transactionId 3, Receive 100 from transactionId 2, referenceId: REQ10_11
  Transaction trans_11 = Transaction(3, "REQ10_11", 2, 3, "receive", 100, "2025/01/06 12:01:00", "success");
  trans_11.setTransactionId(11);
  transactionList.push_back(trans_11);

  // transactionId 2, Withdraw 100, referenceId: REQ12_13
  Transaction trans_12 = Transaction(2, "REQ12_13", 0, 0, "withdraw", 100, "2025/01/07 13:13:00", "success");
  trans_12.setTransactionId(12);
  transactionList.push_back(trans_12);

  // master transaction, Receive 100 from transactionId 2, referenceId: REQ12_13
  Transaction trans_13 = Transaction(1, "REQ12_13", 2, 1, "receive", 100, "2025/01/07 13:13:00", "success");
  trans_13.setTransactionId(13);
  transactionList.push_back(trans_13);

  int nextTransactionId = transactionList.size() + 1;
  FileUtils fileUtils(filename, filenameNextId);
  bool result = fileUtils.saveDataByList(*this, transactionList, nextTransactionId);
  return result;
}

void TransactionManager::writeItemToFile(fstream& file, Transaction item) {
  //convert du lieu ghi vao file de khi doc file len du lieu khong bi loi

  string referenceId = item.getReferenceId();
  if(referenceId == "") {
    referenceId = "NULL"; // Neu referenceId rong thi gan la "NULL"
  }

  string sourceWalletId = item.getSourceWalletId() == 0 ? "NULL" : to_string(item.getSourceWalletId());
  string destinationWalletId = item.getDestinationWalletId() == 0 ? "NULL" : to_string(item.getDestinationWalletId());

  file << item.getTransactionId() << ","
       << item.getWalletId() << ","
       << referenceId << ","
       << sourceWalletId << ","
       << destinationWalletId << ","
       << item.getType() << ","
       << item.getAmount() << ","
       << item.getCreatedDate() << ","
       << item.getStatus() << endl;      
}

Transaction TransactionManager::readItemFromFile(stringstream& ss) {
  int transactionId;
  int walletId;
  string referenceId;
  int sourceWalletId;
  int destinationWalletId;
  string type;
  int amount;
  string createdDate;
  string status;

  string token; // Declare token for getline
  getline(ss, token, ',');
  transactionId = stoi(token);
  getline(ss, token, ',');
  walletId = stoi(token);
  getline(ss, token, ',');
  referenceId = token != "NULL" ? token : ""; //Neu lay ra la NULL thi gan la ""
  getline(ss, token, ',');
  sourceWalletId = token != "NULL" ? stoi(token) : 0; //Neu lay ra la NULL thi gan la 0
  getline(ss, token, ',');
  destinationWalletId = token != "NULL" ? stoi(token) : 0;
  getline(ss, type, ',');
  getline(ss, token, ',');
  amount = stoi(token);  
  getline(ss, createdDate, ',');
  getline(ss, status, ',');

   
  //Tao transaction va set transactionId
  Transaction transaction(walletId, referenceId, sourceWalletId, destinationWalletId, type, amount, createdDate, status);
  transaction.setTransactionId(transactionId);
  return transaction;
}

bool TransactionManager::createTransaction(Transaction newTransaction){
  //Lay danh sach transaction va nextTransactionId moi nhat
  bool resultGetList = getList();
  if(resultGetList == false) {
    return false;
  }

  //kiem tra xem transaction_id  va transactionname da ton tai
  int transactionId = nextTransactionId;
  Transaction* transactionExist = findTransactionById(transactionId); 
  if(transactionExist != NULL) {
    string text = "Da ton tai transactionId '" + to_string(transactionId) + " '";
    console.notify(text);
    return false;
  }
  newTransaction.setTransactionId(transactionId); //gan id cho transaction
  nextTransactionId++; //tang nexTransactionId len 1

  FileUtils fileUtils(filename, filenameNextId); 
  bool resultSave = fileUtils.appendItem(*this, newTransaction, nextTransactionId); 
  if(resultSave == true) {
    string text = "Luu thanh cong transaction_id '" + to_string(transactionId) + "'";
    console.notify(text);
    return true;
  } else {
    string text = "Luu that bai transaction_id '" + to_string(transactionId) + "'";
    console.notify(text);
    return false; 
  }
}

Transaction* TransactionManager::findTransactionById(int transactionId){
  //tim kiem transaction co id = transactionId khong  
  for (int i = 0; i < transactionList.size(); i++) {
    if (transactionList[i].getTransactionId() == transactionId) {
      string text = "Tim thay transactionId '" + to_string(transactionId) + "'";
      console.log(text);
      return &transactionList[i]; //tra ve con tro den transaction      
    }
  }
  //Neu khong tim thay transaction thi tra ve NULL
  string text = "Khong tim thay transaction_id '" + to_string(transactionId) + "'";
  console.log(text);
  return NULL;
}

void TransactionManager::findTransactionByWalleIdFromFile(int walletId){
  try {   
    // Mo file de doc
    string fullPath = DATA_DIRECTORY + filename + ".csv"; //lay duong dan file
    ifstream file(fullPath);
    if (!file.is_open()) {
      cerr << "Khong ton tai file '" << fullPath << "'" << endl;
      file.close();
      // return User();
      // return NULL;
    }  
    string line;
    // bool isExist = false;
    Transaction result;
    while (getline(file, line)) {
      stringstream ss(line);          
      result = readItemFromFile(ss);
      if(result.getWalletId() == walletId) {
        transactionList.push_back(result);
      }
    }
    file.close();
    // if(isExist == false) {
    //   string text = "Khong tim thay item trong file '" + fullPath + "'";
    //   console.log(text);
    //   // return NULL;
    // }
    // else {
    //   string text = "Da tim thay item trong file '" + fullPath + "'";
    //   console.log(text);
    //   User* user = new User(result); //tra ve con tro den user tim thay
    //   return user;
    // }    
  }
  catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
    // return NULL;
  }
}

bool TransactionManager::updateStatus(int transactionId, string status){
  //Lay danh sach transaction va nextTransactionId moi nhat
  bool resultGetList = getList();
  if(resultGetList == false) {
    return false;
  }
 
   //kiem tra xem user_id co ton tai
  Transaction* transactionExist = findTransactionById(transactionId);
  if(transactionExist == NULL) {
    string text = "Khong ton tai transactionId '" + to_string(transactionId) + "'";
    console.notify(text);
    return false;
  }

  transactionExist->setStatus(status);

  //Save transactionList vao file, do file van ban thao tac ghi de 1 dong se de bi pha cau truc cua file trong truong hop do dai chuoi thay doi
  //nen phai ghi lai toan bo file
  FileUtils fileUtils(filename, filenameNextId);
  bool resultSave = fileUtils.saveDataByList(*this, transactionList, nextTransactionId);
  return resultSave;
}