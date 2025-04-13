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
		bool isMaster; //if true, userId is null

	public:
		// Constructor
		// Wallet();

		//Methods
		int getBalance();
		//Lop thuan ao, bat buoc lop con phai co override		
		virtual bool deposit(int amount) = 0;
		virtual bool withdraw(int amount) = 0;
		// Transaction* transfer(Wallet* destination, int amount);
};

#endif
