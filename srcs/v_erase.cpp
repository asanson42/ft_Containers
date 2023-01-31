#include "../inc/test_vector.hpp"

void vector_erase(void)
{
    std::list<std::string> lst;
    for (int i = 0; i < 6; i++)
    {
        lst.push_back(std::string(3, 'a' + i));
    }

    NAMESPACE::vector<std::string> v(lst.begin(), lst.end());

    print_t("before erase");
    print_v(v);
    std::cout << std::endl;
    print_t("after erase(begin(), begin() + 2");
    v.erase(v.begin(), v.begin() + 2);
    print_v(v);
    std::cout << std::endl;

    print_t("before erase");
    print_v(v);
    std::cout << std::endl;
    print_t("erase(end() - 1");
    v.erase(v.end() - 1);
    print_v(v);
    std::cout << std::endl;
}