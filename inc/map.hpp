#ifndef MAP_HPP
# define MAP_HPP

# include "map_tree.hpp"
# include "utils.hpp"
# include "map_node.hpp"
# include "map_node_iterator.hpp"
# include "map_node_const_iterator.hpp"
# include "reverse_iterator.hpp"
# include "iterator_traits.hpp"
# include <memory>
# include <stdexcept>
# include <functional>

namespace ft 
{
	template< class Key, class T, class Compare = std::less< Key >, class Allocator = std::allocator< ft::pair< const Key, T> > >

	class map 
	{

		public :

			typedef Key										key_type;
			typedef T										mapped_type;
			typedef ft::pair< const Key, T >				value_type;
			typedef Compare									key_compare;
			typedef Allocator								allocator_type;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference		const_reference;
			typedef typename Allocator::size_type			size_type;
			typedef typename Allocator::difference_type		difference_type;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;

			class	value_compare : public std::binary_function< value_type, value_type, bool > 
			{
				friend class map;

				protected :

					Compare	comp;
					value_compare( Compare c ) : comp ( c ) 
					{
						return ;
					}

				public :

					value_compare() : comp () {}
					bool	operator()( value_type const & x, value_type const  & y ) const 
					{
						return comp( x.first, y.first );
					}
			};

			typedef ft::Node<value_type>								Node;
			typedef ft::RBTree< value_type, value_compare, Allocator>	RBTree;
			typedef	typename RBTree::iterator							iterator;
			typedef typename RBTree::const_iterator						const_iterator;
			typedef ft::reverse_iterator< iterator >					reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >				const_reverse_iterator;

		protected :

			allocator_type	_alloc;
			key_compare		_keyComp;
			RBTree			_tree;

			bool	isEqual( Key const & x, Key const & y ) const 
			{
				return _keyComp( x, y ) == _keyComp( y, x );
			}

		public :

			explicit	map( Compare const & comp = Compare(), Allocator const & alloc = Allocator() ) : _alloc ( alloc ), _keyComp ( comp ), _tree (RBTree (value_compare(comp))) 
			{
				return ;
			}

			template < class InputIterator >
			map( InputIterator first, InputIterator last, Compare const & comp = Compare(), Allocator const & alloc = Allocator() ) : _alloc ( alloc ), _keyComp ( comp ), _tree (RBTree (value_compare(comp))) 
			{
				insert( first, last );
				return ;
			}

			map( map< Key, T, Compare, Allocator> const & x ) : _alloc ( x._alloc ), _keyComp ( x._keyComp ), _tree (RBTree (value_compare(x._keyComp))) 
			{
				insert( x.begin(), x.end() );
				return ;
			}

			~map() 
			{
				return ;
			}

			map< Key, T, Compare, Allocator > & operator=( map< Key, T, Compare, Allocator > const & x ) 
			{
				if ( this != &x ) 
				{
					this->_tree = x._tree;
				}
				return *this;
			}

			iterator	begin() { return  _tree.begin(); }
			const_iterator	begin() const { return  _tree.begin(); }
			iterator	end() { return _tree.end(); }
			const_iterator	end() const { return _tree.end(); }
			reverse_iterator	rbegin() { return _tree.rbegin(); }
			const_reverse_iterator	rbegin() const { return _tree.rbegin(); }
			reverse_iterator	rend() { return _tree.rend(); }
			const_reverse_iterator	rend() const { return _tree.rend(); }
 
            bool	empty() const { return _tree.size() == 0; }

			size_type	size() const { return _tree.size(); }
			size_type	max_size() const { return std::allocator<Node> ().max_size(); }
            T&	operator[]( key_type const & x ) { return insert( ft::make_pair( x, T () ) ).first->second; }
            ft::pair< iterator, bool >	insert( value_type const & x ) { return _tree.insert( x ); }
			iterator	insert( iterator position, value_type const & x ) { return _tree.insert( position, x ); }

			template< class InputIterator >
			void	insert( InputIterator first, InputIterator last ) 
			{
				return _tree.insert( first, last );
			}

			void	erase( iterator position ) 
			{
				erase( position->first );
				return;
			}

			size_type	erase( key_type const & x ) 
			{
				iterator it = find( x );
				if ( it == end() )
					return 0;
				else
					return _tree.erase( it.getCurrent() );
			}

			void	erase( iterator first, iterator last ) 
			{
				for ( ; first != last ; ) 
				{
					iterator tmp = first;
					first++;
					erase( tmp );
				}
				return ;
			}

			void	swap( map< Key, T, Compare, Allocator > & rhs ) 
			{
				if ( this != &rhs ) 
				{
					Node *		rootTmp = _tree.getRoot();
					size_type	sizeTmp = _tree.size();

					_tree.setRoot( rhs._tree.getRoot() );
					_tree.setSize( rhs._tree.size());

					rhs._tree.setRoot( rootTmp );
					rhs._tree.setSize( sizeTmp );
				}
				return ;
			}

			void	clear() 
			{
				_tree.clear();
				return ;
			}

            key_compare	key_comp() const 
			{
				return _keyComp;
			}

			value_compare	value_comp() const 
			{
				return value_compare( _keyComp ) ;
			}

			allocator_type	get_allocator() const 
			{
				return _alloc;
			}

