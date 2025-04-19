//include file .h tuong ung voi .cpp
#include "TransactionManager.h"

//include thu vien
#include <iostream>
#include <fstream>
#include <iomanip> 

//include file header noi bo khac
#include "../models/Transaction.h"
#include "../utils/FileUtils.h"

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
bool TransactionManager::createSampleData() {
//   Create transaction for master wallet
// 1. Deposit 100.000
// 2. Transfer walletId 2: 1200, referenceId: REQ2_3
// 3. Transfer walletId 3: 700, referenceId: REQ4_5
// 4. Transfer walletId 4: 500, referenceId: REQ6_7
// 5. Transfer walletId 5: 100, referenceId: REQ8_9
// 6. Receive 100 from walletId 2, referenceId: REQ12_13
// -> balance: 97.600

// Create transaction for walletId 2
// 1. Deposit 1200, referenceId: REQ2_3
// 2. Transfer 100 to walletId 3, referenceId: REQ10_11
// 3. Withdraw 100, referenceId: REQ12_13
// -> balance: 1000

// Create transaction for walletId 3
// 1. Deposit 700, referenceId: REQ4_5
// 2. Receive 100 from walletId 2, referenceId: REQ10_11
// -> balance: 800

// Create transaction for walletId 4
// 1. Deposit 500, referenceId: REQ6_7
// -> balance: 500

// Create transaction for walletId 5
// 1. Deposit 100, referenceId: REQ8_9
// -> balance: 0
  vector<Transaction> transactionList;
  // master wallet, Deposit 100.000
  Transaction trans_1 = Transaction(1, "", 0, 0, "deposit", 100000, "2025/01/01 20:12:00", "success");
  trans_1.setTransactionId(1);
  transactionList.push_back(trans_1);

  // walletId 2, Deposit 1200, referenceId: REQ2_3
  Transaction trans_2 = Transaction(2, "REQ2_3", 0, 0, "deposit", 1200, "2025/01/02 20:12:00", "success");
  trans_2.setTransactionId(2);
  transactionList.push_back(trans_2);

  // master wallet, Transfer 1200 to walletId 2, referenceId: REQ2_3
  Transaction trans_3 = Transaction(1, "REQ2_3", 1, 2, "transfer", 1200, "2025/01/02 20:12:00", "success");
  trans_3.setTransactionId(3);
  transactionList.push_back(trans_3);

  // walletId 3, Deposit 700, referenceId: REQ4_5
  Transaction trans_4 = Transaction(3, "REQ4_5", 0, 0, "deposit", 700, "2025/01/03 20:12:00", "success");
  trans_4.setTransactionId(4);
  transactionList.push_back(trans_4);

  // master wallet, Transfer 700 to walletId 3, referenceId: REQ4_5
  Transaction trans_5 = Transaction(1, "REQ4_5", 1, 3, "transfer", 700, "2025/01/03 20:12:00", "success");
  trans_5.setTransactionId(5);
  transactionList.push_back(trans_5);

  // walletId 4, Deposit 500, referenceId: REQ6_7
  Transaction trans_6 = Transaction(4, "REQ6_7", 0, 0, "deposit", 500, "2025/01/04 20:12:00", "success");
  trans_6.setTransactionId(6);
  transactionList.push_back(trans_6);

  // master wallet, Transfer 500 to walletId 4, referenceId: REQ6_7
  Transaction trans_7 = Transaction(1, "REQ6_7", 1, 4, "transfer", 500, "2025/01/04 20:12:00", "success");
  trans_7.setTransactionId(7);
  transactionList.push_back(trans_7);

  // walletId 5, Deposit 100, referenceId: REQ8_9
  Transaction trans_8 = Transaction(5, "REQ8_9", 0, 0, "deposit", 100, "2025/01/05 20:12:00", "success");
  trans_8.setTransactionId(8);
  transactionList.push_back(trans_8);

  // master wallet, Transfer 100 to walletId 5, referenceId: REQ8_9
  Transaction trans_9 = Transaction(1, "REQ8_9", 1, 5, "transfer", 100, "2025/01/05 20:12:00", "success");
  trans_9.setTransactionId(9);
  transactionList.push_back(trans_9);

  // walletId 2, Transfer 100 to walletId 3, referenceId: REQ10_11
  Transaction trans_10 = Transaction(2, "REQ10_11", 2, 3, "transfer", 100, "2025/01/06 12:01:00", "success");
  trans_10.setTransactionId(10);
  transactionList.push_back(trans_10);

  // walletId 3, Receive 100 from walletId 2, referenceId: REQ10_11
  Transaction trans_11 = Transaction(3, "REQ10_11", 2, 3, "receive", 100, "2025/01/06 12:01:00", "success");
  trans_11.setTransactionId(11);
  transactionList.push_back(trans_11);

  // walletId 2, Withdraw 100, referenceId: REQ12_13
  Transaction trans_12 = Transaction(2, "REQ12_13", 0, 0, "withdraw", 100, "2025/01/07 13:13:00", "success");
  trans_12.setTransactionId(12);
  transactionList.push_back(trans_12);

  // master wallet, Receive 100 from walletId 2, referenceId: REQ12_13
  Transaction trans_13 = Transaction(1, "REQ12_13", 2, 1, "receive", 100, "2025/01/07 13:13:00", "success");
  trans_13.setTransactionId(13);
  transactionList.push_back(trans_13);

  int nextTransactionId = transactionList.size() + 1;
  FileUtils fileUtils(filename, filenameNextId);
  bool result = fileUtils.saveDataByList(*this, transactionList, nextTransactionId);
  return result;
}

void TransactionManager::writeItemToFile(fstream& file, Transaction& item) {
  file << item.getTransactionId() << ","
       << item.getWalletId() << ","
       << item.getReferenceId() << ","
       << item.getSourceWalletId() << ","
       << item.getDestinationWalletId() << ","
       << item.getType() << ","
       << item.getAmount() << ","
       << item.getCreatedDate() << ","
       << item.getStatus() << endl;      
}
