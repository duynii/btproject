#include "matrix.h"
#include <iostream>
#include <comma/base/exception.h>

namespace algo {
    
bool matrix::valid(const index_t& ix)
{
    return ix.row >= 0 && ix.col >= 0 && ix.row < uint_t(rows()) && ix.col < uint_t(cols());
}

    
indices_t matrix::move_from(const index_t& cur, uint_t sum, const array_t& visited)
{
    if( !valid(cur) ) { COMMA_THROW(comma::exception, "current index is invalid: " << cur.row << " " << cur.col ); }
    
    indices_t results;
    
    if( sum % 2 > 0 )
    {
        std::cerr << "odd vertical" << std::endl;
        index_t lower(cur.row - 1, cur.col);
        if( visited(lower.row, lower.col) == 0 && valid(lower) ) { results.push_back(lower); }
        index_t upper(cur.row + 1, cur.col);
        if( visited(upper.row, upper.col) == 0 && valid(upper) ) { results.push_back(upper); }
    }
    else
    {
        std::cerr << "even horizontal" << std::endl;
        index_t left(cur.row, cur.col - 1);
        if( visited(left.row, left.col) == 0   && valid(left) )  { results.push_back(left); }
        index_t right(cur.row, cur.col + 1);
        if( visited(right.row, right.col) == 0 && valid(right) ) { results.push_back(right); }
    }
    
    return std::move(results);
}


} // namespace algo {
