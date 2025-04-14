#ifndef WalletManager_H //Neu chua duoc dinh nghia
#define WalletManager_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

class WalletManager
{
		vector<Wallet> walletList; //TODO: gioi han danh sach 100 wallet, 1 admin duy nhat, 99 wallet binh thuong, pagination
		int nextWalletId; //auto increase
		string filename = "walletData"; //ten file luu wallet
		string filenameNextId = "nextWalletId"; //ten file luu nextWalletId
		ConsoleUtils console; // Khai bao doi tuong ConsoleUtils
	protected:
	public:
		//Destructor
		~WalletManager();

		//Methods
		// bool createWallet(Wallet newWallet);
		// bool getList();
		// void displayList();
		// bool updateWallet(int walletId, string fullName, string email);
		// bool deleteWallet(int walletId); // -> then deleteTransaction;
		// Wallet* findWalletFromFile(string walletname, string password);
		// Wallet* findWalletById(int walletId);
		// Wallet* findWalletByIdFromFile(int walletId);
		// bool saveWalletToFile(Wallet newWallet);		
		bool createSampleData();
		// Wallet readItemFromFile(stringstream& ss); //Doc wallet tu file
		// void writeItemToFile(fstream& file, Wallet item); //Ghi wallet vao file
		// bool loadWalletsFromFile(string filename);
		// bool backupWalletData();
		// bool restoreWalletData();

		friend class Application;
};

#endif
