#include "../inc/test_vector.hpp"

void vector_it(void)
{
    std::list<int> lst;
    for (int i = 0; i < 5; i++)
    {
        lst.push_back(i + 1);
    }
    
    NAMESPACE::vector<int> v(lst.begin(), lst.end());

    print_t("vector iterators");
    print_v(v);

    NAMESPACE::vector<int>::iterator it = v.begin();
    print_t("begin()");
    std::cout << *it << std::endl;
    std::cout << std::endl;
    NAMESPACE::vector<int>::reverse_iterator rit = v.rbegin();
    print_t("rbegin()");
    std::cout << *rit << std::endl;
    std::cout << std::endl;
}