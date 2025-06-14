//include file .h tuong ung voi .cpp
#include "Transaction.h"

//Contructors
Transaction::Transaction(int walletId, string referenceId, int sourceWalletId, int destinationWalletId, string type, int amount, string createdDate, string status) {
  this->walletId = walletId;
  this->referenceId = referenceId;
  this->sourceWalletId = sourceWalletId;
  this->destinationWalletId = destinationWalletId;
  this->type = type;
  this->amount = amount;
  this->createdDate = createdDate;
  this->status = status;
}

Transaction::Transaction(int walletId, string referenceId, int sourceWalletId, int destinationWalletId, string type, int amount, string createdDate, string status, int balance) {
  this->walletId = walletId;
  this->referenceId = referenceId;
  this->sourceWalletId = sourceWalletId;
  this->destinationWalletId = destinationWalletId;
  this->type = type;
  this->amount = amount;
  this->createdDate = createdDate;
  this->status = status;
  this->balance = balance;
}

//Setters
void Transaction::setTransactionId(int transactionId){
  this->transactionId = transactionId;
};
void Transaction::setReferenceId(string referenceId){
  this->referenceId = referenceId;
};
void Transaction::setStatus(string status){
  this->status = status;
};
void Transaction::setBalance(int balance){
  this->balance = balance;
};

//Getters
int Transaction::getTransactionId(){
    return transactionId;
};
int Transaction::getWalletId(){
  return walletId;
};
string Transaction::getReferenceId(){
  return referenceId;
};
int Transaction::getSourceWalletId(){
  return sourceWalletId;
};
int Transaction::getDestinationWalletId(){
  return destinationWalletId;
};
string Transaction::getType(){
  return type;
};
int Transaction::getAmount(){
  return amount;
};
string Transaction::getCreatedDate(){
  return createdDate;
};
string Transaction::getStatus(){
  return status;
};
int Transaction::getBalance(){
  return balance;
};

//Methods
