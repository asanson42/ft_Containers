#include "../inc/test_map.hpp"

void map_bound(void)
{
    NAMESPACE::map<char, int>   mp;
    NAMESPACE::map<char, int>::iterator itl, itl2, itu, itu2;

    print_t("Map Bound");

    mp['a'] = 1;
    mp['c'] = 5;
    mp['e'] = 11;
    mp['g'] = 15;
    print_m(mp);

    itl = mp.lower_bound('c');
    itl2 = mp.lower_bound('e');
    itu = mp.upper_bound('a');
    itu2 = mp.upper_bound('c');

    print_t("lower bound('c')");
    print_pair(itl);
    print_t("upper bound('c')");
    print_pair(itu2);
    std::cout << std::endl;
    print_t("lower bound('e')");
    print_pair(itl2);
    print_t("upper bound('a')");
    print_pair(itu);
    std::cout << std::endl;
}