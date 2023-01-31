#ifndef TEST_UTILS_HPP
# define TEST_UTILS_HPP
# ifdef USESTL
#   define NAMESPACE std
# else
#   define NAMESPACE ft
#endif

# include <iostream>
# define YLW "\x1B[33m"
# define END "\x1B[0m"

void	print_t(std::string str);

#endif
