# include "../inc/test_map.hpp"

void map_swap(void)
{
    print_t("Map Swap");
    std::cout << std::endl;
    NAMESPACE::map<char, int> m, m2;

    m['a'] = 1;
    m['b'] = 2;

    m2['z'] = 26;
    m2['y'] = 25;

    std::cout << "before swap" << std::endl;
    NAMESPACE::map<char, int>::iterator it = m.begin();
    for (; it != m.end(); ++it)
    {
        std::cout << "first map1: " << it->first << std::endl;
        std::cout << "second map1: " << it->second << std::endl;
    }
    std::cout << std::endl;
    
    NAMESPACE::map<char, int>::iterator it2 = m2.begin();
    for (; it2 != m2.end(); ++it2)
    {
        std::cout << "first map2: " << it2->first << std::endl;
        std::cout << "second map2: " << it2->second << std::endl;
    }
    std::cout << std::endl;

    m.swap(m2);
    std::cout << "after swap" << std::endl;
    NAMESPACE::map<char, int>::iterator it_2 = m.begin();
    for (; it_2 != m.end(); ++it_2)
    {
        std::cout << "first map1: " << it_2->first << std::endl;
        std::cout << "second map1: " << it_2->second << std::endl;
    }
    std::cout << std::endl;
    
    NAMESPACE::map<char, int>::iterator it2_2 = m2.begin();
    for (; it2_2 != m2.end(); ++it2_2)
    {
        std::cout << "first map2: " << it2_2->first << std::endl;
        std::cout << "second map2: " << it2_2->second << std::endl;
    }
    std::cout << std::endl;
}