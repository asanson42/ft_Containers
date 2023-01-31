# include "../inc/test_map.hpp"

void map_compare(void)
{
    print_t("Map Overload");

    NAMESPACE::map<char, int> mp, mp2;

    mp['a'] = 5;
    mp['b'] = 11;

    mp2['a'] = 5;
    mp2['b'] = 11;

    print_t("mp");
    print_m(mp);
    std::cout << std::endl;
    print_t("mp2");
    print_m(mp2);
    std::cout << std::endl;

    print_t("mp == mp2");
    if (mp == mp2) std::cout << "mp and mp2 are equal" << std::endl;
    print_t("mp != mp2");
    if (mp != mp2) std::cout << "mp and mp2 are not equal" << std::endl;
    print_t("mp <= mp2");
    if (mp <= mp2) std::cout << "mp is less than or equal to mp2" << std::endl;
    print_t("mp >= mp2");
    if (mp >= mp2) std::cout << "mp is greater than or equal to mp2" << std::endl;
    print_t("mp < mp2");
    if (mp < mp2) std::cout << "mp is less than mp2" << std::endl;
    print_t("mp > mp2");
    if (mp > mp2) std::cout << "mp is greater than mp2" << std::endl;
    std::cout << std::endl;

    print_t("change mp['a'] = 21");
    mp['a'] = 21;
    print_t("change mp['b'] = 42");
    mp['b'] = 42;

    print_t("mp");
    print_m(mp);
    std::cout << std::endl;
    print_t("mp2");
    print_m(mp2);
    std::cout << std::endl;

     print_t("mp == mp2");
    if (mp == mp2) std::cout << "mp and mp2 are equal" << std::endl;
    print_t("mp != mp2");
    if (mp != mp2) std::cout << "mp and mp2 are not equal" << std::endl;
    print_t("mp <= mp2");
    if (mp <= mp2) std::cout << "mp is less than or equal to mp2" << std::endl;
    print_t("mp >= mp2");
    if (mp >= mp2) std::cout << "mp is greater than or equal to mp2" << std::endl;
    print_t("mp < mp2");
    if (mp < mp2) std::cout << "mp is less than mp2" << std::endl;
    print_t("mp > mp2");
    if (mp > mp2) std::cout << "mp is greater than mp2" << std::endl;
    std::cout << std::endl;
}