#pragma once
#include <Eigen/Dense>
#include <vector>
#include <queue>
#include <boost/optional.hpp>
#include <boost/concept_check.hpp>
#include "matrix.h"
#include <boost/heap/priority_queue.hpp>
#include <boost/heap/fibonacci_heap.hpp>

namespace algo {
    

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

static std::ostream& operator<<( std::ostream& os, const cost_t& rhs) {
    os << '(' << rhs.row << ',' << rhs.col << ';' << rhs.cost << ')';
    return os;
}

// typedef std::priority_queue< cost_t, std::vector< cost_t >, cost_t::greater > min_queue_t;

class min_queue_t : public boost::heap::fibonacci_heap< cost_t, boost::heap::compare< cost_t::greater > >
{
public:
    min_queue_t::ordered_iterator find( const index_t& index ) const;
    bool find_and_update( const cost_t& item );
};

} // namespace algo {
