#ifndef Wallet_H //Neu chua duoc dinh nghia
#define Wallet_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien
#include <string>

#include "../models/Transaction.h"
#include "../managers/TransactionManager.h"

class Wallet
{
	private:		
	protected:
		int walletId; //auto increase
		int userId; //link to user
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
};

#endif
