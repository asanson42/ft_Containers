#ifndef MAP_NODE_CONST_ITERATOR_HPP
# define MAP_NODE_CONST_ITERATOR_HPP

# include <cstddef>
# include <iterator>
# include "map_node.hpp"
# include "map_node_iterator.hpp"

namespace ft 
{
	template< typename T >
	class rbt_iterator;

	template< typename T >
	class rbt_const_iterator 
	{
		public :

			typedef T const								value_type;
			typedef std::ptrdiff_t						difference_type;
			typedef T const *							pointer;
			typedef T const &							reference;
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef ft::Node<T>							Node;

		protected :

			Node *	_current;
			Node *	_root;

		public :

			rbt_const_iterator( Node * node = NULL, Node * root = NULL ) : _current ( node ), _root ( root ) 
			{
				return ;
			}

			rbt_const_iterator( rbt_const_iterator const & src ) : _current ( src._current ), _root ( src._root ) 
			{
				return ;
			}

			rbt_const_iterator( rbt_iterator<T> const & src ) : _current ( src.getCurrent() ), _root ( src.getRoot() ) 
			{
				return ;
			}

			~rbt_const_iterator() 
			{
				return ;
			}

			Node *	getCurrent() const 
			{
				return this->_current;
			}

			Node *	getRoot() const 
			{
				return this->_root;
			}

			Node *min( Node *node ) const 
			{
				Node * tmp = node;
				while ( tmp && tmp->_left )
					tmp = tmp->_left;
				return tmp;
			}

			Node *	max( Node *node ) const 
			{
				Node * tmp = node;
				while ( tmp && tmp->_right )
					tmp = tmp->_right;
				return tmp;
			}

			rbt_const_iterator &	operator=( rbt_const_iterator const & rhs ) 
			{
				if ( this != &rhs ) 
				{
					this->_current = rhs._current;
					this->_root = rhs._root;
				}
				return *this;
			}

			rbt_const_iterator &	operator++() 
			{
				if ( _current == NULL )
					_current = min( _root );
				else if ( _current->_right )
					_current = min(_current->_right);
				else if ( _current->_parent && _current == _current->_parent->_left )
					_current = _current->_parent;
				else if ( _current->_parent ) 
				{
					while ( _current->_parent && _current == _current->_parent->_right )
						_current = _current->_parent;
					_current = _current->_parent && _current == _current->_parent->_left ?	_current->_parent : NULL;
				}
				else
					_current = NULL;
				return *this;
			}

			rbt_const_iterator	operator++( int ) 
			{
				rbt_const_iterator	tmp = *this;
				operator++();
				return tmp;
			}

			rbt_const_iterator &	operator--() 
			{
				if ( _current == NULL && _root )
					_current = max( _root );
				else if ( _current->_left )
					_current = max( _current->_left );
				else if ( _current->_parent && _current == _current->_parent->_right )
					_current = _current->_parent;
				else if ( _current->_parent ) 
				{
					while ( _current->_parent && _current == _current->_parent->_left )
						_current = _current->_parent;
					_current = _current->_parent && _current == _current->_parent->_right ?	_current->_parent : NULL;
				}
				else
					_current = NULL;
				return *this;
			}

			rbt_const_iterator	operator--( int ) 
			{
				rbt_const_iterator	tmp = *this;
				operator--();
				return tmp;
			}

			pointer	operator->() const 
			{
				return &( _current->_value );
			}

			reference	operator*() const
			{
				return _current->_value;
			}

			bool	operator==( rbt_const_iterator< T > const & rhs ) const 
			{
				return _current == rhs._current;
			}

			bool	operator!=( rbt_const_iterator< T > const & rhs ) const 
			{
				return _current != rhs._current;
			}
	};

	template< typename T, typename U >
	bool	operator==( ft::rbt_const_iterator< T > const & x, ft::rbt_const_iterator< U > const & y ) 
	{
		return x.getCurrent() == y.getCurrent();
	}

	template< typename T, typename U >
	bool	operator!=( ft::rbt_const_iterator< T > const & x, ft::rbt_const_iterator< U > const & y ) 
	{
		return x.getCurrent() != y.getCurrent();
	}
}

#endif