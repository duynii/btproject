#pragma once
#include <boost/optional.hpp>
#include "matrix.h"

namespace algo {

class djtra
{
    const matrix& board;
    int move_cost;
    typedef Eigen::Array< index_t, Eigen::Dynamic, Eigen::Dynamic > previous_t;
    previous_t previous;
    
public:
    // djtra( const matrix& b, int move_cost_=1 ) : board(b), move_cost(move_cost_) {}
    djtra( const matrix& b, int move_cost_=1 );
    // return the targets that have been reached
    indices_t find(const index_t& source, const indices_t& targets);
    
    previous_t& get_previous() { return previous; }
    const previous_t& get_previous() const { return previous; }
    
    indices_t get_path( const index_t& target, const index_t& source );
};

} // namespace algo {