            iterator	find( key_type const & x ) 
			{
				Node * tmp = _tree.getRoot();

				while ( tmp && !isEqual( tmp->_value.first, x ) ) 
				{
					if ( _keyComp( x, tmp->_value.first ) )
						tmp = tmp->_left;
					else
						tmp = tmp->_right;
				}
				return iterator ( tmp );
			}

			const_iterator	find( key_type const & x ) const 
			{
				Node * tmp = _tree.getRoot();

				while ( tmp && !isEqual( tmp->_value.first, x ) ) 
				{
					if ( _keyComp( x, tmp->_value.first ) )
						tmp = tmp->_left;
					else
						tmp = tmp->_right;
				}
				return const_iterator ( tmp );
			}

			size_type	count( key_type const & x ) const 
			{
				if ( find( x ) == this->end() )
					return 0;
				return 1;
			}

			iterator	lower_bound( key_type const & x ) 
			{
				if ( _tree.getRoot() == NULL )
					return _tree.end();
				else if ( isEqual( _tree.getRoot()->_value.first, x ) )
					return iterator( _tree.getRoot() );
				else if ( _keyComp(_tree.getRoot()->_value.first, x) ) 
				{
					reverse_iterator it = _tree.rbegin();
					for ( reverse_iterator ite = _tree.rend() ; it != ite ; ++it ) 
					{
						if ( isEqual( it->first, x ) )
						{
							it++;
							return iterator( it.base() );
						}
						else if ( _keyComp( it->first, x ) )
							return iterator( it.base() );
					}
				}
				else 
				{
					iterator it = _tree.begin();
					for ( iterator ite = _tree.end() ; it != ite ; ++it ) 
					{
						if ( isEqual( it->first, x ) || _keyComp( x, it->first ) )
							return it;
					}
				}
				return _tree.end();
			}

			const_iterator	lower_bound( key_type const & x ) const 
			{
				if ( _tree.getRoot() == NULL )
					return _tree.end();
				else if ( isEqual(_tree.getRoot()->_value.first, x) )
					return const_iterator( _tree.getRoot() );
				else if ( _keyComp(_tree.getRoot()->_value.first, x) ) 
				{
					const_reverse_iterator it = _tree.rbegin();
					for ( const_reverse_iterator ite = _tree.rend() ; it != ite ; it++ ) 
					{
						if ( isEqual( it->first, x ) ) 
						{
							it++;
							return const_iterator( it.base() );
						}
						else if ( _keyComp( it->first, x ) )
							return const_iterator(it.base());
					}
				}
				else 
				{
					const_iterator it = _tree.begin();
					for ( const_iterator ite = _tree.end() ; it != ite ; ++it ) 
					{
						if ( isEqual( it->first, x ) || _keyComp( x, it->first ) )
							return it;
					}
				}
				return _tree.end();
			}

			iterator	upper_bound( key_type const & x ) 
			{
				iterator it = lower_bound(x);
				if ( it != end() && isEqual( it->first, x ) )
					it++;
				return it;
			}

			const_iterator	upper_bound( key_type const & x ) const 
			{
				const_iterator it = lower_bound(x);
				if ( it != end() && isEqual( it->first, x ) )
					it++;
				return it;
			}

			ft::pair< iterator, iterator >	equal_range( key_type const & x ) 
			{
				iterator low = lower_bound(x);
				iterator up = low;
				if ( up != end() && isEqual( up->first, x ) )
					up++;
				return ft::make_pair( low, up );
			}

			ft::pair< const_iterator, const_iterator >	equal_range( key_type const & x ) const 
			{
				const_iterator low = lower_bound(x);
				const_iterator up = low;
				if ( up != end() && isEqual( up->first, x ) )
					up++;
				return ft::make_pair( low, up );
			}
	};

	template< class Key, class T, class Compare, class Allocator >
	bool	operator==( map< Key, T, Compare, Allocator > const & x, map< Key, T, Compare, Allocator> const & y ) 
	{
		if ( x.size() != y.size() )
			return false;
		return ft::equal( x.begin(), x.end(), y.begin() );
	}

	template< class Key, class T, class Compare, class Allocator >
	bool	operator<( map< Key, T, Compare, Allocator > const & x, map< Key, T, Compare, Allocator> const & y ) 
	{
		return ft::lexicographical_compare( x.begin(), x.end(), y.begin(), y.end() );
	}

	template< class Key, class T, class Compare, class Allocator >
	bool	operator!=( map< Key, T, Compare, Allocator > const & x, map< Key, T, Compare, Allocator> const & y ) 
	{
		return !( x == y );
	}

	template< class Key, class T, class Compare, class Allocator >
	bool	operator>( map< Key, T, Compare, Allocator > const & x, map< Key, T, Compare, Allocator> const & y ) 
	{
		return !( x <= y );
	}

	template< class Key, class T, class Compare, class Allocator >
	bool	operator>=( map< Key, T, Compare, Allocator > const & x, map< Key, T, Compare, Allocator> const & y ) 
	{
		return !( x < y );
	}

	template< class Key, class T, class Compare, class Allocator >
	bool	operator<=( map< Key, T, Compare, Allocator > const & x, map< Key, T, Compare, Allocator> const & y ) 
	{
		return !( y < x );
	}

}

namespace std 
{
	template< class Key, class T, class Compare, class Allocator >
	void	swap( ft::map< Key, T, Compare, Allocator > & x, ft::map< Key, T, Compare, Allocator > & y ) 
	{
		x.swap( y );
		return ;
	}
}

#endif