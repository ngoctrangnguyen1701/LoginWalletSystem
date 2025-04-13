#ifndef MasterWallet_H //Neu chua duoc dinh nghia
#define MasterWallet_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

#include "Wallet.h"

class MasterWallet : public Wallet
{
	private:		
	protected:
		int walletId; //auto increase
		int userId; //link to user
		// User* owner;
		int balance;
		bool const isMaster = true;

	public:
		//Methods
		bool deposit(int amount);
		bool withdraw(int amount);
		// Transaction* transfer(Wallet* destination, int amount);
};

#endif
