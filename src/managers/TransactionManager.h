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
#include "../utils/Utils.h"

using namespace std;

class TransactionManager
{
	private:
		vector<Transaction> transactionList; //Danh sach lich su giao dich
		int nextTransactionId; //auto increase
		string filename = "transactionData"; //ten file luu transaction
		string filenameNextId = "nextTransactionId"; //ten file luu nextTransactionId
		ConsoleUtils console; // Khai bao doi tuong ConsoleUtils		
	protected:
	public:
		//Methods
		bool getList(int walletId = 0); //walletId = 0 la lay toan bo lich su giao dich trong file du lieu
		void displayList(int walletId = 0);
		bool createSampleData();
		Transaction readItemFromFile(stringstream& ss); //Doc wallet tu file
		void writeItemToFile(fstream& file, Transaction item); //Ghi ransaction vao file
		bool createTransaction(Transaction& newTransaction);
		bool createTransactionList(vector<Transaction>& list);
		Transaction* findTransactionById(int transactionId);
		vector<Transaction> findTransactionByIds(int transactionId_1, int transactionId_2);
		void findTransactionByWalleIdFromFile(int walletId);
		bool updateStatus(int transactionId, string status);
		bool updateStatus(vector<Transaction> list, string status);
		bool saveList();
		bool setBalance(Transaction& newTransaction); //set gia tri so du sau khi giao dich xong

		friend class Application;
		friend class BackupManager;
};

#endif
