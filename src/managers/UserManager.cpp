//include file .h tuong ung voi .cpp
#include "UserManager.h"

//Methods
bool UserManager::createUser(User newUser){
  //Lay danh sach user va nextUserId moi nhat
  bool resultGetList = getList();
  if(resultGetList == false) {
    return false;
  }

  //kiem tra xem user_id  va username da ton tai
  int userId = nextUserId;
  User* userExist = findUserById(userId); 
  if(userExist != NULL) {
    if(userExist->getUserId() == userId) {
      string text = "Da ton tai userId '" + to_string(userId) + " '";
      console.notify(text);
      return false;
    }
    if(userExist->getUsername() == newUser.getUsername()) {
      string text = "Da ton tai ten dang nhap '" + newUser.getUsername() + " '";
      console.notify(text);
      return false;
    }
  }
  newUser.setUserId(userId); //gan id cho user
  nextUserId++; //tang nexUserId len 1

  FileUtils fileUtils(filename, filenameNextId); 
  bool resultSave = fileUtils.appendItem(*this, newUser, nextUserId); 
  if(resultSave == true) {
    string text = "Luu thanh cong user_id '" + to_string(userId) + "'";
    console.log(text);
    return true;
  } else {
    string text = "Luu that bai user_id '" + to_string(userId) + "'";
    console.log(text);
    return false; 
  }
}

bool UserManager::getList(){
  FileUtils fileUtils(filename, filenameNextId); 
  bool result = fileUtils.loadFile(*this, userList, nextUserId);
  return result;
}

vector<User> UserManager::getList_2(){
  getList();
  return userList;
}

void UserManager::displayList() {
  bool resultGetList = getList(); //Doc danh sach user tu file
  if(resultGetList == false) {
    console.notify("Khong the doc danh sach nguoi dung");
    return;
  }
  // Check if list is empty
  if (userList.empty()) {
    cout << "\n===== Danh sach nguoi dung dang trong =====\n";
    return;
  }
  
  // Calculate the width of each column to display
  const int idWidth = 6;
  const int usernameWidth = 15;
  const int fullNameWidth = 25;
  const int emailWidth = 30;
  
  cout << "\n+-------------------------------------------------------------------------------+\n";
  cout << "|                           DANH SACH NGUOI DUNG                                |";
  cout << "\n+------+---------------+-------------------------+------------------------------+\n";
  cout << "| " << setw(idWidth-1) << left << "ID" << "|";
  cout << " " << setw(usernameWidth-1) << left << "Ten dang nhap" << "|";
  cout << " " << setw(fullNameWidth-1) << left << "Ho va ten" << "|";
  cout << " " << setw(emailWidth-1) << left << "Email" << "|";
  cout << "\n+------+---------------+-------------------------+------------------------------+\n";
  
  // Print each user
  for (int i = 0; i < userList.size(); i++) {
    User item = userList[i];
    cout << "|" << setw(idWidth-1) << right << item.getUserId() << " |";
    cout << " " << setw(usernameWidth-1) << left << item.getUsername() << "|";
    cout << " " << setw(fullNameWidth-1) << left << item.getFullName() << "|";
    cout << " " << setw(emailWidth-1) << left << item.getEmail() << "|";
    cout << endl;
  }
  
  cout << "+------+---------------+-------------------------+------------------------------+\n";
  cout << "Tong so nguoi dung: " << userList.size() << endl;
}

bool UserManager::updateUser(int userId, string fullName, string email, string passwordHash, string isAutoGenPassword) {
  //Lay danh sach user va nextUserId moi nhat
  bool resultGetList = getList();
  if(resultGetList == false) {
    return false;
  }

  //kiem tra xem user_id co ton tai
  User* userExist = findUserById(userId);
  if(userExist == NULL) {
    string text = "Khong ton tai userId '" + to_string(userId) + "'";
    console.notify(text);
    return false;
  }

  if(fullName != "") {
    userExist->setFullName(fullName);
  }
  if(email != "") {
    userExist->setEmail(email);
  }
  if(passwordHash != "") {
    userExist->setPasswordHash(passwordHash);
  }
  if(isAutoGenPassword != "") {
    bool isAutoGen = isAutoGenPassword == "true" ? true : false;
    userExist->setIsAutoGenPassword(isAutoGen);
  }

  //Save userList vao file, do file van ban thao tac ghi de 1 dong se de bi pha cau truc cua file trong truong hop do dai chuoi thay doi
  //nen phai ghi lai toan bo file
  FileUtils fileUtils(filename, filenameNextId);
  bool resultSave = fileUtils.saveDataByList(*this, userList, nextUserId);
  return resultSave;
}

bool UserManager::deleteUser(int userId){
  //Lay danh sach user va nextUserId moi nhat
  bool resultGetList = getList();
  if(resultGetList == false) {
    return false;
  }

  //kiem tra xem user_id co ton tai
  User* userExist = findUserById(userId);
  if(userExist == NULL) {
    string text = "Khong ton tai userId '" + to_string(userId) + "'";
    console.notify(text);
    return false;
  }

  //Xoa user khoi danh sach
  for (int i = 0; i < userList.size(); i++) {
    if (userList[i].getUserId() == userId) {
      userList.erase(userList.begin() + i); //Xoa user khoi danh sach
      break;
    }
  }  

  //Save userList vao file, do file van ban thao tac ghi de 1 dong se de bi pha cau truc cua file trong truong hop do dai chuoi thay doi
  //nen phai ghi lai toan bo file
  FileUtils fileUtils(filename, filenameNextId);
  bool resultSave = fileUtils.saveDataByList(*this, userList, nextUserId);
  return resultSave;
}

