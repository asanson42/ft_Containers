# include "../inc/test_map.hpp"
#include <stdlib.h>

typedef NAMESPACE::map<int, int>::value_type Pair;
typedef NAMESPACE::map<int, int>::iterator m_it;

template <typename Map, typename T>
void m_insert(Map &mp, T val)
{
    NAMESPACE::pair<m_it, bool> res;

    std::cout << "Try insert :" << std::endl;
    std::cout << " [" << val.first << "]";
    std::cout << " -> " <<  val.second << std::endl;

    res = mp.insert(val);
    std::cout << "Created: " << (res.second ? "y" : "n") << std::endl;
    print_m(mp);
    std::cout << std::endl;
}

template <typename Map, typename T1, typename T2>
void m_insert(Map &mp, T1 it, T2 val)
{
    m_it res;

    std::cout << "Try insert :" << std::endl;
    std::cout << " [" << val.first << "]";
    std::cout << " -> " <<  val.second << std::endl;

    res = mp.insert(it, val);
    std::cout << "Created: " << (res->second ? "y" : "n") << std::endl;
    print_m(mp);
    std::cout << std::endl;
}

void map_insert(void)
{
    NAMESPACE::map<int, int> mp;
    NAMESPACE::map<int, int> mp2;

    print_t("Map Insert");

    std::cout << "insertion" << std::endl;
    m_insert(mp, Pair(1, 11));
    m_insert(mp, Pair(42, 42));
    std::cout << "insertion a same key" << std::endl;
    m_insert(mp, Pair(1, 111));
    std::cout << "insertion a same value" << std::endl;
    m_insert(mp, Pair(0, 11));    
    std::cout << "insertion pair" << std::endl;
    m_insert(mp, mp.begin(), Pair(2, 22));

    print_t("Map insert with ::Make_pair");

    NAMESPACE::map<int, int> map_int;
    for (int i = 0; i < 15; i++)
	{
		map_int.insert(NAMESPACE::make_pair(i, i));
	}
    print_m(map_int);
    std::cout << std::endl;
}