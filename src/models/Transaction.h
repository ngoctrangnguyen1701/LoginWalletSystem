#ifndef Transaction_H //Neu chua duoc dinh nghia
#define Transaction_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

#include <string>
using namespace std;

class Transaction
{
	private:
		int transactionId; //auto increase
		int walletId; //id vi phat sinh giao dich
		string referenceId; // (dung de lien ket giao dich chung cua 2 vi voi nhau, theo format REQid1_id2, vd: REQ1_2)
		int sourceWalletId; //id cu vi nguon
		int destinationWalletId; //id cua vi dich
		string type; // ("deposit", "withdraw", "transfer", "receive" "deleteWallet" -> for master wallet)
		int amount;
		string createdDate; //format theo yyyy/mm/dd hh:mm:ss
		string status; // ("success", "failed")
		int balance; //So du khi giao dich xong
	protected:
	public:
		// Constructors
		Transaction() = default;
		Transaction(int walletId, string referenceId, int sourceWalletId, int destinationWalletId, string type, int amount, string createdDate, string status);
		Transaction(int walletId, string referenceId, int sourceWalletId, int destinationWalletId, string type, int amount, string createdDate, string status, int balance);

		//Setters
		void setTransactionId(int transactionId);
		void setReferenceId(string referenceId);
		void setStatus(string status);
		void setBalance(int balance);

		//Getters
		int getTransactionId();
		int getWalletId();
		string getReferenceId();
		int getSourceWalletId();
		int getDestinationWalletId();
		string getType();
		int getAmount();
		string getCreatedDate();
		string getStatus();
		int getBalance();
};

#endif
