#pragma once

#include <Eigen/Dense>
#include <vector>
#include <boost/optional.hpp>

namespace algo {
    
typedef std::size_t uint_t;

struct index_t {
    uint_t row;
    uint_t col;
   
    index_t() : row(0), col(0) {}
    index_t( uint_t r, uint_t c ) : row(r), col(c) {}
    
    bool operator==(const index_t& rhs) const { 
        return row == rhs.row && col == rhs.col;
    }
    bool operator!=(const index_t& rhs) const { return !(*this == rhs); }
    
};
// static std::ostream& operator<<( std::ostream& os, const index_t& rhs) {
//     os << '(' << rhs.row << ',' << rhs.col << ')';
//     return os;
// }
    
typedef std::vector< index_t > indices_t; 

typedef Eigen::ArrayXXi array_t;
class matrix : public array_t
{
public:
    typedef array_t array_type;
    indices_t move_from(const index_t& cur, uint_t sum, const array_t& visited) const;
    
    inline bool movable( const index_t& index, int value) const { 
        const matrix& m = *this;
        return value <= m(index.row, index.col);
    }
    
    matrix(uint_t r, uint_t c) : array_t( r, c ) {}
private:
    bool valid(const index_t& ix) const;
};

} // namespace algo {
