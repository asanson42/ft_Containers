#include "../inc/test_vector.hpp"

void    vector_access(void)
{
    std::list<std::string> l;
    for (int i = 0; i < 5; i++)
    {
        l.push_back(std::string(3, 'a' + i));
    }

    NAMESPACE::vector< std::string > v(l.begin(), l.end());
    print_t("operator []");
    for (int i = 0; i < 5; i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;

    print_t("assign operator []");
    for (int i = 0; i < 5; i++)
    {
        v[i] = v[i] + "b";
    }
    print_v(v);
    
    print_t("at(3)");
    std::cout << v.at(3) << std::endl;
    print_t("front");
    std::cout << v.front() << std::endl;
    print_t("back");
    std::cout << v.back() << std::endl;
    
}