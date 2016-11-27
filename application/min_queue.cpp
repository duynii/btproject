#include "min_queue.h"

namespace algo {
    
cost_t::cost_t() {}

cost_t::cost_t(uint_t r, uint_t c) : 
    index_t(r, c) , cost( std::numeric_limits< int >::max() )
{

}


min_queue_t::ordered_iterator min_queue_t::find(const index_t& index) const
{
    for( auto iter=ordered_begin(); iter!=ordered_end(); ++iter )
    {
        if( iter->row == index.row && iter->col == index.col ) { return iter; }
    }
    
    return ordered_end();
}

bool min_queue_t::find_and_update(const cost_t& item)
{
    for( auto iter=begin(); iter!=end(); ++iter )
    {
        if( iter->row == item.row && iter->col == item.col )
        {
            this->update( min_queue_t::s_handle_from_iterator(iter), item );
            return true;
        }
            
    }
    return false;
}



} // namespace algo {
