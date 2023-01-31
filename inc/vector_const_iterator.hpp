#ifndef VECTOR_CONST_ITERATOR_HPP
# define VECTOR_CONST_ITERATOR_HPP

# include <cstddef>
# include <iterator>
# include "vector_iterator.hpp"

namespace ft
{
    template< typename T >
    class vector_iterator;

    template< typename T>
    class vector_const_iterator
    {
        
        public:    
            typedef std::random_access_iterator_tag         iterator_category;
            typedef T  const                                value_type;
            typedef ptrdiff_t                               difference_type;
            typedef T const *                               pointer;
            typedef T const &                               reference;
        
        protected:
            pointer _current;
        
        public:
            vector_const_iterator() : _current(NULL) {}
            vector_const_iterator(pointer ptr) : _current(ptr) {}
            vector_const_iterator(vector_const_iterator const &o) : _current(o._current) {}
            vector_const_iterator(ft::vector_iterator< T > const &o) : _current (o.getCurr()) {}
            ~vector_const_iterator() {}

            pointer getCurr() const { return (this->_current);}

            vector_const_iterator &operator=(vector_const_iterator const &cpy)
            {
                if (this != &cpy)
                    this->_current = cpy._current;
                return (*this);
            }

            // Operators
            vector_const_iterator &operator++()
            {
                ++_current;
                return (*this);
            }

            vector_const_iterator operator++( int )
            {
                vector_const_iterator tmp = *this;
                ++(*this);
                return (tmp);
            }

            vector_const_iterator &operator--()
            {
                --_current;
                return (*this);
            }

            vector_const_iterator operator--( int )
            {
                vector_const_iterator tmp = *this;
                --(*this);
                return (tmp);
            }

            vector_const_iterator operator+(difference_type n) const
            {
                vector_const_iterator tmp = *this;
                return (tmp += n);
            }
            
            friend difference_type operator-(vector_const_iterator const &x, vector_const_iterator const &y)
            {
                return (x._current - y._current);
            }

            vector_const_iterator operator-(difference_type n) const
            {
                vector_const_iterator tmp = *this;
                return (tmp -= n);
            }

            vector_const_iterator &operator-=(difference_type n)
            {
                return (*this += -n);
            }

            vector_const_iterator &operator+=(difference_type n)
            {
                difference_type tmp = n;

                if (tmp >= 0)
                {
                    while (tmp--)
                    {
                        ++(*this);
                    }
                }
                else
                {
                    while (tmp++)
                    {
                        --(*this);
                    }
                }
                return (*this);
            }

            reference operator[] (int n) const { return *(_current + n); }
            pointer operator->() const { return (_current); }
            reference operator*() const { return (*_current); }

            bool operator==(ft::vector_const_iterator< T > const &x) const
            {
                return (_current == x.getCurr());
            }

            bool operator!=(ft::vector_const_iterator< T > const &x) const
            {
                return (_current != x.getCurr());
            }

            bool operator<=(ft::vector_const_iterator< T > const &x) const
            {
                return (_current <= x.getCurr());
            }

            bool operator<(ft::vector_const_iterator< T > const &x) const
            {
                return (_current < x.getCurr());
            }

            bool operator>=(ft::vector_const_iterator< T > const &x) const
            {
                return (_current >= x.getCurr());
            }

            bool operator>(ft::vector_const_iterator< T > const &x) const
            {
                return (_current > x.getCurr());
            }
    };

    template< typename T, typename U >
    bool operator==(ft::vector_const_iterator< T > const &x, vector_const_iterator< U > const &y)
    {
        return (x.getCurr() == y.getCurr());
    }

    template< typename T, typename U >
    bool operator!=(ft::vector_const_iterator< T > const &x, vector_const_iterator< U > const &y)
    {
        return (x.getCurr() != y.getCurr());
    }
    
    template< typename T, typename U >
    bool operator<=(ft::vector_const_iterator< T > const &x, vector_const_iterator< U > const &y)
    {
        return (x.getCurr() <= y.getCurr());
    }

    template< typename T, typename U >
    bool operator<(ft::vector_const_iterator< T > const &x, vector_const_iterator< U > const &y)
    {
        return (x.getCurr() < y.getCurr());
    }

    template< typename T, typename U >
    bool operator>=(ft::vector_const_iterator< T > const &x, vector_const_iterator< U > const &y)
    {
        return (x.getCurr() >= y.getCurr());
    }

    template< typename T, typename U >
    bool operator>(ft::vector_const_iterator< T > const &x, vector_const_iterator< U > const &y)
    {
        return (x.getCurr() > y.getCurr());
    }
}

#endif