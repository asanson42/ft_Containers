# include "../inc/test_map.hpp"

void map_it(void)
{
    print_t("Map iterators");

    typedef NAMESPACE::pair<const char, int> Pair;

    std::list<Pair> lst;
    for (int i = 0; i < 5; i++)
    {
       lst.push_back(Pair('a' + i, i));
    }

    NAMESPACE::map<const char, int> mp(lst.begin(), lst.end());
    NAMESPACE::map<const char, int>::iterator it = mp.begin();
    NAMESPACE::map<const char, int>::reverse_iterator rit(it);
    NAMESPACE::map<const char, int>::reverse_iterator rite;

    print_m(mp);
    std::cout << std::endl;
    std::cout << "before increment rit" << std::endl;
    --rit;
    print_pair(rit);
    std::cout << "after increment (--) rit" << std::endl;
    --rit;
    print_pair(rit);
    std::cout << std::endl;

    std::cout << "rbegin() -> rend()" << std::endl;
    rit = mp.rbegin();
    rite = mp.rend();
    for (; rit != rite; rit++)
    {
        print_pair(rit);
    }
    std::cout << std::endl;
}