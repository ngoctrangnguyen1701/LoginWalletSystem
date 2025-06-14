//include file .h tuong ung voi .cpp
#include "TransactionManager.h"
#include "../Application.h"

using namespace std;

//Methods
bool TransactionManager::getList(int walletId){
  FileUtils fileUtils(filename, filenameNextId);
  bool result;
  if(walletId == 0) {
    //walletId == 0 se doc toan bo danh sach
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
    cout << "\n===== Danh sach lich su giao dich dang trong =====\n";
    return;
  }
  
  cout << "\n+-----------------------------------------------------+\n";
  cout << "|             DANH SACH LICH SU GIAO DICH             |\n";
  cout << "+-----------------------------------------------------+\n";
  
  // Print each transaction
  for (int i = 0; i < transactionList.size(); i++) {
    Transaction item = transactionList[i];
    cout << endl;
    cout << "________ ID giao dich: " << item.getTransactionId() << " ________" << endl;
    // cout << "ID vi: " << item.getWalletId() << endl;
    if(item.getReferenceId() != "") {
      cout << "Ma tham chieu: " << item.getReferenceId() << endl;
    }
    if(item.getSourceWalletId() != 0) {
      cout << "ID vi nguon: " << item.getSourceWalletId() << endl;
    }
    if(item.getDestinationWalletId() != 0) {
      cout << "ID vi dich: " << item.getDestinationWalletId() << endl;
    }

    string type = item.getType();
    int amount = item.getAmount();
    string amountStr = formatWithDotSeparator(amount);
    if(type == "deposit") {
      type = "Nap diem";
      amountStr = "+" + formatWithDotSeparator(amount);
    } else if(type == "withdraw") {
      type = "Rut diem";
      amountStr = "-" + formatWithDotSeparator(amount);
    } else if(type == "transfer") {
      type = "Chuyen diem";
      amountStr = "-" + formatWithDotSeparator(amount);
    } else if(type == "receive") {
      type = "Nhan diem";
      amountStr = "+" + formatWithDotSeparator(amount);
    }
    string balanceStr =  formatWithDotSeparator(item.getBalance());
    string statusStr = item.getStatus() == "success" ? "Thanh cong" : "That bai";

    cout << "Loai giao dich: " << type << endl;
    cout << "So tien: " << amountStr << endl;
    cout << "Thoi gian: " << item.getCreatedDate() << endl;
    cout << "Trang thai: " << statusStr << endl;
    cout << "So du: " << balanceStr << endl;
  }
  
  cout << endl;
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
  Transaction trans_1 = Transaction(1, "", 0, 0, "deposit", 100000, "2025/01/01 20:12:00", "success", 100000);
  trans_1.setTransactionId(1);
  transactionList.push_back(trans_1);

  // walletId 2, Deposit 1200, referenceId: REQ2_3
  Transaction trans_2 = Transaction(2, "REQ2_3", 0, 0, "deposit", 1200, "2025/01/02 20:12:00", "success", 1200);
  trans_2.setTransactionId(2);
  transactionList.push_back(trans_2);

  // master transaction, Transfer 1200 to walletId 2, referenceId: REQ2_3
  Transaction trans_3 = Transaction(1, "REQ2_3", 1, 2, "transfer", 1200, "2025/01/02 20:12:00", "success", 98800);
  trans_3.setTransactionId(3);
  transactionList.push_back(trans_3);

  // walletId 3, Deposit 700, referenceId: REQ4_5
  Transaction trans_4 = Transaction(3, "REQ4_5", 0, 0, "deposit", 700, "2025/01/03 20:12:00", "success", 700);
  trans_4.setTransactionId(4);
  transactionList.push_back(trans_4);

  // master transaction, Transfer 700 to walletId 3, referenceId: REQ4_5
  Transaction trans_5 = Transaction(1, "REQ4_5", 1, 3, "transfer", 700, "2025/01/03 20:12:00", "success", 98100);
  trans_5.setTransactionId(5);
  transactionList.push_back(trans_5);

  // walletId 4, Deposit 500, referenceId: REQ6_7
  Transaction trans_6 = Transaction(4, "REQ6_7", 0, 0, "deposit", 500, "2025/01/04 20:12:00", "success", 500);
  trans_6.setTransactionId(6);
  transactionList.push_back(trans_6);

  // master transaction, Transfer 500 to walletId 4, referenceId: REQ6_7
  Transaction trans_7 = Transaction(1, "REQ6_7", 1, 4, "transfer", 500, "2025/01/04 20:12:00", "success", 97600);
  trans_7.setTransactionId(7);
  transactionList.push_back(trans_7);

  // walletId 5, Deposit 100, referenceId: REQ8_9
  Transaction trans_8 = Transaction(5, "REQ8_9", 0, 0, "deposit", 100, "2025/01/05 20:12:00", "success", 100);
  trans_8.setTransactionId(8);
  transactionList.push_back(trans_8);

  // master transaction, Transfer 100 to walletId 5, referenceId: REQ8_9
  Transaction trans_9 = Transaction(1, "REQ8_9", 1, 5, "transfer", 100, "2025/01/05 20:12:00", "success", 97500);
  trans_9.setTransactionId(9);
  transactionList.push_back(trans_9);

  // walletId 2, Transfer 100 to walletId 3, referenceId: REQ10_11
  Transaction trans_10 = Transaction(2, "REQ10_11", 2, 3, "transfer", 100, "2025/01/06 12:01:00", "success", 1100);
  trans_10.setTransactionId(10);
  transactionList.push_back(trans_10);

  // walletId 3, Receive 100 from walletId 2, referenceId: REQ10_11
  Transaction trans_11 = Transaction(3, "REQ10_11", 2, 3, "receive", 100, "2025/01/06 12:01:00", "success", 800);
  trans_11.setTransactionId(11);
  transactionList.push_back(trans_11);

  // walletId 2, Withdraw 100, referenceId: REQ12_13
  Transaction trans_12 = Transaction(2, "REQ12_13", 0, 0, "withdraw", 100, "2025/01/07 13:13:00", "success", 1000);
  trans_12.setTransactionId(12);
  transactionList.push_back(trans_12);

  // master transaction, Receive 100 from walletId 2, referenceId: REQ12_13
  Transaction trans_13 = Transaction(1, "REQ12_13", 2, 1, "receive", 100, "2025/01/07 13:13:00", "success", 97600);
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
       << item.getStatus() << ","     
       << item.getBalance() << endl;      
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
  int balance;

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
  getline(ss, token, ',');
  balance = stoi(token);
   
  //Tao transaction va set transactionId
  Transaction transaction(walletId, referenceId, sourceWalletId, destinationWalletId, type, amount, createdDate, status, balance);
  transaction.setTransactionId(transactionId);
  return transaction;
}

