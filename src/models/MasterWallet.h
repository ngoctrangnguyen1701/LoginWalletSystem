#ifndef MasterWallet_H //Neu chua duoc dinh nghia
#define MasterWallet_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

#include "Wallet.h"

class MasterWallet : public Wallet
{
	private:		
	protected:
	public:
		//Contructors
		MasterWallet(int userId, int balance);

		//Methods
		bool deposit(int amount);
		bool withdraw(int amount);
		// Transaction* transfer(Wallet* destination, int amount);
};

#endif
