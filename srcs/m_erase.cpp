
#include "../inc/test_map.hpp"

template <typename Map, typename T>
void erase_print(Map &mp, T v)
{
    // v = value
    mp.erase(v);
    print_m(mp);
}

template <typename Map, typename T1, typename T2>
void erase_print(Map &mp, T1 strt, T2 end)
{
    mp.erase(strt, end);
    print_m(mp);
}

typedef NAMESPACE::pair<const int, std::string> Pair;

void map_erase(void)
{
    print_t("Map Erase");

    std::list<Pair> lst;

    lst.push_back(Pair(1, "str1"));
    lst.push_back(Pair(2, "str2"));
    lst.push_back(Pair(3, "str3"));
    lst.push_back(Pair(4, "str4"));
    lst.push_back(Pair(5, "str5"));

    NAMESPACE::map<int, std::string> mp(lst.begin(), lst.end());
    print_m(mp);
    std::cout << std::endl;

    print_t("erase begin()");
    erase_print(mp, mp.begin());
    std::cout << std::endl;

    print_t("erase begin() -> end()");
    erase_print(mp, mp.begin(), mp.end());
}