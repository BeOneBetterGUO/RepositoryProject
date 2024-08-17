Control::Control():manager("product.txt");
{
    Menu::mainMenu();
    cout << "Enter your choice: ";
    cin >> choice;
    if(choice == "2")
    exit(EXIT_SUCCESS);
    else if(choice == "1")
    {
        system("pause");
        system("cls");
        manager.readRecord();//read record from file
        mainControl();
    }
}


/**
 * @brief 主控制函数，处理用户输入并调用相应的管理操作。
 * 
 * 该函数是程序的主控制逻辑，负责处理用户输入并调用相应的功能。
 * 它通过一个无限循环不断显示菜单并处理用户的选择，直到用户选择退出。
 * 
 * @details
 * 函数流程如下：
 * 1. 初始化变量 `extra`, `keyword` 和 `sExtra`。
 * 2. 进入一个无限循环，直到用户选择退出。
 * 3. 调用 `Menu::subMenu()` 显示子菜单。
 * 4. 提示用户输入选择，并读取输入到 `choice`。
 * 5. 根据用户的选择执行不同的操作：
 *    - 如果选择 '2'：提示用户输入搜索条件，并读取 `keyword` 和 `sExtra`。
 *    - 如果选择 '3'：提示用户输入排序条件，并读取 `keyword`。
 *    - 如果选择 '4'：提示用户输入产品类型，并读取 `extra`。
 *    - 如果选择 '5'：提示用户输入销售条件，并读取 `keyword`, `extra` 和 `sExtra`。
 *    - 如果选择 '6'：提示用户输入修改条件，并读取 `keyword`, `extra` 和 `sExtra`。
 *    - 如果选择 '7'：提示用户输入插入条件，并读取 `keyword`, `extra` 和 `sExtra`。
 * 6. 调用 `manager.inventorymanager(choice, extra, keyword, sExtra)` 执行相应的管理操作。
 * 7. 如果选择 '9'：退出循环，结束函数。
 * 8. 调用 `system("pause")` 暂停程序，等待用户按键。
 * 9. 调用 `system("cls")` 清屏。
 * 
 * 参数的含义分别为:
 * 1. choice: 用户的选择。
 * 2. keyword: 执行子功能时按哪个产品属性进行搜索或排序。如为0时,按产品型号操作。
 * 3. extra: 执行子功能时堆keyword对应的属性按那种方法进行操作。
 * 4. sExtra: 根据keyword,输入具体的属性内容。
 * 
 * @note
 * - 该函数依赖于 `Menu::subMenu()` 函数来显示菜单。
 * - 该函数依赖于 `Manager::inventorymanager()` 函数来执行具体的管理操作。
 * - 该函数使用了 `system("pause")` 和 `system("cls")` 来控制控制台的暂停和清屏。
 */
void Control::mainControl()
{
    int extra = 0;
    int keyword = -1;
    std::string sExtra;
    while (true)
    {
        Menu::subMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == "2")
        {
            OUTPUT_ATTRIBUTE_CHOICE(cout, "search by condition");
            cin >> keyword;
            OUTPUT_CONDITION_INFO(cout, "search by condition", keyword, false);
            cin >> sExtra;
        }
        else if (choice == "3")
        {
            cout << "please input the index of sorting by condition: ";
            cout << "0. product id\n1. product name\n2. product type\n3. product price\n4. product quantity\n";
            cin >> keyword;
        }
        else if (choice == "4")
        {
            cout << "please input the product type: ";
            cin >> extra;
        }
        else if (choice == "5")
        {
            OUTPUT_INFO(cout, "sell by condition", false);
            cin >> keyword >> extra >> sExtra;
        }
        else if (choice == "6")
        {
            OUTPUT_INFO(cout, "modify by condition", false);
            cin >> keyword >> extra >> sExtra;
        }
        else if(choice == "7")
        {
            OUTPUT_INFO(cout, "insert by condition", false);
            cin >> keyword >> extra >> sExtra;
        }
        manager.inventorymanager(choice, extra, keyword, sExtra);
        if(choice == "9")
        {
            return;
        }
        system("pause");
        system("cls");
    }
}