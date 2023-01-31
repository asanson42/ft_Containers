#include "../inc/test_vector.hpp"

void vector_compare(void)
{
    std::list<int> lst;
    for (int i = 0; i < 5; i++)
    {
        lst.push_back(i + 1);
    }
    
    print_t("Vector Overload");
    NAMESPACE::vector<int> v(lst.begin(), lst.end());
    NAMESPACE::vector<int> v2(lst.begin(), lst.end());
    print_t("v");
    print_v(v);
    std::cout << std::endl;
    print_t("v2");
    print_v(v2);
    std::cout << std::endl;

    print_t("v == v2");
    if (v == v2) std::cout << "v and v2 are equal" << std::endl;
    print_t("v != v2");
    if (v != v2) std::cout << "v and v2 are not equal" << std::endl;
    print_t("v <= v2");
    if (v <= v2) std::cout << "v is less than or equal to v2" << std::endl;
    print_t("v >= v2");
    if (v >= v2) std::cout << "v is greater than or equal to v2" << std::endl;
    print_t("v < v2");
    if (v < v2) std::cout << "v is less than v2" << std::endl;
    print_t("v > v2");
    if (v > v2) std::cout << "v is greater than v2" << std::endl;
    std::cout << std::endl;

    print_t("v.assign(lst.begin(), lst.end()");
    v.assign(lst.begin(), lst.end());
    print_t("v2.assign(lst.rbegin(), lst.rend()");
    v2.assign(lst.rbegin(), lst.rend());

    print_t("v");
    print_v(v);
    std::cout << std::endl;
    print_t("v2");
    print_v(v2);
    std::cout << std::endl;

     print_t("v == v2");
    if (v == v2) std::cout << "v and v2 are equal" << std::endl;
    print_t("v != v2");
    if (v != v2) std::cout << "v and v2 are not equal" << std::endl;
    print_t("v <= v2");
    if (v <= v2) std::cout << "v is less than or equal to v2" << std::endl;
    print_t("v >= v2");
    if (v >= v2) std::cout << "v is greater than or equal to v2" << std::endl;
    print_t("v < v2");
    if (v < v2) std::cout << "v is less than v2" << std::endl;
    print_t("v > v2");
    if (v > v2) std::cout << "v is greater than v2" << std::endl;
    std::cout << std::endl;
}