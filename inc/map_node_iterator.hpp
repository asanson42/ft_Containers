#ifndef MAP_NODE_ITERATOR_HPP
# define MAP_NODE_ITERATOR_HPP

# include <cstddef>
# include <iterator>
# include "map_node.hpp"
# include "map_node_const_iterator.hpp"

namespace ft 
{
	template< typename T >
	class rbt_const_iterator;

	template< typename T >
	class rbt_iterator 
	{
		public :

			typedef T									value_type;
			typedef std::ptrdiff_t						difference_type;
			typedef T*									pointer;
			typedef T&									reference;
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef ft::Node<T>							Node;

		protected :

			Node *	_current;
			Node *	_root;

		public :

			rbt_iterator( Node * node = NULL, Node * root = NULL ) : _current ( node ), _root ( root ) 
			{
				return ;
			}

			rbt_iterator( rbt_iterator const & src ) : _current ( src._current ), _root ( src._root ) 
			{
				return ;
			}

			~rbt_iterator() 
			{
				return ;
			}

			Node * 	getCurrent() const 
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
				while (tmp && tmp->_right )
					tmp = tmp->_right;
				return tmp;
			}

			rbt_iterator &	operator=( rbt_iterator const & rhs ) 
			{
				if ( this != &rhs ) 
				{
					this->_current = rhs._current;
					this->_root = rhs._root;
				}
				return *this;
			}

			rbt_iterator &	operator++() 
			{
				if ( _current == NULL ) 
				{
					_current = min( _root );
				}
				else if ( _current->_right ) 
				{
					_current = min( _current->_right );
				}
				else if ( _current->_parent && _current == _current->_parent->_left ) 
				{
					_current = _current->_parent;
				}
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

			rbt_iterator	operator++( int ) 
			{
				rbt_iterator	tmp = *this;
				operator++();
				return tmp;
			}

			rbt_iterator &	operator--() 
			{
				if ( _current == NULL )
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

			rbt_iterator	operator--( int ) 
			{
				rbt_iterator	tmp = *this;
				operator--();
				return tmp;
			}

			pointer	operator->() const 
			{
				return &(_current->_value);
			}

			reference	operator*() const 
			{
				return _current->_value;
			}

			bool	operator==( ft::rbt_iterator< T > const & rhs ) const 
			{
				return _current == rhs._current;
			}

			bool	operator!=( ft::rbt_iterator< T > const & rhs ) const 
			{
				return _current != rhs._current;
			}
	};
}

#endif