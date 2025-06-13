#ifndef TransactionManager_H //Neu chua duoc dinh nghia
#define TransactionManager_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>  

//include file header noi bo khac
#include "../models/Transaction.h"
#include "../utils/FileUtils.h"
#include "../utils/ConsoleUtils.h"

using namespace std;

class TransactionManager
{
	private:
		vector<Transaction> transactionList; //TODO: pagination
		int nextTransactionId; //auto increase
		string filename = "transactionData"; //ten file luu transaction
		string filenameNextId = "nextTransactionId"; //ten file luu nextTransactionId
		ConsoleUtils console; // Khai bao doi tuong ConsoleUtils		
	protected:
	public:
		//Destructor
		~TransactionManager();

		//Methods
		bool getList(int walletId = 0); //walletId = 0 la lay toan bo lich su giao dich trong file du lieu
		void displayList(int walletId = 0);
		bool createSampleData();
		Transaction readItemFromFile(stringstream& ss); //Doc wallet tu file
		void writeItemToFile(fstream& file, Transaction item); //Ghi ransaction vao file
		bool createTransaction(Transaction& newTransaction);
		bool createTransactions(Transaction& newTransaction_1, Transaction& newTransaction_2);
		Transaction* findTransactionById(int transactionId);
		vector<Transaction> findTransactionByIds(int transactionId_1, int transactionId_2);
		void findTransactionByWalleIdFromFile(int walletId);
		bool updateStatus(int transactionId, string status);
		bool updateStatus(int transactionId_1, string status_1, int transactionId_2, string status_2);
		bool saveList();

		friend class Application;
		friend class BackupManager;
};

#endif
