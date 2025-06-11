#ifndef UserWallet_H //Neu chua duoc dinh nghia
#define UserWallet_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien
#include <string>

//include file header noi bo khac
#include "Wallet.h"

class UserWallet : public Wallet
{
	private:		
	protected:
	public:
		//Contructors
		UserWallet();
		UserWallet(int userId, int balance);

		//Methods
		bool deposit(int amount);
		bool withdraw(int amount);
		// Transaction* transfer(Wallet* destination, int amount);
		bool transfer(int walletIdDestination, int amount);
};

#endif
