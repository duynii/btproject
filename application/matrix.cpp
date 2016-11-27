#include "matrix.h"
#include <iostream>
#include <comma/base/exception.h>

namespace algo {
    
bool matrix::valid(const index_t& ix) const
{
    return ix.row >= 0 && ix.col >= 0 && ix.row < uint_t(rows()) && ix.col < uint_t(cols());
}

    
indices_t matrix::move_from(const index_t& cur, uint_t sum, const array_t& visited) const
{
    if( !valid(cur) ) { COMMA_THROW(comma::exception, "current index is invalid: " << cur.row << " " << cur.col ); }
    
    const matrix& self = *this;
    auto value = self(cur.row, cur.col);
    indices_t results;
    
    if( sum % 2 > 0 )
    {
        index_t lower(cur.row - 1, cur.col);
        if( !visited(lower.row, lower.col)  && valid(lower) && movable(lower, value) ) { results.push_back(lower); }
        index_t upper(cur.row + 1, cur.col);
        if( !visited(upper.row, upper.col) && valid(upper) && movable(upper, value) ) { results.push_back(upper); }
    }
    else
    {
        index_t left(cur.row, cur.col - 1);
        if( !visited(left.row, left.col)   && valid(left) && movable(left, value) )  { results.push_back(left); }
        index_t right(cur.row, cur.col + 1);
        if( !visited(right.row, right.col) && valid(right) && movable(right, value) ) { results.push_back(right); }
    }
    
    return std::move(results);
}


} // namespace algo {
