Manager::Manager(std::string fileName, std::string logFile) : strRecordFile(fileName), strLogFileName(logFile), producthead(new ProductList())
{
    foutLogFile.open(strLogFileName, ios_base::out | ios_base::app);
    foutLogFile.clear();
    foutLogFile.seekp(0, ios_base::beg);
    Logout("successfully open log file");
    system("pause");
    system("cls");
}
void Manager::readRecord()
{
    finRecord.open(strRecordFile, ios_base::in);
    finRecord.clear();
    finRecord.seekg(0, ios_base::beg);
    OUTPUT_HEAD(foutLogFile);
    Product pro;
    while (INPUT_PRODUCT(finRecord, pro))
        producthead->addProduct(&pro);
    finRecord.close();
}
void Manager::updateRecord()
{
    auto str = strRecordFile + ".bak";
    BackupRecord(str);
    remove(strRecordFile.c_str());
    rename(str.c_str(), strRecordFile.c_str());
}
void Manager::backupRecord(std::string fileName)
{
    Logout("backup record");
    ofstream fout(file);
    auto p = producthead;
    auto ptr = ProductList::getProduct(p);
    while(ptr)
    {
        OUTPUT_PRODUCT(fout, ptr);
        ptr = ProductList::getProduct(p);
    }
    fout.close();
    Logout("backup record successfully");
    system("pause");
}
