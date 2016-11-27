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
    
};
static std::ostream& operator<<( std::ostream& os, const index_t& rhs) {
    os << '(' << rhs.row << ',' << rhs.col << ')';
    return os;
}
    
typedef std::vector< index_t > indices_t; 

typedef Eigen::ArrayXXi array_t;
class matrix : public array_t
{
public:
    indices_t move_from(const index_t& cur, uint_t sum, const array_t& visited);
    
    matrix(uint_t r, uint_t c) : array_t( r, c ) {}
private:
    bool valid(const index_t& ix);
};

} // namespace algo {