ProductList::ProductList() : products(nullptr), productNext(nullptr)
{
    if (!(head || tail))
    {
        head = this;
        tail = this;
    }
}

// 函数参数为待插入的产品对象地址，ptr值有两种
// 1. 从product.txt文件中读取的产品对象地址，则ptr为非nullptr
// 2. 从键盘输入的产品对象地址，则ptr为nullptr
void ProductList::addProduct(const Product *ptr)
{
    Product pro;
    if (!ptr)
    {
        cout << "please input the product information" << endl;
        OUOTPUT_HEAD(cout);
        INPUT_PRODUCT(cin, pro);
    }
    else
    {
        pro = *ptr;
    }
    // 将待插节点的产品型号、名称、品牌同链表现有节点进行比较
    // 若存在内容相同的节点，用p记录链表节点地址，否则p为nullptr
    auto p = isSameProduct(pro);
    if (p)
    {
        cout << "the product already exists, the system will merge the product" << endl;
        cout << "the original product information is as follows:" << endl;
        OUTPUT_HEAD(cout);
        OUTPUT_PRODUCT(cout, p->product);
        int total = p->product->price * p->product->count + pro->price * pro->count;
        p->product->count += pro->count;
        p->product->price = total / p->product->count;
        cout << "the product information after merging is as follows:" << endl;
        OUTPUT_PRODUCT(cout, p->product);
        cout << endl;
        return;
    }
    if (tail)
    {
        tail->product = new Product(pro);
        tail->productNext = new ProductList();
        tail = tail->productNext;
    }
}

/*
参数说明：
type t: 产品属性编号
condition c: 搜索条件, 如若查询条件为“相等”，则c为1
std::string str: 具体的属性内容
*/
ProductList *ProductList::SearchProduct(Type t, Condition c, std::string str) const
{
    int val;
    Condition res;
    const char *s = str.c_str();
    auto p = head;
    auto pList = new ProductList();
    auto phead = pList;
    sscanf(s, "%d", &val);
    while (p->product)
    {
        switch (t)
        {
        case TYPE_SERIAL:
            COMPARE_WITH(p, serial, str, res);
            break;
        case TYPE_NAME:
            COMPARE_WITH(p, name, str, res);
            break;
        case TYPE_BRAND:
            COMPARE_WITH(p, brand, str, res);
            break;
        case TYPE_PRICE:
            COMPARE_WITH(p, price, val, res);
            break;
        case TYPE_COUNT:
            COMPARE_WITH(p, count, val, res);
            break;
        }
        if (c == res)
        {
            pList->product = p->product;
            pList->productNext = new ProductList();
            pList = pList->productNext;
        }
        p = p->productNext;
    }
    return phead->product ? phead : nullptr;
}

void ProductList::SortProductByType(Type t)
{
    auto p = head;
    if (!p->productNext)
    {
        p.showAllProduct();
        return;
    }

    ProductList *pTemp;
    for (auto i = p; i->productNext->product;)
    {
        pTemp = i;
        auto j = i->productNext;
        while (j->product)
        {
            if (compareByType(type, pTemp, j) > 0)
                pTemp = j;
            j = j->productNext;
        }
        Swap(i, pTemp);
        i = i->productNext;
    }
}

void ProductList::InsertProduct(const ProductList *product, int num)
{
    ProductList *pThis = IsProductExist(product, num);
    if (!pThis)
        return;
    int i = 0;
    Product pro;
    auto pNext = pThis->productNext;
    while (i++ < num)
    {
        cout << "please input the product information" << endl;
        OUTPUT_HEAD(cout);
        INPUT_PRODUCT(cin, pro);
        auto p = isSameProduct(pro);
        if (p)
        {
            p->product->count += pro.count;
            continue;
        }
        pThis->productNext = new ProductList();
        pThis = pThis->productNext;
        pThis->product = new Product(pro);
        pThis->productNext = pNext;
    }
    return;
}

void ProductList::SellProduct(const ProductList *product, int num)
{
    auto p = isProductExist(product, SELECT::SELECT_FIRST);
    if (p)
    {
        cout << "show the product information" << endl;
        OUTPUT_HEAD(cout);
        OUTPUT_PRODUCT(cout, p->product);
        p->product->count -= num;
        if (p->product->count <= 0)
        {
            cout << "the num sold out is " << p->product->count + num << " and the product will be deleted" << endl;
            deleteProduct(p);
        }
    }
}

void ProductList::DeleteProduct(const ProductList *product, int num)
{
    int i = 0;
    auto p = product;
    ProductList *pThis;
    ProductList *pNext;
    ProductList *pFront;
    if (product == head)
    {
        delete product->product;
        head = head->productNext;
        delete product;
        return;
    }
    while (i++ < num)
    {
        if (!p->product)
        {
            cout << "Warning: param product == nullptr!" << endl;
            return;
        }
        pFront = getFrontProduct(p);
        pThis = isProductExist(p, num);
        if (!pThis)
        {
            cout << "Warning: param pThis == nullptr!" << endl;
            return;
        }
        p = p->productNext;
        pNext = pThis->productNext;
        delete pThis->product;
        delete pThis;
        if (pFront)
            pFront->productNext = pThis = pNext;
    }
    return;
}

void ProductList::EditProduct(const ProductList *product, int num)
{
    Product pro;
    auto p = product;
    ProductList *pSame;
    ProductList *pThis;

    while (p->product)
    {
        pThis = isProductExist(p, ProductList::SELECT::SELECT_FIRST);
        if (pThis)
        {
            cout << "the info of the product as belows:" << endl;
            OUTPUT_PRODUCT(cout, pThis->product);
            cout << "please input new info: " << endl;
            INPUT_PRODUCT(cin, pro);
            pSame = isSameProduct(pro);
            if (!pSame || pSame->product == p->product)
                COPY_PRODUCT(pThis->product, pro);
            else
            {
                deleteProduct(pThis);
                pSame->product->count += pro.count;
            }
            cout << "edit successfully, please press ENTER to edit more" << endl;
            cin.get();
            cin.get();
        }
        else
            break;
        p = p->productNext;
    }
    cout << "edit done" << endl;
}

void ProductList::ShowAllProduct(ProductList *h) const{
    OUTPUT_HEAD(cout);
    auto p = h;
    while(p->product)
    {
        OUTPUT_PRODUCT(cout , p->product);
        p = p->productNext;
    }
}