#ifndef UserWallet_H //Neu chua duoc dinh nghia
#define UserWallet_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

#include "Wallet.h" // Ensure Wallet.h exists and defines the Wallet class or struct

class UserWallet : public Wallet
{
	private:		
	protected:
		int walletId; //auto increase
		int userId; //link to user
		// User* owner;
		int balance;
		bool const isMaster = false; 
		
	public:
		//Contructors
		UserWallet(int userId, int balance);

		//Methods
		bool deposit(int amount);
		bool withdraw(int amount);
		// Transaction* transfer(Wallet* destination, int amount);
		bool transfer(int walletIdDestination, int amount);
};

#endif
