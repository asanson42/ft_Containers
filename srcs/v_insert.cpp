#include "../inc/test_vector.hpp"

void vector_insert(void)
{
    NAMESPACE::vector<int> v(5, 0);
    NAMESPACE::vector<int> v2(v);
    NAMESPACE::vector<int> v3(v);

    print_t("vector insert");

    print_t("vector v2");
    print_v(v2);
    std::cout << std::endl;
    print_t("insert [42] -> begin() + 1");
    v2.insert(v2.begin() + 1, 42);
    print_v(v2);
    std::cout << std::endl;

    print_t("vector insert range");
    std::list<int> lst;
    for (int i = 0; i < 5; i++)
    {
        lst.push_back(i);
    }
    print_t("vector v3");
    print_v(v3);
    std::cout << std::endl;
    print_t("insert with lst.begin(), lst.end()");
    v3.insert(v3.begin(), lst.begin(), lst.end());
    print_v(v3);
    std::cout << std::endl;
}