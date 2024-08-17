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