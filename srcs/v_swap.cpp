# include "../inc/test_vector.hpp"

void vector_swap(void)
{
    print_t("Vector Swap");

    NAMESPACE::vector<int> v(3, 5);
    NAMESPACE::vector<int> v2(5, 10);

    std::cout << "before swap" << std::endl;
    std::cout << "vector 1:" << std::endl;
    print_v(v);
    std::cout << "vector 2:" << std::endl;
    print_v(v2);
    std::cout << std::endl;

    v.swap(v2);
    std::cout << "after swap" << std::endl;
    std::cout << "vector 1:" << std::endl;
    print_v(v);
    std::cout << "vector 2:" << std::endl;
    print_v(v2);
    std::cout << std::endl;
}