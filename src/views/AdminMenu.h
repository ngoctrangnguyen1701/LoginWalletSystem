#ifndef AdminMenu_H //Neu chua duoc dinh nghia
#define AdminMenu_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

#include "Menu.h"
class AdminMenu : public Menu
{
	private:		
	protected:
	public:
		AdminMenu();
		void display() override;
		void handleInput() override;
		void handleReadUserList();
		void handleCreateUser();
		void handleUpdateUser();
		void handleDeleteUser();
};

#endif
