#ifndef PRA_T01_QUICKSORT_H
#define PRA_T01_QUICKSORT_H

#include <functional>
#include <algorithm>
#include <iterator>

template< typename BidirectionalIterator, typename Compare >
void quick_sort( BidirectionalIterator first, BidirectionalIterator last, Compare cmp ) {
    if( first != last ) {
        BidirectionalIterator left  = first;
        BidirectionalIterator right = last;
        BidirectionalIterator pivot = left++;

        while( left != right ) {
            if( cmp( *left, *pivot ) ) {
                ++left;
            } else {
                while( (left != right) && cmp( *pivot, *right ) )
                    --right;
                std::iter_swap( left, right );
            }
        }

        --left;
        std::iter_swap( pivot, left );

        quick_sort( first, left, cmp );
        quick_sort( right, last, cmp );
    }
}

template< typename BidirectionalIterator >
    inline void quick_sort( BidirectionalIterator first, BidirectionalIterator last ) {
        quick_sort( first, last,
                std::less_equal< typename std::iterator_traits< BidirectionalIterator >::value_type >()
                );
    }

#endif //PRA_T01_QUICKSORT_H
