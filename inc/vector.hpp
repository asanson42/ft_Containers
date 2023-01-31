#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "utils.hpp"
# include "vector_iterator.hpp"
# include "reverse_iterator.hpp"
# include <iterator>
# include <memory>
# include <stdexcept>
# include <string>
# include <sstream>

namespace ft
{
    template< class T, class Allocator = std::allocator< T > >
    class vector
    {
        public:
                typedef typename Allocator::reference                   reference;
                typedef typename Allocator::const_reference             const_reference;
                typedef ft::vector_iterator< T >                        iterator;
                typedef ft::vector_const_iterator< T >                  const_iterator;
                typedef typename Allocator::size_type                   size_type;
                typedef typename Allocator::difference_type             difference_type;
                typedef T                                               value_type;
                typedef Allocator                                       allocator_type;
                typedef typename Allocator::pointer                     pointer;
                typedef typename Allocator::const_pointer               const_pointer;
                typedef ft::reverse_iterator< iterator >                reverse_iterator;
                typedef ft::reverse_iterator< const_iterator>           const_reverse_iterator;

        protected:
                allocator_type      _alloc;
                size_type           _size;
                size_type           _capacity;
                T*                  _array;

        public:
                explicit vector(Allocator const &alloc = Allocator()) : _alloc(alloc), _size(0), _capacity(0), _array(0) {}
                explicit vector(size_type n, T const &value = T(), Allocator const &alloc = Allocator()) : _alloc(alloc), _size(n), _capacity(n), _array(NULL)
                {
                    _array = _alloc.allocate(n);
                    for (size_type i = 0; i < n; ++i)
                        _alloc.construct(_array + i, value);
                    return;
                }

                template< class InputIterator >
                vector (InputIterator first, InputIterator last, allocator_type const &alloc = allocator_type(), typename ft::enable_if< !ft::is_integral< InputIterator >::value, bool >::type = true) : _alloc(alloc), _size(0), _capacity(0), _array(NULL)
                {
                    _size = std::distance(first, last);
                    _capacity = _size;
                    _array = _alloc.allocate(_size);

                    for (size_type i = 0; i < _size; ++i, ++first)
                    {
                        _alloc.construct(_array + i, *first);
                    }
                    return;
                }

                vector( const vector< T, Allocator > & x ) : _alloc ( x._alloc ), _size ( x._size ), _capacity ( x._size ), _array ( NULL )
                {
				    _array = _alloc.allocate( _capacity );
				    for ( size_type i = 0 ; i < _size ; ++i )
					    _alloc.construct( _array + i, *(x._array + i) );
				    return ;
			    }

                ~vector()
                {
                    this->clear();
                    _alloc.deallocate(_array, _capacity);
                    return ;
                }

                vector< T, Allocator> &operator=(const vector< T, Allocator > &o)
                {
                    if (this != &o)
                    {
                        this->clear();
                        _alloc.deallocate(_array, _capacity);
                        _size = o._size;
                        if (_capacity < o._size)
                            _capacity = o._size;
                        _array = _alloc.allocate(_capacity);
                        for (size_type i = 0; i < _size; ++i)
                        {
                            _alloc.construct(_array + i, *(o._array + i));
                        }
                    }
                    return (*this);
                }

                template< class InputIterator >
                void assign(InputIterator first, InputIterator last, typename ft::enable_if< !ft::is_integral< InputIterator >::value, bool>::type = true)
                {
                    erase(begin(), end());
                    insert(begin(), first, last);
                    return;
                }

                void assign(size_type n, const T& t)
                {
                    erase(begin(), end());
                    insert(begin(), n, t);
                    return;
                }

                allocator_type get_allocator() const
                {
                    return (_alloc);
                }

                // Iterators
                iterator	begin() { return iterator( _array ); }
                const_iterator	begin() const { return const_iterator( _array ); }
			    iterator	end() { return iterator( _array + _size ); }
			    const_iterator	end() const { return const_iterator( _array + _size ); }
			    reverse_iterator	rbegin() { return reverse_iterator( _array + _size ); }
                const_reverse_iterator	rbegin() const { return const_reverse_iterator( _array + _size ); }
			    reverse_iterator	rend() { return reverse_iterator( _array ); }
			    const_reverse_iterator	rend() const { return const_reverse_iterator( _array ); }

                size_type	size() const { return _size; }
			    size_type	max_size() const { return _alloc.max_size(); }

			    void	resize( size_type sz, T c = T() ) 
                {
				    if ( sz > size() )
					    insert( end(), sz - size(), c);
				    else if (sz < size() )
					    erase( begin() + sz, end() );
				    return ;
			    }

			    size_type	capacity() const { return _capacity; }
			    bool	empty() const { return _size == 0; }

                // Demande un changement de capacité
			    void	reserve( size_type n ) 
                {
				    if ( n > max_size() )
					    throw std::length_error("vector::reserve");
				    if ( n >_capacity ) {
					    pointer	newArray = _alloc.allocate( n );
					    for ( size_type i = 0 ; i < _size ; ++i ) {
						    _alloc.construct( newArray + i, *(_array + i) );
						    _alloc.destroy( _array + i );
					    }
					    _alloc.deallocate( _array, _capacity );
					    _capacity = n;
					    _array = newArray;
				    }
				    return ;
			    }

                reference operator[](size_type n) { return _array[n]; }
                const_reference operator[](size_type n) const { return _array[n]; }

                reference at(size_type n)
                {
                    if (n < 0 || _size <= n)
                        throw std::out_of_range("Error: vector::at");
                    return _array[n];
                }

