# include "../inc/test_map.hpp"

void map_access(void)
{
    print_t("Map Access");

    NAMESPACE::pair<int, int> p1(1, 1);
    NAMESPACE::pair<int, int> p2(2, 2);
    NAMESPACE::pair<int, int> p3(3, 3);

    NAMESPACE::map<int, int> mp;
    mp.insert(p1);
    mp.insert(p2);
    mp.insert(p3);

    std::cout << "Map: " << std::endl;
    print_m(mp);
    std::cout << std::endl;

    print_t("access (operator[])");
    std::cout << " [1] => " << mp[1] << std::endl;
    std::cout << " [3] => " << mp[3] << std::endl;
    std::cout << " [0] => " << mp[0] << std::endl;
    std::cout << std::endl;
    // map[0] should be created
    print_m(mp);
    std::cout << std::endl;

    print_t("assign (operator[]");
    std::cout << "mp[1] before (mp[1] = 42)" << std::endl;
    std::cout << mp[1] << std::endl;
    std::cout << "mp[1] after" << std::endl;
    mp[1] = 42;
    std::cout << mp[1] << std::endl;
    std::cout << "mp[0] before (mp[0] = -21)" << std::endl;
    std::cout << mp[0] << std::endl;
    std::cout << "mp[0] after" << std::endl;
    mp[0] = -21;
    std::cout << mp[0] << std::endl;
    std::cout << std::endl;
    print_m(mp);
    std::cout << std::endl;
}