bool TransactionManager::setBalance(Transaction& newTransaction) {
  //Set so du sau khi giao dich thanh cong
  Application& app = Application::getInstance();
  int walletId = newTransaction.getWalletId();
  int balance = app.getWalletMgr().loadBalanceFromFile(walletId);
  if(balance < 0) {
    string text = "Khong load duoc so du walletId '" + to_string(walletId) + "'";
    console.log(text);
    return false; //Tra ve false khi khong load duoc so du
  }
  int amount = newTransaction.getAmount();
  string type = newTransaction.getType();
  if(type == "deposit" || type == "receive") {
    balance = balance + amount;
  }
  else if(type == "withdraw" || type == "transfer") {
    balance = balance - amount;
  }
  newTransaction.setBalance(balance);
  return true;
}

bool TransactionManager::createTransaction(Transaction &newTransaction){
  bool resultBalance = setBalance(newTransaction);
  if(resultBalance == false) {
    return false;
  }

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
    console.log(text);
    return true;
  } else {
    string text = "Luu that bai transaction_id '" + to_string(transactionId) + "'";
    console.log(text);
    return false; 
  }
}

bool TransactionManager::createTransactionList(vector<Transaction>& list){
  int sizeList = list.size();
  for (int i = 0; i < sizeList; i++) {
    bool resultBalance = setBalance(list[i]);
    if(resultBalance == false) {
      return false;
    }
  }
  
  //Lay danh sach transaction va nextTransactionId moi nhat
  bool resultGetList = getList();
  if(resultGetList == false) {
    return false;
  }

  //kiem tra xem transaction_id  va transactionname da ton tai
  string referenceId = "REQ" + to_string(nextTransactionId) + '_' + to_string(nextTransactionId + 1);
  for (int i = 0; i < sizeList; i++) {
    Transaction* transactionExist = findTransactionById(nextTransactionId); 
    if(transactionExist != NULL) {
      string text = "Da ton tai transactionId '" + to_string(nextTransactionId) + " '";
      console.notify(text);
      return false;
    }
    list[i].setTransactionId(nextTransactionId); //gan id cho transaction
    list[i].setReferenceId(referenceId); //gan referenceId cho transaction
    nextTransactionId++; //tang nexTransactionId len 1
  }

  FileUtils fileUtils(filename, filenameNextId); 
  bool resultSave = fileUtils.appendItemList(*this, list, nextTransactionId); 
  if(resultSave == true) {
    string text = "Luu thanh cong danh sach transaction_id";
    console.log(text);
    return true;
  }
  else {
    string text = "Luu that bai danh sach transaction_id";
    console.log(text);
    return true;
  }
}

