#pragma once

#include <Eigen/Dense>
#include <vector>
#include <boost/optional.hpp>

namespace algo {
    
typedef std::size_t uint_t;

/// Struct to store indentify a cell by its row and column
struct index_t {
    uint_t row;
    uint_t col;
   
    index_t() : row(0), col(0) {}
    index_t( uint_t r, uint_t c ) : row(r), col(c) {}
    
    bool operator==(const index_t& rhs) const {  return row == rhs.row && col == rhs.col; }
    bool operator!=(const index_t& rhs) const { return !(*this == rhs); }
};

// Needed to diagnose errors for unit tests
static std::ostream& operator<<( std::ostream& os, const index_t& rhs) {
    os << '(' << rhs.row << ',' << rhs.col << ')';
    return os;
}

// A list of cells or a path
typedef std::vector< index_t > indices_t; 

// Using dynamic 2D grid, it can be any size
typedef Eigen::ArrayXXi array_t;
class matrix : public array_t
{
public:
    typedef array_t array_type;
    /// This function does a lot of the work, especially dealing with cell indices
    // There are unit tests to test out of bound
    // @param cur the current cell
    // @param sum the sum of values to get here, if odd move vertically only, else horizonal. Possibly need to store 0 or 1 only
    // @param A duplicated grid like the matrix, cells with 0 means un-visited
    // @return A list of indices that the cell can move to. May be empty if unable to move.
    indices_t move_from(const index_t& cur, uint_t sum, const array_t& visited) const;
    
    // Wraps the code to ensure moving to another cell of equal or greater value only
    inline bool movable( const index_t& index, int value) const { 
        const matrix& m = *this;
        return value <= m(index.row, index.col);
    }
    
    /// Constructor to create the 'grid'
    // The 'grid' is later initialised using comma separated list, see unit tests
    matrix(uint_t r, uint_t c) : array_t( r, c ) {}
    
    /// To check if a cell is not out of bound
    bool valid(const index_t& ix) const;
};

} // namespace algo {
