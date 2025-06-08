#ifndef UserMenu_H //Neu chua duoc dinh nghia
#define UserMenu_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

#include "Menu.h"
class UserMenu : public Menu
{
	private:
		bool isReloadLogin = false; //load lai menu dang nhap neu nguoi dung yeu cau doi mat khau
	protected:
	public:
		UserMenu();
		void display() override;
		void handleInput() override;
		void handleChangeInfo();
		void handleChangePassword();
};

#endif
