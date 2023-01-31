#include <vector>
#include <stack>
#include <map>
#include <iostream>
#include "../inc/vector.hpp"
#include "../inc/map.hpp" 
#include <time.h>
#include <list>

// include tester_hpp
#include "../inc/test_vector.hpp"
#include "../inc/test_map.hpp"

typedef void (*t_func)(void);

static void t_vector(void)
{
        vector_access();
        vector_compare();
        vector_const();
        vector_erase();
        vector_insert();
        vector_it();
        vector_swap();    
}

static void t_map(void)
{
        map_bound();
        map_const();
        map_access();
        map_erase();
        map_find();
        map_it();
        map_insert();
        map_swap();
		map_compare();
}

static void t_containers(const std::string &str)
{
        const int               nb_cont = 2;
        const std::string       cont[nb_cont] = {"vector", "map"};
        t_func                  func[nb_cont] = {t_vector, t_map};

        int                     id = -1;

        for (int i = 0; i < nb_cont; i++)
        {
                if (str == cont[i])
                {
                        id = i;
                        break;
                }
        }
        if (id >= 0)
                func[id]();
}

int main(int argc, char *argv[])
{
        if (argc == 1)
        {
                t_vector();
                t_map();
        }
        else
        {
                for (int i = 0; i < argc; i++)
                {
                        t_containers(std::string(argv[i]));
                }
        }
        return (0);
}