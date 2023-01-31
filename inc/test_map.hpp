#ifndef TEST_MAP_HPP
# define TEST_MAP_HPP
# include "test_utils.hpp"
# include <vector>
# include <list>
# ifdef USESTL
#   include <map>
# else
#   include "map.hpp"
# endif
#endif

# include <iostream>

void map_bound(void);
void map_const(void);
void map_access(void);
void map_erase(void);
void map_find(void);
void map_it(void);
void map_insert(void);
void map_obs(void);
void map_swap(void);
void map_compare(void);

template <typename T>
void print_pair(const T &it)
{
    std::cout << " [" << it->first << "]";
    std::cout << " -> " <<  it->second << std::endl;
}

template <typename map>
void print_m(map const &m, bool content = true)
{
    typedef typename map::const_iterator m_it;

    std::cout << "[size]:  " << m.size() << std::endl;
    std::cout << "[content]:  " << std::endl;

    if (content)
    {
        m_it it = m.begin();
        m_it ite = m.end();

        for (; it != ite; ++it)
        {
            print_pair(it);
        }
    }
    std::cout << std::endl;
}