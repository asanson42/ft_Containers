#include "../inc/test_map.hpp"

static void map_const_str(void)
{
    print_t("Map Constructor (with string)");
    NAMESPACE::pair<int, std::string> p1(1, "str1");
    NAMESPACE::pair<int, std::string> p2(2, "str2");
    NAMESPACE::pair<int, std::string> p3(3, "str3");
    
    print_t("default const");
    NAMESPACE::map<int, std::string> mp;
    mp.insert(p1);
    mp.insert(p2);
    mp.insert(p3);
    print_m(mp);
    std::cout << std::endl;

    print_t("copy const");
    NAMESPACE::map<int, std::string> mpcpy(mp);
    std::cout << "clear default map" << std::endl;
    mp.clear();
    std::cout << "print cpy map" << std::endl;
    print_m(mpcpy);
    std::cout << "print default map" << std::endl;
    print_m(mp);

    print_t("iterator const");
    std::vector<NAMESPACE::pair<int, std::string> > v;
    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);

    mp.insert(v.begin(), v.end());
    print_m(mp);
}

static void map_const_it(void)
{
    print_t("Map Constructor (with iterators)");
    
    typedef NAMESPACE::map<int, std::string>::value_type Pair;

    std::list<Pair> lst;
    std::list<Pair>::iterator it;

    lst.push_back(Pair(1, "str1"));
    lst.push_back(Pair(2, "str2"));
    lst.push_back(Pair(3, "str3"));
    lst.push_back(Pair(4, "str4"));

    std::cout << "size lst" << lst.size() << std::endl;
    for (it = lst.begin(); it != lst.end(); ++it)
    {
        print_pair(it);
    }
    std::cout << std::endl;

    NAMESPACE::map<int, std::string> mp(lst.begin(), lst.end());
    std::cout << "lst clear & print map" << std::endl;
    lst.clear();
    print_m(mp);
}

void map_const(void)
{
    map_const_str();
    map_const_it();

}