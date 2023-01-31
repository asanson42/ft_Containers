#ifndef TEST_VECTOR_HPP
# define TEST_VECTOR_HPP
# include "test_utils.hpp"
# include <list>
# ifdef USESTL
#   include <vector>
# else
#   include "vector.hpp"
# endif
#endif

# include <iostream>

void    vector_access(void);
void    vector_compare(void);
void    vector_const(void);
void    vector_erase(void);
void    vector_insert(void);
void    vector_it(void);
void    vector_swap(void);

template <typename vector>
void    print_v(const vector &v, bool content = true)
{
    typedef typename vector::const_iterator v_it;

    std::cout << "[size]:  " << v.size() << std::endl;
    std::cout << "[content]:  " << std::endl;

    if (content)
    {
        v_it it = v.begin();
        v_it ite = v.end();

        for ( ; it != ite; ++it)
        {
            std::cout << *it << " ";
        }
    }
    std::cout << std::endl;
}