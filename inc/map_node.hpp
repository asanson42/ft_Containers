#ifndef MAP_NODE_HPP
# define MAP_NODE_HPP

# include <cstddef>
# include <memory>

namespace ft
{
    template < class T >
    class Node
    {
        public:

            enum t_color{ BLACK = 0, RED = 1 };
            typedef T               value_type;
            typedef std::ptrdiff_t  difference_type;
            typedef T*              pointer;
            typedef T&              reference;

            Node *  _right;
            Node *  _left;
            Node *  _parent;
            T       _value;
            t_color _color;

            Node(T value = T(), Node *parent = NULL) : _right(NULL), _left(NULL), _parent(parent), _value(value), _color(RED)
            {
                return ;
            }
    };
}

#endif