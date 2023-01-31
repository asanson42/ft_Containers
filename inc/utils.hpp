#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
    
    template< bool B, class T = void >
    struct enable_if {};

    template< class T >
    struct enable_if< true, T > {typedef T type;};
    
    
    template <typename>
    struct is_integral_type
    {
        static bool const value = false;
    };

    template <>
    struct is_integral_type< bool >
    {
        static bool const value = true;
    };

    template <>
    struct is_integral_type< char >
    {
        static bool const value = true;
    };

    template <>
    struct is_integral_type< unsigned char >
    {
        static bool const value = true;
    };

    template <>
    struct is_integral_type< signed char >
    {
        static bool const value = true;
    };
    
    template <>
    struct is_integral_type< wchar_t >
    {
        static bool const value = true;
    };

    template <>
    struct is_integral_type< short int >
    {
        static bool const value = true;
    };

    template <>
    struct is_integral_type< unsigned short int >
    {
        static bool const value = true;
    };
    
    template <>
    struct is_integral_type< int >
    {
        static bool const value = true;
    };

    template <>
    struct is_integral_type< unsigned int >
    {
        static bool const value = true;
    };

    template <>
    struct is_integral_type< long int >
    {
        static bool const value = true;
    };

    template <>
    struct is_integral_type< unsigned long int >
    {
        static bool const value = true;
    };

    template <>
    struct is_integral_type< unsigned long long int >
    {
        static bool const value = true;
    };

    template < typename T >
    struct is_integral : is_integral_type< T > {};
    
   
    template< class InputIterator1, class InputIterator2 >
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        while (first1 != last1)
        {
            if (*first1 != *first2)
                return false;
            ++first1;
            ++first2;
        }
        return (true);
    }

    template< class InputIterator1, class InputIterator2, class BinaryPredicate >
    bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
    {
        while (first1 != last1)
        {
            if ( !pred( *first1, *first2))
                return (false);
            ++first1;
            ++first2;
        }
        return (true);
    }

    template< class InputIt1, class InputIt2 >
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
        {
            if (*first1 < *first2)
                return (true);
            if (*first2 < *first1)
                return (false);
        }
        return (first1 == last1) && (first2 != last2);
    }

    template< class InputIt1, class InputIt2, class Compare >
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
        {
            if (comp(*first1, *first2))
                return (true);
            if (comp (*first2, *first1))
                return (false);
        }
        return (first1 == last1) && (first2 != last2);
    }

    template< class T1, class T2 >
    struct pair
    {
        T1 first;
        T2 second;

        pair() : first (T1()), second (T2()) {};
        pair (const T1 &x, const T2 &y) : first (x), second (y) {};

        template < class U, class V>
        pair (const pair< U, V > &p) : first (p.first), second (p.second) {};

        pair &operator=(const pair &other)
        {
            if (this != &other)
            {
                this->first = other.first;
                this->second = other.second;
            }
            return (*this);
        }
    };

    template< class T1, class T2 >
	bool	operator==( const pair< T1, T2 > & x, const pair< T1, T2 > & y )
    {
		return x.first == y.first && x.second == y.second;
	}

	template< class T1, class T2 >
	bool	operator!=( const pair< T1, T2 > & x, const pair< T1, T2 > & y )
    {
		return !(x == y);
	}

	template< class T1, class T2 >
	bool	operator<( const pair< T1, T2 > & x, const pair< T1, T2 > & y )
    {
		return x.first < y.first || ( !( y.first < x.first ) && x.second < y.second );
	}

	template< class T1, class T2 >
	bool	operator<=( const pair< T1, T2 > & x, const pair< T1, T2 > & y )
    {
		return !(y < x);
	}

	template< class T1, class T2 >
	bool	operator>( const pair< T1, T2 > & x, const pair< T1, T2 > & y )
    {
		return y < x;
	}

	template< class T1, class T2 >
	bool	operator>=( const pair< T1, T2 > & x, const pair< T1, T2 > & y )
    {
		return !(x < y);
	}

    template< class T1, class T2 >
	pair< T1, T2 >	make_pair( const T1 & x, const T2 & y ) 
    {
		return pair< T1, T2 >( x, y );
	}
}

#endif