                const_reference at(size_type n) const
                {
                    if (n < 0 || _size <= n)
                        throw std::out_of_range("Error: vector::at");
                    return _array[n];
                }

                reference front() { return *(begin()); }
                const_reference front() const { return *(begin()); }
                reference back() { return *(end() - 1); }
                const_reference back() const { return *(end() - 1); }

                void push_back(const T& x)
                {
                    if (_capacity == 0)
                        reserve(1);
                    else if (_size == _capacity)
                    {
                        reserve(_capacity * 2);
                    }
                    _alloc.construct(_array + _size, x);
                    _size++;
                    return ;
                }

                void pop_back()
                {
                    _size--;
                    _alloc.destroy(_array + _size);
                    return ;
                }

                iterator insert(iterator pos, const T& x)
                {
                    difference_type dis = std::distance(begin(), pos);
                    insert(pos, 1, x);
                    return (iterator(begin() + dis));
                }

                void insert(iterator pos, size_type n, const T& x)
                {   
                    size_type dis = std::distance(begin(), pos);
                    if (n <= 0)
                        return ;
                    else if (n > _capacity - _size)
                    {
                        if (max_size() - _size >= _size && n <= _size)
                            reserve(_size * 2);
                        else
                            reserve(_size + n);
                        pos = begin() + dis;
                    }
                    pointer tmp_end = _array + _size + n - 1;
                    pointer tmp_start = _array + dis + n - 1;
                    while (tmp_end != tmp_start)
                    {
                        _alloc.construct(tmp_end, *(tmp_end -n));
                        _alloc.destroy(tmp_end -n);
                        tmp_end--;
                    }
                    _size += n;
                    for (size_type i = 0; i < n; ++i)
                    {
                        _alloc.construct(_array + dis + i, x);
                    }
                    return ;
                }   

                template< class InputIterator >
                void insert(iterator pos, InputIterator first, InputIterator last, typename ft::enable_if< !ft::is_integral< InputIterator >::value, bool >::type = true)
                {
                    size_type dis = std::distance(begin(), pos);
                    size_type n = std::distance(first, last);

                    if (n <= 0)
                        return;
                    else if (n > _capacity - _size)
                    {
                        if (max_size() - _size >= _capacity && n <= _size)
                            reserve(_size * 2);
                        else
                            reserve(_size + n);
                        pos = begin() + dis;
                    }
                    for (size_type i = 0; i < n; ++i, ++first)
                    {
                        insert(begin() + dis + i, *(first));
                    }
                    return ;
                }

                iterator erase(iterator position)
                {
                    if ( position == end() || empty() )
				        return end();
				    for ( iterator it = position ; it != end() ; ++it ) {
					    _alloc.destroy( &(*it) );
					    if (it !=  end() - 1)
						    _alloc.construct( &(*it), *(it + 1) );
				    }
				    _size--;
				    return position;
                }

                iterator erase(iterator first, iterator last)
                {
                    iterator ret = first;
				    size_type	distFromBegin = std::distance( begin(), first );
				    size_type	toMove = std::distance( last, end() );;
				    size_type	dist = std::distance( first, last );
				    if ( dist == 0 )
					    return ret;
				    for ( ; first != last ; ++first )
					    _alloc.destroy( &(*first) );
				    for ( size_type i = 0 ; i != toMove ; ++i ) {
					    _alloc.construct( _array + distFromBegin + i, *(_array + distFromBegin + dist + i) );
					    _alloc.destroy( _array + distFromBegin + dist + i );
				    }
				    _size -= dist;
				    return ret;
                }

                void swap(vector< T, Allocator > &x)
                {
                    allocator_type tmp_alloc = x._alloc;
                    size_type tmp_capacity = x._capacity;
                    size_type tmp_size = x._size;
                    pointer tmp_array = x._array;

                    x._alloc = _alloc;
                    x._capacity = _capacity;
                    x._size = _size;
                    x._array = _array;

                    _alloc = tmp_alloc;
                    _capacity = tmp_capacity;
                    _size = tmp_size;
                    _array = tmp_array;

                    return ;
                }

                void clear()
                {
                    for (size_type i = 0; i < _size; ++i)
                    {
                        _alloc.destroy(_array + i);
                    }
                    _size = 0;
                    return ;
                }
    };
    
    template< class T, class Allocator >
	bool	operator==( vector< T, Allocator >const & x, vector< T, Allocator > const & y ) 
    {
		if ( x.size() != y.size() )
			return false;
		return ft::equal( x.begin(), x.end(), y.begin() );
	}

	template< class T, class Allocator >
	bool	operator<( vector< T, Allocator >const & x, vector< T, Allocator > const & y ) 
    {
		return	ft::lexicographical_compare( x.begin(), x.end(), y.begin(), y.end() );
	}

	template< class T, class Allocator >
	bool	operator!=( vector< T, Allocator >const & x, vector< T, Allocator > const & y ) 
    {
		return !(x == y);
	}

	template< class T, class Allocator >
	bool	operator>=( vector< T, Allocator >const & x, vector< T, Allocator > const & y ) 
    {
		return !(x < y);
	}

	template< class T, class Allocator >
	bool	operator>( vector< T, Allocator >const & x, vector< T, Allocator > const & y ) 
    {
		return y < x;
	}

	template< class T, class Allocator >
	bool	operator<=( vector< T, Allocator >const & x, vector< T, Allocator > const & y ) 
    {
		return !(x > y);
	}
}

namespace std
{
    template< class T, class Allocator >
	void	swap( ft::vector< T, Allocator>& x, ft::vector< T, Allocator >& y ) 
    {
		x.swap( y );
		return ;
	}   
}

#endif