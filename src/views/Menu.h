#ifndef Menu_H //Neu chua duoc dinh nghia
#define Menu_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

#include <vector>
#include <string>
using namespace std;

#include "../models/User.h"
#include "../utils/ConsoleUtils.h"

class Menu
{
	private:		
	protected:
		string title;
		vector<string> options;
		string selectedOption; //chon kieu string de tranh nguoi dung nhap hon 1 ky tu
		bool isRunning;
		ConsoleUtils console;
	public:
		// Constructor
		Menu(string title);
		
		//Destructor
		virtual ~Menu(); 

		void setIsRunning(bool x);
		bool getIsRunning();
		void printHeader();

		//Lop thuan ao, bat buoc lop con phai co override
		virtual void display() = 0;
		virtual void handleInput() = 0;
};

#endif
