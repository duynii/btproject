#pragma once
#include <Eigen/Dense>
#include <vector>
#include <queue>
#include <boost/optional.hpp>
#include <boost/concept_check.hpp>
#include "matrix.h"

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

typedef std::priority_queue< cost_t, std::vector< cost_t >, cost_t::greater > min_queue_t;


} // namespace algo {
