#ifndef Wallet_H //Neu chua duoc dinh nghia
#define Wallet_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

class Wallet
{
	private:		
	protected:
		int walletId; //auto increase
		int userId; //link to user
		// User* owner;
		int balance;
		bool isMaster;

	public:
		// Constructor
		Wallet() = default;
		Wallet(int userId, int balance, bool isMaster);

		//Setters
		void setWalletId(int walletId);
		void setBalance(int walletId);

		//Getters
		int getWalletId();
		int getUserId();
		int getBalance();
		bool getIsMaster();

		//Methods
		
		// Transaction* transfer(Wallet* destination, int amount);
};

#endif
