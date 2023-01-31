#ifndef MAP_TREE_HPP
# define MAP_TREE_HPP

# include "utils.hpp"
# include "map_node.hpp"
# include "map_node_iterator.hpp"
# include "map_node_const_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft 
{
	template < class T, class Key_Compare, class Allocator = std::allocator< T > >
	class RBTree 
	{
		public :

			typedef T												value_type;
			typedef Key_Compare										key_compare;
			typedef Allocator										allocator_type;
			typedef typename Allocator::reference					reference;
			typedef typename Allocator::const_reference				const_reference;
			typedef ft::rbt_iterator<T>								iterator;
			typedef ft::rbt_const_iterator<T>						const_iterator;
			typedef typename Allocator::size_type					size_type;
			typedef typename Allocator::difference_type				difference_type;
			typedef typename Allocator::pointer						pointer;
			typedef typename Allocator::const_pointer				const_pointer;
			typedef ft::reverse_iterator< iterator >				reverse_iterator;
			typedef ft::reverse_iterator< const_iterator >			const_reverse_iterator;
			typedef ft::Node<T>										Node;
			typedef std::allocator<Node>							node_allocator_type;

		protected :
		
			Node *				_root;
			size_type			_size;
			allocator_type		_alloc;
			node_allocator_type	_nodeAlloc;
			key_compare		_comp;

			enum t_relativePos { LEFT = 0, RIGHT = 1 };

			Node *min() const 
			{
				Node * tmp = this->_root;
				while ( tmp && tmp->_left )
					tmp = tmp->_left;
				return tmp;
			}

			Node *max() const 
			{
				Node * tmp = this->_root;
				while (tmp && tmp->_right)
					tmp = tmp->_right;
				return tmp;
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

			void	clearRecursive( Node * node ) 
			{
				if ( node && node->_left )
					clearRecursive( node->_left );
				if ( node && node->_right )
					clearRecursive( node->_right);
				if ( node ) 
				{
					_nodeAlloc.destroy( node );
                    _nodeAlloc.deallocate( node, 1);
				}
			}

			Node * newNode( T const & value, Node * parent ) 
			{
				Node *	tmp = _nodeAlloc.allocate( 1 );
				_nodeAlloc.construct( tmp, Node( value, parent ) );
				return tmp;
			}

			void	adopt( Node * newParent, Node *child, t_relativePos position ) 
			{
				if ( newParent == NULL )
					return;
				if ( position == LEFT )
					newParent->_left = child;
				else
					newParent->_right = child;
				if ( child == NULL )
					return ;
				else
					child->_parent = newParent;
				return;
			}

			void	leftRotate( Node * toRotate ) 
			{
				if ( toRotate == NULL )
					return;

				Node *	parent = toRotate->_parent;
				Node *	child = toRotate->_right;

				adopt( toRotate, child->_left, RIGHT );
				if ( parent == NULL ) 
				{
					_root = child;
					_root->_parent = NULL;
				}
				else if ( parent->_left == toRotate )
					adopt( parent, child, LEFT );
				else
					adopt( parent, child, RIGHT );
				adopt( child, toRotate, LEFT );
				return;
			}

			void	rightRotate( Node *toRotate ) 
			{
				if ( toRotate == NULL )
					return;

				Node * parent = toRotate->_parent;
				Node * child = toRotate->_left;

				adopt( toRotate, child->_right, LEFT );
				if ( parent == NULL ) 
				{
					_root = child;
					_root->_parent = NULL;
				}
				else if ( parent && parent->_right == toRotate )
					adopt( parent, child, RIGHT );
				else
					adopt( parent, child, LEFT );
				adopt( child, toRotate, RIGHT);
				return;
			}

			void	transplant( Node * x, Node * y )
			{
				if ( x == NULL )
					return;
				if ( x->_parent == NULL )
					_root = y;
				else if ( x->_parent->_left == x )
					x->_parent->_left = y;
				else
					x->_parent->_right = y;

				if ( y )
					y->_parent = x->_parent;
				return ;
			}

			void	insertFix( Node *toInsert ) 
			{
				Node *parent = toInsert->_parent;
				Node *grandParent = parent != NULL ? parent->_parent : NULL;
				while ( toInsert && toInsert->_parent && toInsert->_parent->_color == Node::RED ) 
				{
					parent = toInsert->_parent;
					grandParent = parent != NULL ? parent->_parent : NULL;

					if ( grandParent && parent == grandParent->_left ) 
					{	
						if ( grandParent->_right && grandParent->_right->_color == Node::RED ) 
						{
							grandParent->_left->_color = Node::BLACK;
							grandParent->_right->_color = Node::BLACK;
							grandParent->_color = Node::RED;
							toInsert = grandParent;
						}
						else 
						{
							if ( parent->_right && parent->_right == toInsert ) 
							{
								toInsert = parent;
								leftRotate( toInsert );
							}
							if ( toInsert->_parent )
								toInsert->_parent->_color = Node::BLACK;
							if ( toInsert->_parent && toInsert->_parent->_parent ) 
								toInsert->_parent->_parent->_color = Node::RED;
							if ( toInsert->_parent) 
								rightRotate( toInsert->_parent->_parent );
						}
					}
					else 
					{
						if ( grandParent && grandParent->_left && grandParent->_left->_color == Node::RED ) 
						{
							grandParent->_left->_color = Node::BLACK;
							grandParent->_right->_color = Node::BLACK;
							grandParent->_color = Node::RED;
							toInsert = grandParent;
						}
						else 
						{
							if ( parent->_left && parent->_left == toInsert ) 
							{
								toInsert = parent;
								rightRotate( toInsert );
							}
							if ( toInsert->_parent )
								toInsert->_parent->_color = Node::BLACK;
							if ( toInsert->_parent && toInsert->_parent->_parent )
								toInsert->_parent->_parent->_color = Node::RED;
							if ( toInsert->_parent) 
								leftRotate( toInsert->_parent->_parent );
						}
					}
				}
				if ( _root && _root->_color == Node::RED )
					_root->_color = Node::BLACK;
			}

			void	deleteFix( Node * x, Node* parent ) 
			{
				Node * sibling;

				while ( x != _root &&  (x == NULL || x->_color == Node::BLACK) ) 
				{
					if (x != NULL)
						parent = x->_parent;
					if ( parent->_left == x ) 
					{
						sibling = parent->_right;
						if ( sibling && sibling->_color == Node::RED ) 
						{
							sibling->_color = Node::BLACK;
							parent->_color = Node::RED;
							leftRotate(parent );
							sibling = parent != NULL ?	parent->_right : NULL;
						}
						if ( sibling == NULL || ( ( sibling->_left == NULL || sibling->_left->_color == Node::BLACK ) && ( sibling->_right == NULL || sibling->_right->_color == Node::BLACK ) ) )
						{
							if ( sibling != NULL )
								sibling->_color = Node::RED;
							x = parent;
						}
						else 
						{
							if ( sibling->_right == NULL || sibling->_right->_color == Node::BLACK ) 
							{
								if ( sibling->_left != NULL )
									sibling->_left->_color = Node::BLACK;
								sibling->_color = Node::RED;
								rightRotate(sibling);
								sibling = parent != NULL ?	parent->_right : NULL;
							}
							if (sibling != NULL) 
							{
								sibling->_color = parent == NULL ?	Node::BLACK : parent->_color;
							}
							parent->_color = Node::BLACK;
							if ( sibling != NULL && sibling->_right != NULL )
								sibling->_right->_color = Node::BLACK;
							leftRotate(parent);
							x = _root;
							x->_parent = NULL;
						}
					}
					else 
					{
						sibling = parent->_left;
						if ( sibling && sibling->_color == Node::RED ) 
						{
							sibling->_color = Node::BLACK;
							parent->_color = Node::RED;
							rightRotate( parent );
							sibling = parent->_left;
						}
						if ( sibling == NULL || ( ( sibling->_left == NULL || sibling->_left->_color == Node::BLACK ) && ( sibling->_right == NULL || sibling->_right->_color == Node::BLACK ) ) ) 
						{
							if ( sibling != NULL )
								sibling->_color = Node::RED;
							x = parent;
						}
						else 
						{
							if ( sibling->_left == NULL || sibling->_left->_color == Node::BLACK ) 
							{
								if ( sibling->_right != NULL )
									sibling->_right->_color = Node::BLACK;
								sibling->_color = Node::RED;
								leftRotate(sibling);
								sibling = parent != NULL ?	parent->_left : NULL;
							}
							if (sibling != NULL) 
							{
								sibling->_color = parent == NULL ?	Node::BLACK : parent->_color;
							}
							parent->_color = Node::BLACK;
							if ( sibling != NULL && sibling->_left != NULL )
								sibling->_left->_color = Node::BLACK;
							rightRotate(parent);
							x = _root;
							x->_parent = NULL;
						}
					}
				}
				if (x != NULL)
					x->_color = Node::BLACK;
			}

			bool	isEqual( T const & x, T const & y) const 
			{				
				return _comp(x, y) == _comp(y, x);
			}

		public :

			RBTree( key_compare const & comp = key_compare()) : _root ( NULL ), _size ( 0 ), _alloc ( allocator_type() ), _nodeAlloc ( node_allocator_type() ), _comp ( comp ) 
			{
				return ;
			}

			~RBTree() 
			{
				this->clear();
				return;
			}

			RBTree &	operator=( RBTree const & rhs ) 
			{
				if ( this != &rhs ) 
				{
					clear();
					insert(rhs.begin(), rhs.end());
				}
				return *this;
			}

			Node * getRoot() const 
			{
				return this->_root;
			}

			void	setRoot( Node *newRoot ) 
			{
				_root = newRoot;
				return;
			}

			void	setSize( size_type newSize ) 
			{
				_size = newSize;
				return ;
			}

			void	clear() 
			{
				clearRecursive( _root );
				_size = 0;
				_root = NULL;
			}

			bool	empty() const { return (_size== 0); }
			size_type	size() const { return this->_size; }

			template< class InputIterator >
			void	insert( InputIterator first, InputIterator last) 
			{
				for ( ; first != last ; ++first )
					insert( *first );
				return ;
			}

			iterator	insert( iterator position, T const & newValue ) 
			{
				(void)position;
				return insert( newValue ).first;	
			}

			iterator	insert( const_iterator position, T const & newValue ) 
			{
				(void)position;
				return insert( newValue ).first;	
			}

			ft::pair<iterator, bool>	insert( T const & newValue ) 
			{
				if ( _root == NULL ) 
				{
					_root = newNode( newValue, NULL );
					_root->_color = Node::BLACK;
					_size++;
					return ft::make_pair( iterator( _root ), true );
				}

				Node *tmp = _root;
				if ( isEqual(tmp->_value, newValue ) )
					return ft::make_pair( iterator( tmp ), false );

				Node *next = _comp( newValue, tmp->_value ) ? tmp->_left : tmp->_right;
				while ( next != NULL ) 
				{
					tmp = next;
					next = _comp( newValue, tmp->_value ) ?	tmp->_left : tmp->_right;
					if ( isEqual(tmp->_value, newValue ) )
						return ft::make_pair( iterator( tmp ), false );
				}
				if ( isEqual(tmp->_value, newValue ) )
					return ft::make_pair( iterator( tmp ), false );

				Node *	toInsert = newNode( newValue, NULL );
				if ( _comp( newValue, tmp->_value ) )
					adopt(tmp, toInsert, LEFT);
				else
					adopt(tmp, toInsert, RIGHT);
				insertFix(toInsert);
				_size++;
				return ft::make_pair( iterator( toInsert ), true );
			}

			size_type	erase( Node *toDelete ) 
			{
				Node *	x;
				Node *	y;

				Node *parent = toDelete->_parent;

				typename Node::t_color originalColor = toDelete->_color;
				if ( toDelete->_left == NULL ) 
				{
					x = toDelete->_right;
					transplant( toDelete, x);
				}
				else if ( toDelete->_right == NULL) 
				{
					x = toDelete->_left;
					transplant(toDelete, x);
				}
				else 
				{
					y = min(toDelete->_right);
					originalColor = y->_color;
					x = y->_right;
					if ( y->_parent == toDelete )
						parent = y;
					else 
					{
						parent = y->_parent;
						transplant( y, y->_right );
						y->_right = toDelete->_right;
						y->_right->_parent = y;
					}
					transplant( toDelete, y );
					y->_left = toDelete->_left;
					y->_left->_parent = y;
					y->_color = toDelete->_color;
				}
				_nodeAlloc.destroy( toDelete );
				_nodeAlloc.deallocate( toDelete, 1);

				if ( originalColor == Node::BLACK )
					deleteFix(x, parent);
				_size--;
				return 1;
			}

			iterator	begin() { return iterator( min(), this->_root ); }
			iterator	end() { return iterator ( NULL, this->_root ); }
			const_iterator	begin() const { return const_iterator( min(), this->_root ); }
			const_iterator	end() const { return const_iterator( NULL, this->_root ); }
			reverse_iterator	rbegin() { return reverse_iterator( this->end() ); }
			reverse_iterator	rend() { return reverse_iterator( this->begin() ); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator( this->end() ); }
			const_reverse_iterator	rend() const { return const_reverse_iterator( this->begin() ); }
	};
}

#endif