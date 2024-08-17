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
void Manager::backupRecord(std::string file)
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

/*
参数说明:
1. choice: 用户的选择。
2. keyword: 属性选项。
3. extra: 操作条件。
4. sextra: 与keyword对应的属性内容。
*/
void Manager::invertoryManager(std::string choice, int extra, int keyword, std::string sextra)
{
    producthead = ProductList::getListHead();
    if(choice == "1")
    {
        Logout("show all product");
        producthead->showAllProduct();
        Logout("show all product successfully");
    }
    else if(choice == "2")
    {
        Logout("search by condition");
        auto p = producthead->searchProduct(static_cast<Type>(keyword), static_cast<ProductList::Condition>(extra), sextra);
        if(!p)
        {
            cout << "----------no product found----------" << endl;
            return;
        }
        p->showAllProduct(p);
        Logout("search by condition successfully");
        ProductList::deleteProductList(p);
    }
    else if(choice == "3")
    {
        Logout("sort by condition");
        producthead->sortProductByType(static_cast<Type>(keyword));
        producthead->showAllProduct();
        Logout("sort by condition successfully");
    }
    else if(choice == "4")
    {
        Logout("add product");
        for(auto i = 0; i < extra; i++)
        {
            cout << "please input the " << i + 1 << " product" << endl;
            producthead->addProduct();
        }
        Logout("add product successfully");
    }
    else if(choice == "5")
    {
        Logout("sell product");
        auto p = producthead->searchProduct(static_cast<Type>(keyword), ProductList::Condition::ON_EQUAL, sextra);
        if(!p)
        {
            cout << "----------no product found----------" << endl;
            return;
        }
        producthead->sellProduct(p, extra);
        Logout("sell product successfully");
        ProductList::deleteProductList(p);
    }
    else if(choice=="6")
    {
        Logout("modify product");
        auto p = producthead->searchProduct(static_cast<Type>(keyword), static_cast<ProductList::Condition>(extra), sextra);
        if(!p)
        {
            cout << "----------no product found----------" << endl;
            return;
        }
        producthead->editProduct(p, ProductList::Select::SELECT_FIRST);
        Logout("modify product successfully");
        ProductList::deleteProductList(p);
    }
    else if(choice=="7")
    {
        Logout("insert product by condition");
        auto p = producthead->searchProduct(static_cast<Type>(keyword), ProductList::Condition::ON_EQUAL, sextra);
        if(!p)
        {
            cout << "no found the insert place" << endl;
            return;
        }
        producthead->insertProduct(p, extra);
        Logout("insert product by condition successfully");
    }
    else if(choice == "8")
    {
        Logout("store product");
        UpdateRecord();
        Logout("store product successfully");
    }
    else if(choice == "9")
    {
        Logout("thanks for using this system");
        system("pause");
        return;
}
Manager::~Manager()
{
    foutLogFile.close();
    ProductList::deleteProductList(producthead);
}