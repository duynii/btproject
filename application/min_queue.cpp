#include "min_queue.h"

namespace algo {
    
cost_t::cost_t() {}

cost_t::cost_t(uint_t r, uint_t c) : 
    index_t(r, c) , cost( std::numeric_limits< int >::max() )
{

}



} // namespace algo {
