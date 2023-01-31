#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include <cstddef>
# include <iterator>
# include "vector_const_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
    template< typename T >
    class vector_const_iterator;

    template< typename T>
    class vector_iterator
    {
        public:    
            typedef std::random_access_iterator_tag         iterator_category;
            typedef T                                       value_type;
            typedef ptrdiff_t                               difference_type;
            typedef T*                                      pointer;
            typedef T&                                      reference;
        
        protected:
            pointer _current;

        public:
            vector_iterator() : _current(NULL) {}
            vector_iterator(pointer ptr) : _current(ptr) {}
            vector_iterator(vector_iterator const &o) : _current(o._current) {}
            ~vector_iterator() {}

            pointer getCurr() const { return (this->_current);}

            vector_iterator &operator=(vector_iterator const &cpy)
            {
                if (this != &cpy)
                    this->_current = cpy._current;
                return (*this);
            }

            // Operators
            vector_iterator &operator++()
            {
                ++_current;
                return (*this);
            }

            vector_iterator operator++( int )
            {
                vector_iterator tmp = *this;
                ++(*this);
                return (tmp);
            }

            vector_iterator &operator--()
            {
                --_current;
                return (*this);
            }

            vector_iterator operator--( int )
            {
                vector_iterator tmp = *this;
                --(*this);
                return (tmp);
            }

            friend vector_iterator operator+(difference_type n, vector_iterator const &x)
            {
                vector_iterator tmp = x;
                return (tmp += n);
            }

            vector_iterator operator+(difference_type n) const
            {
                vector_iterator tmp = *this;
                return (tmp += n);
            }

            difference_type operator-(vector_iterator const &x)
            {
                return (_current - x._current);
            }

            vector_iterator operator-(difference_type n) const
            {
                vector_iterator tmp = *this;
                return (tmp -= n);
            }

            vector_iterator &operator-=(difference_type n)
            {
                return (*this += -n);
            }

            vector_iterator &operator+=(difference_type n)
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
    bool operator==(ft::vector_const_iterator< T > const &x, vector_iterator< U > const &y)
    {
        return (x.getCurr() == y.getCurr());
    }

    template< typename T, typename U >
    bool operator!=(ft::vector_const_iterator< T > const &x, vector_iterator< U > const &y)
    {
        return (x.getCurr() != y.getCurr());
    }
    
    template< typename T, typename U >
    bool operator<=(ft::vector_const_iterator< T > const &x, vector_iterator< U > const &y)
    {
        return (x.getCurr() <= y.getCurr());
    }

    template< typename T, typename U >
    bool operator<(ft::vector_const_iterator< T > const &x, vector_iterator< U > const &y)
    {
        return (x.getCurr() < y.getCurr());
    }

    template< typename T, typename U >
    bool operator>=(ft::vector_const_iterator< T > const &x, vector_iterator< U > const &y)
    {
        return (x.getCurr() >= y.getCurr());
    }

    template< typename T, typename U >
    bool operator>(ft::vector_const_iterator< T > const &x, vector_iterator< U > const &y)
    {
        return (x.getCurr() > y.getCurr());
    }
}

#endif