Transaction* TransactionManager::findTransactionById(int transactionId){
  //tim kiem transaction co id = transactionId khong
  int size = transactionList.size();
  for (int i = 0; i < size; i++) {
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

vector<Transaction> TransactionManager::findTransactionByIds(int transactionId_1, int transactionId_2){
  //tim kiem transaction co id = transactionId khong  
  vector<Transaction> list;
  int size = transactionList.size();
  for (int i = 0; i < size; i++) {
    if (transactionList[i].getTransactionId() == transactionId_1 || transactionList[i].getTransactionId() == transactionId_2) {
      list.push_back(transactionList[i]);
    }
  }
  return list;
}

void TransactionManager::findTransactionByWalleIdFromFile(int walletId){
  try {   
    // Mo file de doc
    string fullPath = DATA_DIRECTORY + filename + ".csv"; //lay duong dan file
    ifstream file(fullPath);
    if (!file.is_open()) {
      cerr << "Khong ton tai file '" << fullPath << "'" << endl;
      file.close();
    }  
    string line;
    Transaction result;
    while (getline(file, line)) {
      stringstream ss(line);          
      result = readItemFromFile(ss);
      if(result.getWalletId() == walletId) {
        transactionList.push_back(result);
      }
    }
    file.close();
  }
  catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
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
  bool resultSave = saveList();
  return resultSave;
}

bool TransactionManager::updateStatus(vector<Transaction> list, string status) {
  bool resultGetList = getList();
  if(resultGetList == false) {
    return false;
  }
  int size = transactionList.size();
  int id_1 = list[0].getTransactionId();
  int id_2 = list[1].getTransactionId();
  Transaction* transaction_1;
  Transaction* transaction_2;
  for (int i = 0; i < size; i++) {    
    if(transactionList[i].getTransactionId() == id_1) {
      transaction_1 = &transactionList[i];
      transaction_1->setStatus(status);
    }

    if(transactionList[i].getTransactionId() == id_2) {
      transaction_2 = &transactionList[i];
      transaction_2->setStatus(status);
    }
  }

  if(transaction_1 == NULL) {
    string text = "Khong ton tai transactionId '" + to_string(id_1) + "'";
    console.notify(text);
    return false;
  }

  if(transaction_2 == NULL) {
    string text = "Khong ton tai transactionId '" + to_string(id_2) + "'";
    console.notify(text);
    return false;
  }
  
  //Save transactionList vao file, do file van ban thao tac ghi de 1 dong se de bi pha cau truc cua file trong truong hop do dai chuoi thay doi
  //nen phai ghi lai toan bo file
  bool resultSave = saveList();
  return resultSave;
}

bool TransactionManager::saveList() {
  FileUtils fileUtils(filename, filenameNextId);
  bool resultSave = fileUtils.saveDataByList(*this, transactionList, nextTransactionId);
  return resultSave;
}
