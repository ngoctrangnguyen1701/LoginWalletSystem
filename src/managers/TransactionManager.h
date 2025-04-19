#ifndef TransactionManager_H //Neu chua duoc dinh nghia
#define TransactionManager_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien
#include <vector>
#include <string>
#include <fstream>

//include file header noi bo khac
#include "../models/Transaction.h"
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
		bool createSampleData();
		void writeItemToFile(fstream& file, Transaction& item); //Ghi ransaction vao file

		friend class Application;
};

#endif
