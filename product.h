// #include <string>

struct Product
{
    std::string serial;
    std::string name;
    std::string brand;
    int price;
    int count;
};
enum Type
{
    TYPE_SERIAL,
    TYPE_NAME,
    TYPE_BRAND,
    TYPE_PRICE,
    TYPE_COUNT
};