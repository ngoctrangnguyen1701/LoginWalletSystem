template <typename T, typename M>
bool FileUtils::saveDataByList(M &classManager, vector<T> data, int nextId) {
  //Mo file goc de doc, dam bao file goc ton tai
  fstream file(fullPath, ios::in);
  if (!file.is_open()) {
    cerr << "Khong ton tai file '" << fullPath << "'" << endl;
    file.close();
    exit(1);    
  }

  //Tao file tam de ghi, dam bao file tam khong co du lieu
  fstream tempFile(tempFilePath, ios::out | ios::trunc);
  if (!tempFile.is_open()) {
    cerr << "Khong the tao file '" << tempFilePath << "'" << endl;
    tempFile.close();
    exit(1);
  }

  //Ghi tung item vao file tam
  for (int i = 0; i < data.size(); i++) {
    T item = data[i];
    classManager.writeItemToFile(tempFile, item);
  }
  //Dong ca 2 file
  tempFile.close();
  file.close();

  //Thay the file goc bang file tam
  remove(fullPath.c_str());
  rename(tempFilePath.c_str(), fullPath.c_str());
  string text = "Da luu du lieu vao file '" + fullPath + "'";
  console.log(text);

  //Tao file luu tru cho nextUserId, dam bao file luu nextId xoa het du lieu cu
  ofstream fileNextId(nextIdFilePath, ios::trunc);
  if (!fileNextId.is_open()) {
    cerr << "Khong the tao file '" << nextIdFilePath << "'" << endl;
    fileNextId.close();
    exit(1);    
  }
  fileNextId << nextId << endl;
  fileNextId.close();
  text = "Da luu du lieu nextId vao file '" + nextIdFilePath + "'";
  console.log(text);
  return true;
}

template <typename T, typename M>
bool FileUtils::loadFile(M &classManager, vector<T> &data, int &nextId) {
  try {   
    // Mo file de doc
    ifstream file(fullPath);
    if (!file.is_open()) {
      cerr << "Khong the mo file '" << fullPath << "'" << endl;
      file.close();
      return false;
    }
  
    // Xoa du lieu cu
    data.clear();
    string line;
    while (getline(file, line)) {
      stringstream ss(line);          
      //lay tung gia tri          
      T item = classManager.readItemFromFile(ss);
      data.push_back(item);
    }
  
    file.close();
    string text = "Da doc du lieu danh sach tu file '" + fullPath + "'";
    console.log(text);

    //Doc nextId tu file *.txt
    ifstream fileNextId(nextIdFilePath);
    if (!fileNextId.is_open()) {
      cerr << "Khong ton tai file '" << nextIdFilePath << "'" << endl;
      fileNextId.close();
      return false;
    }
    fileNextId >> nextId;
    fileNextId.close();
    text = "Da doc du lieu nextId tu file '" + nextIdFilePath + "'";
    console.log(text);

    return true;
  }
  catch (const exception &e) {
    cerr << "Error: " << e.what() << endl;
    return false;  
  }
}

template <typename T, typename M>
bool FileUtils::appendItem(M &classManager, const T& item, int nextId) {
  try {
    fstream file(fullPath, ios::in | ios::out | ios::app);
    if (!file.is_open()) {
      cerr << "Khong ton tai file '" << fullPath << "'" << endl;
      file.close();
      return false;
    }
    
    classManager.writeItemToFile(file, item);    
    file.close();
    string text = "Da luu du lieu moi vao file '" + fullPath + "'";
    console.log(text);

    //Tao file luu tru cho nextUserId      
    ofstream fileNextId(nextIdFilePath);
    if (!fileNextId.is_open()) {
      cerr << "Khong the tao file '" << nextIdFilePath << "'" << endl;
      fileNextId.close();
      exit(1);    
    }
    fileNextId << nextId << endl;
    fileNextId.close();
    text = "Da luu du lieu moi nextId vao file '" + nextIdFilePath + "'";
    console.log(text);
    return true;
    
  } catch (const exception& e) {
    cerr << "Error: " << e.what() << endl;        
    return false;
  }
}
