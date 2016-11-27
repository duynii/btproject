#pragma once
#include <boost/optional.hpp>
#include "matrix.h"

namespace algo {

class djtra
{
    const matrix& board;
    int move_cost;
    Eigen::Array< index_t, Eigen::Dynamic, Eigen::Dynamic > previous;
    
    indices_t get_path( const index_t& target );
public:
    // djtra( const matrix& b, int move_cost_=1 ) : board(b), move_cost(move_cost_) {}
    djtra( const matrix& b, int move_cost_=1 );
    // return the targets that have been reached
    indices_t find(const index_t& source, const indices_t& targets);
};

} // namespace algo {
