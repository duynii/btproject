#pragma once
#include <boost/optional.hpp>
#include <boost/concept_check.hpp>
#include "matrix.h"
#include "min_queue.h"
#include <comma/base/types.h>

namespace algo {

typedef Eigen::Array< sum_t, Eigen::Dynamic, Eigen::Dynamic > cost_matrix_t;

class djtra
{
    const matrix& board;    /// This is the grid to search
    int move_cost;      // cost from one square to the next
    typedef Eigen::Array< index_t, Eigen::Dynamic, Eigen::Dynamic > previous_t;
    // Each cell point to the previous cell on the path
    previous_t previous;
    // Store the cost to get to this cell, and the sum to get here
    cost_matrix_t cost_matrix_;     // Perhaps merge with previous
    
public:
    /// This code takes the grid as having a Directed Acyclic Graph
    // It does not build this graph
    // the cost of moving from one cell to the next is 1 for shortest path or
    // -1 for longest path
    enum class type { longest_path=-1, shortest_path=1 };
    /// Give it the grid to search on
    djtra( const matrix& b, type t=type::longest_path );
    
    /// @Brief Returns the path that is the longest or shortest
    // Given one source node/cell and multiple target cells
    // Note: If the grid has multiple lowest cell hence multiple sources, then call this function 
    // multiple times (in parallel?)
    // @param targets If multiple targets are set, returns the longest or shortest path
    // @Return Returns empty list if no target is reachable
    indices_t find(const index_t& source, const indices_t& targets);
    
    /// Accessors
    previous_t& get_previous() { return previous; }
    const previous_t& get_previous() const { return previous; }
    cost_matrix_t& costs() { return cost_matrix_; }
    const cost_matrix_t& costs() const { return cost_matrix_; }
    
    /// Given that we know there is a path from source to target
    // This data is encoded in 'previous' grid
    // Return the sequence of cells for the path from source to target
    indices_t get_path( const index_t& target, const index_t& source );
};

} // namespace algo {
