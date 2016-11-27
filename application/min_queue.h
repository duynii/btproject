#pragma once
#include <Eigen/Dense>
#include <vector>
#include <queue>
#include <boost/optional.hpp>
#include <boost/concept_check.hpp>
#include "matrix.h"
#include <boost/heap/priority_queue.hpp>
#include <boost/heap/fibonacci_heap.hpp>
#include <comma/base/types.h>

namespace algo {
    
/// Store a cost at a specific cell
/// The cost_t goes into the priority queue
struct cost_t : public index_t
{
public:
    int cost;
    
    cost_t();
    cost_t(uint_t r, uint_t c);
    cost_t(uint_t r, uint_t c, int cost) : index_t(r, c), cost(cost) {}
    
    static int max() { return std::numeric_limits< int >::max(); }
    
    struct greater {
        bool operator()(const cost_t& lhs, const cost_t& rhs) const { return lhs.cost > rhs.cost; }
    };
};

// Needed for gtest, to easily diagnose error
static std::ostream& operator<<( std::ostream& os, const cost_t& rhs) {
    os << '(' << rhs.row << ',' << rhs.col << ';' << rhs.cost << ')';
    return os;
}

/// Dijkstra's algorithm uses a min priority_queue, update of item in the queue is needed
class min_queue_t : public boost::heap::fibonacci_heap< cost_t, boost::heap::compare< cost_t::greater > >
{
public:
    min_queue_t::ordered_iterator find( const index_t& index ) const;
    bool find_and_update( const cost_t& item );
};
    
// Store cost with sum, could use std::pair instead
struct sum_t
{
    int cost;
    comma::uint64 sum;
    
    sum_t() : cost(cost_t::max()), sum( 0 ) {}
    sum_t( int c, comma::uint64 s ) : cost(c), sum(s) {}
};

} // namespace algo {
