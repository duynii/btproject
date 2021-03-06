#include <boost/optional.hpp>
#include <comma/base/exception.h>
#include <iostream>
#include <stack>
#include "dj_path.h"
#include "min_queue.h"

namespace algo {
    
djtra::djtra(const matrix& b, type t) : board(b), move_cost(int(t))
    , previous( board.rows(), board.cols() )
    , cost_matrix_( board.rows(), board.cols() )
{

}


static void populate_queue(  const matrix::array_type& a 
                           , const index_t& source
                           , min_queue_t& queue
                           , cost_matrix_t& cost_matrix
                          )
{
    for(int r=0; r<a.rows(); ++r)
    {
        for(int c=0; c<a.cols(); ++c) 
        { 
            // cost to max for all
            cost_matrix( r, c ) = sum_t( cost_t::max(), 0 );
            if( index_t( r, c ) != source) { queue.push( cost_t(r, c) ); }
        }
    }
    // Zero cost for source node
    queue.push( cost_t( source.row, source.col, 0 ) );
    // set cost to zero for source, set sum
    cost_matrix( source.row, source.col ) = sum_t(0, a(source.row, source.col));
}

indices_t djtra::get_path(const index_t& target, const index_t& source)
{
    if( !board.valid(target) ) { COMMA_THROW( comma::exception, "target is invalid" ); }
    if( !board.valid(source) ) { COMMA_THROW( comma::exception, "source is invalid" ); }
    
    std::stack< index_t > stack;
    stack.push(target);
    
    // Test source == target
    
    uint_t count = 0;
    uint_t total_nodes = board.rows() * board.cols();
    
    index_t prev = target;
    while( prev != source)
    {
        ++count;
        
        const index_t& cur = prev;
        prev = previous(cur.row, cur.col);
        stack.push( prev );
        
        if( count > total_nodes ) { COMMA_THROW( comma::exception, "A path does not exist, incorrect target & source given" ); }
    }
    
    indices_t path;
    while( !stack.empty() ) { 
        path.push_back( stack.top() );
        stack.pop();
    }
    
    return path;
}


// Attempt 1
//      Use matrix and std::priority_queue
//      Use Eigen Matrix
indices_t djtra::find(const index_t& source, const indices_t& targets)
{
    array_t visited = board;
    visited.setZero();
    
    min_queue_t queue;
    cost_matrix_t& cost_matrix = cost_matrix_;
    
    // Populate the queue with all cells, also cost matrix 
    // Set the source cell to cost of 0, sum of value of the cell
    populate_queue( board, source, queue, cost_matrix );
    
    while( !queue.empty() )
    {
        const cost_t& cur = queue.top();
        queue.pop();
        if( cur.cost == cost_t::max() ) { 
//             std::cerr  << "No more node to visit" << std::endl;
            break; 
        } // Done
        
        sum_t cell = cost_matrix(cur.row, cur.col);
        
        // Find out which cells it can move to, if any
        indices_t moves = board.move_from( cur, cell.sum, visited );
        
//         std::cerr << "current: " << cur << " sum: " << cell.sum << " moves: " << moves.size() << std::endl;
        
        // process edges here (cells to move to)
        for( const index_t& node : moves )
        {
            int cost = cur.cost + move_cost;
            if( cost_matrix(node.row, node.col).cost > cost )
            {
                // set new cost at the next cell, and the sum at this cell
                cost_matrix(node.row, node.col) = sum_t( cost, cell.sum + board(node.row, node.col) );
                previous(node.row, node.col) = cur;     // set the path
                // Update value in priority_queue here
                queue.find_and_update( cost_t( node.row, node.col, cost ) );
            }
        }
        
        // set visited
        visited( cur.row, cur.col ) = 1;
        
        bool all_target_done = true;
        for( const auto& target : targets ) { if( !visited(target.row, target.col) ) { all_target_done = false; } }
        if( all_target_done )
        {
//             std::cerr  << "Found all target(s) " << targets.size() << std::endl;
            // Todo pick best target
            indices_t best_path =  get_path( targets.front(), source );
            
            auto it=targets.cbegin();
            ++it;
            for(; it!=targets.cend(); ++it) {
                indices_t path = get_path( *it, source );
                if( move_cost == int(type::longest_path) ) {
                    if( path.size() > best_path.size() ) { best_path = path; }
                }
                else {
                    if( path.size() < best_path.size() ) { best_path = path; }
                }
            } 
            return best_path;
        }
    }

    return indices_t();
}


} // namespace algo {
