#ifndef Utils_H //Neu chua duoc dinh nghia
#define Utils_H //Dinh nghia no
//tranh include nhieu lan trong cac file .cpp khi su dung chung file header

#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>

using namespace std;

// Ham tra ve chuoi thoi gian hien tai dang YYYY/MM/DD HH:MM:SS
inline string getCurrentDateTimeFormatted() {
  time_t now = time(0);                 // Lay thoi gian hien tai (tinh bang giay)
  struct tm* t = localtime(&now);       // Chuyen thanh thoi gian cuc bo (local time)

  char buffer[20];                      // Bo dem luu chuoi thoi gian
  sprintf(buffer, "%04d/%02d/%02d %02d:%02d:%02d",
  t->tm_year + 1900,            // Nam bat dau tu 1900
  t->tm_mon + 1,                // Thang bat dau tu 0
  t->tm_mday,                   // Ngay trong thang
  t->tm_hour,                   // Gio
  t->tm_min,                    // Phut
  t->tm_sec);                   // Giay

  return string(buffer); // Tra ve chuoi thoi gian
};

// Dinh dang so nguyen: them dau cham moi 3 chu so tu phai sang trai
inline string formatWithDotSeparator(int number) {
  string numStr = to_string(number);
  string result;
  int count = 0;

  for (int i = numStr.length() - 1; i >= 0; i--) {
    result = numStr[i] + result;
    count++;
    if (count % 3 == 0 && i != 0) {
      result = '.' + result;
    }
  }

  return result;
}

#endif