User* UserManager::findUserFromFile(string username, string password){
  try {   
    // Mo file de doc
    string fullPath = DATA_DIRECTORY + filename + ".csv"; //lay duong dan file
    ifstream file(fullPath);
    if (!file.is_open()) {
      cerr << "Khong ton tai file '" << fullPath << "'" << endl;
      file.close();
      // return User();
      return NULL;
    }  
    string line;
    bool isExist = false;
    User result;
    while (getline(file, line)) {
      stringstream ss(line);          
      result = readItemFromFile(ss);
      //Ma hoa bam mat khau truyen vao va so sanh voi ma bam trong file du lieu
      string passwordHash = HashUtils::generateHash(password, result.getPasswordSalt());
      if(result.getUsername() == username && result.getPasswordHash() == passwordHash) {
        isExist = true;
        break;
      }
    }
    file.close();
    if(isExist == false) {
      string text = "Khong tim thay item trong file '" + fullPath + "'";
      console.log(text);
      return NULL;
    }
    else {
      string text = "Da tim thay item trong file '" + fullPath + "'";
      console.log(text);
      User* user = new User(result); //tra ve con tro den user tim thay
      return user;
    }    
  }
  catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
    return NULL;
  }
}

User* UserManager::findUserById(int userId){
  //tim kiem user co id = userId khong  
  for (int i = 0; i < userList.size(); i++) {
    if (userList[i].getUserId() == userId) {
      string text = "Tim thay userId '" + to_string(userId) + "'";
      console.log(text);
      return &userList[i]; //tra ve con tro den user      
    }
  }
  //Neu khong tim thay user thi tra ve NULL
  string text = "Khong tim thay user_id '" + to_string(userId) + "'";
  console.log(text);
  return NULL;
}

User* UserManager::findUserByConditionFromFile(string key, string value) {
  try {   
    // Mo file de doc
    string fullPath = DATA_DIRECTORY + filename + ".csv"; //lay duong dan file
    ifstream file(fullPath);
    if (!file.is_open()) {
      cerr << "Khong the mo file '" << fullPath << "'" << endl;
      file.close();
      return NULL;
    }  
    string line;
    bool isExist = false;
    User result;
    while (getline(file, line)) {
      stringstream ss(line);          
      result = readItemFromFile(ss);
      if(key == "userId") {
        int userId = stoi(value);
        if(result.getUserId() == userId) {
          isExist = true;
          break;
        }
      }
      else if(key == "username") {
        if(result.getUsername() == value) {
          isExist = true;
          break;
        }
      }
    }
    file.close();
    if(isExist == false) {
      string text = "Khong tim thay item trong file '" + fullPath + "'";
      console.log(text);
      return NULL;
    }
    else {
      string text = "Da tim thay item trong file '" + fullPath + "'";
      console.log(text);
      User* user = new User(result); //tra ve con tro den user tim thay
      return user;
    }    
  }
  catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
    return NULL;
  }
}

bool UserManager::createSampleData() {
  vector<User> userList;
  userList.push_back(User("admin", "123", "Administrator", "admin@example.com", true, false));
  userList.push_back(User("binhduong", "binhduong123", "Binh Duong", "binhduong@example.com", false, false));
  userList.push_back(User("vungtau", "vungtau123", "Vung Tau", "vungtau@example.com", false, false));
  userList.push_back(User("trian", "trian123", "Tri An", "trian@example.com", false, false));
  userList.push_back(User("vinhhy", "vinhhy123", "Vinh Hy", "vinhhy@example.com", false, false));
  userList.push_back(User("nuicam", "nuicam123", "Thien Cam Son", "nuicam@example.com", false, false));  

  for (int i = 0; i < userList.size(); i++) {
    userList[i].setUserId(i + 1);
  }
  int nextUserId = userList.size() + 1;
  FileUtils fileUtils(filename, filenameNextId);
  bool result = fileUtils.saveDataByList(*this, userList, nextUserId);
  return result;
}

User UserManager::readItemFromFile(stringstream& ss) {
  int userId; 
  string username;
  string passwordHash;
  string passwordSalt;
  string fullName;
  string email;
  bool isAdmin;
  bool isAutoGenPassword;

  string token; // Declare token for getline
  
  getline(ss, token, ',');
  userId = stoi(token);
  getline(ss, username, ',');
  getline(ss, passwordHash, ',');
  getline(ss, passwordSalt, ',');
  getline(ss, fullName, ',');
  getline(ss, email, ',');
  getline(ss, token, ',');
  isAdmin = (token == "1"); //cho nay se ra true or false
  getline(ss, token);
  isAutoGenPassword = (token == "1"); //cho nay se ra true or false
    
  //Tao user va set userId
  User user(username, passwordHash, passwordSalt, fullName, email, isAdmin, isAutoGenPassword);
  user.setUserId(userId);
  return user;
};

void UserManager::writeItemToFile(fstream& file, User item) {
  file << item.getUserId() << ","
      << item.getUsername() << ","
      << item.getPasswordHash() << ","
      << item.getPasswordSalt() << ","
      << item.getFullName() << ","
      << item.getEmail() << ","
      << item.getIsAdmin() << ","
      << item.getIsAutoGenPassword() << endl;
};
