#include "../inc/test_vector.hpp"

static void default_const(void)
{
    NAMESPACE::vector<int> v;
    
    print_t("default constructor");
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    print_v(v);
}

static void fill_const(void)
{
    NAMESPACE::vector<int> v(5, 42);

    print_t("fill constructor");
    print_v(v);
}

static void it_const(void)
{
    std::list<int> lst;
    for (int i = 0; i < 5; i++)
    {
        lst.push_back(i + 1);
    }

    NAMESPACE::vector<int> v(lst.begin(), lst.end());
    NAMESPACE::vector<int> v2(lst.rbegin(), lst.rend());

    print_t("iterator constructor");

    print_t("lst.begin -> lst.end");
    print_v(v);
    std::cout << std::endl;
    print_t("lst.rbegin -> lst.rend");
    print_v(v2);
    std::cout << std::endl;
}

static void cpy_const(void)
{
    std::list<int> lst;
    for (int i = 0; i < 5; i++)
    {
        lst.push_back(i + 1);
    }

    NAMESPACE::vector<int> v(lst.begin(), lst.end());
    NAMESPACE::vector<int> vcpy(v);

    print_t("copy constructor");
    print_t("vector");
    print_v(v);
    std::cout << std::endl;
    print_t("copy vector");
    print_v(vcpy);
    std::cout << std::endl; 
    print_t("clear vector...");
    v.clear();
    print_t("copy vector after clear");
    print_v(vcpy);
    std::cout << std::endl;  
}

void vector_const(void)
{
    default_const();
    fill_const();
    it_const();
    cpy_const();
}