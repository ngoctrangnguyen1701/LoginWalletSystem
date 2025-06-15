#ifndef WalletManager_H //Neu chua duoc dinh nghia
#define WalletManager_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip> 

//include file header noi bo khac
#include "../models/Wallet.h"
#include "../models/MasterWallet.h"
#include "../models/UserWallet.h"
#include "../managers/UserManager.h"
#include "../utils/FileUtils.h"
#include "../utils/ConsoleUtils.h"
#include "../utils/Utils.h"

using namespace std;

class WalletManager
{
		vector<Wallet> walletList;
		int nextWalletId; //auto increase
		string filename = "walletData"; //ten file luu wallet
		string filenameNextId = "nextWalletId"; //ten file luu nextWalletId
		ConsoleUtils console; // Khai bao doi tuong ConsoleUtils
	protected:
	public:
		//Methods
		bool createWallet(Wallet newWallet);
		bool getList();
		void displayList();
		bool updateBalance(int walletId, int amount, string type); //type la 'increment' hoac la 'decrement'
		bool updateBalanceTwoWallets(int walletId_1, int amount_1, string type_1, int walletId_2, int amount_2, string type_2); //type la 'increment' hoac la 'decrement'
		bool updateBalanceNotSave(Wallet* wallet, int amount, string type);
		Wallet* findWalletById(int walletId);
		vector<Wallet> findWalletByIds(int walletId_1, int walletId_2);
		Wallet* findWalletByIdFromFile(int walletId);
		Wallet* findWalletByUserId(int userId);
		Wallet* findWalletByUserIdFromFile(int userId);
		bool createSampleData();
		Wallet readItemFromFile(stringstream& ss); //Doc wallet tu file
		void writeItemToFile(fstream& file, Wallet item); //Ghi wallet vao file
		bool saveList();
		bool checkValidDecrement(int userId, int amount); //Kiem tra balance co hop le, type la 'increment' hoac la 'decrement'
		int loadBalanceFromFile(int walletId);

		friend class Application;
		friend class BackupManager;
};

#endif
