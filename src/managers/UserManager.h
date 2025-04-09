#ifndef UserManager_H //Neu chua duoc dinh nghia
#define UserManager_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

//include thu vien
#include <vector>
#include <string>

//include file header noi bo khac
#include "../models/User.h"
#include "../utils/ConsoleUtils.h"

using namespace std;

class UserManager
{
		vector<User> userList; //TODO: gioi han danh sach 100 user, 1 admin duy nhat, 99 user binh thuong, pagination
		int nextUserId; //auto increase
		string filename = "userData"; //ten file luu user
		string filenameNextId = "nextUserId"; //ten file luu nextUserId
		ConsoleUtils console; // Khai bao doi tuong ConsoleUtils
	protected:
	public:
		//Destructor
		~UserManager();

		//Methods
		bool createUser(User newUser);
		bool getList(); //-> page size = 10
		void displayList(); //-> page size = 10
		bool updateUser(int userId, string fullName, string email);
		bool deleteUser(int userId); // -> then deleteWallet;
		User* findUserFromFile(string username, string password);
		User* findUserById(int userId);
		User* findUserByIdFromFile(int userId);
		string generateRandomPassword();
		string hashPassword(string plainPassword);
		// bool saveUserToFile(User newUser);		
		bool createSampleData();
		User readItemFromFile(stringstream& ss); //Doc user tu file
		void writeItemToFile(fstream& file, User item); //Ghi user vao file
		// bool loadUsersFromFile(string filename);
		bool backupUserData();
		bool restoreUserData();

		friend class Application;
};

#endif
