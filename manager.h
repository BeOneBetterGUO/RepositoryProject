class Manager
{
private:
    std::ifstream finRecord;
    std::ofstream foutRecord;
    std::string strRecordFile;
    std::string strLogFileName;
    ProductList *producthead;

public:
    Manager(std::string fileName, std::string logFile = "info.log");
    ~Manager();

public:
    void ReadRecord();
    void UpdateRecord();
    void BackupRecord();
    void LogoutInfo();
    void Logout(std::string content, bool hasInfo = true);
    void inventorymanager(std::string choice, int extra = ProductList::Condition::ON_NONE, int keyword = -1, std::string extra = nullptr);
};