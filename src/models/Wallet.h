#ifndef Wallet_H //Neu chua duoc dinh nghia
#define Wallet_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

#include "../models/Transaction.h"
#include "../managers/TransactionManager.h"
#include "../utils/DateTimeUtils.h"

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
		// bool adminDeposist(int amount);
		// bool adminWithdraw(int amount);
		// bool userDepoist(int amount);
		// bool adminWithdraw(int amount);
		
		// Transaction* transfer(Wallet* destination, int amount);
};

#endif
