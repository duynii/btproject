#include <boost/optional.hpp>
#include "dj_path.h"
#include "min_queue.h"

namespace algo {
    
djtra::djtra(const matrix& b, int move_cost_) : board(b), move_cost(move_cost_)
    , previous( board.rows(), board.cols() )
{

}


static void populate_queue(  const matrix::array_type& a 
                           , const index_t& source
                           , min_queue_t& queue
                           , matrix::array_type& cost_matrix
                          )
{
    for(uint_t r=0; r<a.rows(); ++r)
    {
        for(uint_t c=0; c<a.cols(); ++c) { 
            cost_matrix( r, c ) = cost_t::max();
            if( index_t( r, c ) != source) { queue.push( cost_t(r, c) ); }
        }
    }
    // Zero cost for source node
    queue.push( cost_t( source.row, source.col, 0 ) );
    cost_matrix( source.row, source.col ) = 0;
}

indices_t djtra::get_path(const index_t& target)
{
    return indices_t();
}


// Attempt 1
//      Use matrix and std::priority_queue
//      Use Eigen Matrix
indices_t djtra::find(const index_t& source, const indices_t& targets)
{
    array_t visited = board;
    visited.setZero();
    
    min_queue_t queue;
    matrix::array_type cost_matrix;
    populate_queue( board, source, queue, cost_matrix );
    
    while( !queue.empty() )
    {
        const cost_t& cur = queue.top();
        queue.pop();
        if( cur.cost == cost_t::max() ) { break; } // Done
        
        int value = board( cur.row, cur.col );
        indices_t moves = board.move_from( cur, value, visited );
        
        // set targets here
        for( const index_t& node : moves )
        {
            int cost = value + move_cost;
            if( cost_matrix(node.row, node.col) > cost )
            {
                cost_matrix(node.row, node.col) = cost;
                previous(node.row, node.col) = cur;
                // TODO Set value in priority_queue here
            }
        }
        
        // set visited
        visited( cur.row, cur.col ) = 1;
        
        bool all_target_done = true;
        for( const auto& target : targets ) {
            if( !visited(target.row, target.col) ) { all_target_done = false; }
        }
        if( all_target_done )
        {
            // Todo pick best target
            return get_path( targets.front() );
        }
    }

    return indices_t();
}


} // namespace algo {
