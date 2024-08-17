class ProductList{
    public:
    enum Select{
        SELECT_ALL = -1,
        SELECT_FIRST = 1;
    };
    enum Condition{
        ON_NONE =0,
        ON_EQUAL = 0x01,
        ON_LESS = 0x02,
        ON_GREATER = 0x03,
    };
    private:
    Product* products;
    ProductList* productNext;
    private:
    static ProductList* head;
    static ProductList* tail;
    public:
    static void deleteProductList(ProductList*& product);
    static const Product* getProduct(ProductList*& p);
    static bool isSame(const Product* p1, const Product& p2);
    static ProductList *getListHead();
    public:
    ProductList();
    ~ProductList();
    private:
    void Swap(ProductList* p1, ProductList* p2);
    int compareByType(Type type, const Product* p1, const Product* p2);
    ProductList* isSameProduct(const Product* p) const;
    ProductList* getFrontProduct(const ProductList* p);
    ProductList* isProductExist(const Product* p, int num);
    public:
    void addProduct(const Product* p = nullptr);
    void insertProduct(const ProductList* product, int num = SELECT_FIRST);
    void sellProduct(const ProductList* product, int num = SELECT_FIRST);
    void deleteProduct(const ProductList* product, int num = SELECT_FIRST);
    ProductList* searchProduct(Type type, Condition c, std::string str)const;
    void showAllProduct(ProductList *head = head)const;
    void sortProductByType(Type type);
    void editProduct(const ProductList* product, int num = SELECT_FIRST);
    void showProduct(const ProductList* product, int num = SELECT_FIRST);
};