# include "../inc/test_map.hpp"

void map_find(void)
{
    print_t("Map Find");

    NAMESPACE::map<int, int> mp;
    NAMESPACE::map<int, int>::iterator it;

    mp[1] = 1;
    mp[2] = 22;
    mp[3] = 333;
    mp[4] = 4444;
    
    print_m(mp);
    std::cout << std::endl;

    it = mp.find(2);
    std::cout << "erase(find(2))" << std::endl;
    if (it != mp.end())
        mp.erase(it);
    print_m(mp);
    std::cout << std::endl;

    print_t("Map Count");
    
    NAMESPACE::map<char, int> mp2;
    char c;

    mp2['a'] = 1;
    mp2['b'] = 2;
    mp2['c'] = 3;
    mp2['e'] = 4;

    print_m(mp2);
    std::cout << std::endl;

    for (c = 'a'; c < 'f'; c++)
    {
        std::cout << "c : " << c << std::endl;
        if (mp2.count(c) > 0)
            std::cout << "c is in map" << std::endl;
        else
            std::cout << "c not is in map" << std::endl;
    }
    std::cout << std::endl;
}