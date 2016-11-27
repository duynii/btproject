#include <limits>
#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include "../matrix.h"
#include "../min_queue.h"
#include "../dj_path.h"

using namespace algo;
static std::ostream& operator<<( std::ostream& os, const cost_t& rhs) {
    os << '(' << rhs.row << ',' << rhs.col << ';' << rhs.cost << ')';
    return os;
}

TEST( djtra, get_path )
{
    algo::matrix board(3, 3);
    board <<    1, 5, 3,
                5, 5, 5,
                7, 5, 9;
    djtra path_search( board );
    
    {
        // Make a dummy path across the board
        auto & prev = path_search.get_previous();
        prev << index_t(0,0), index_t(0,0), index_t(0,0),
                index_t(0,0), index_t(1,0), index_t(1,1),
                index_t(0,0), index_t(0,0), index_t(0,0); // left to right middle row
                
        indices_t path = path_search.get_path( index_t(1,2), index_t(1, 0) );
        EXPECT_EQ( 3, path.size() );
        EXPECT_EQ( index_t(1,0), path.front() );
        EXPECT_EQ( index_t(1,1), path[1] );
        EXPECT_EQ( index_t(1,2), path.back() );
    }
    {
        // Make a dummy path across the board
        auto & prev = path_search.get_previous();
        prev << index_t(0,0), index_t(0,0), index_t(0,0),
                index_t(0,0), index_t(0,1), index_t(1,1),
                index_t(0,0), index_t(0,0), index_t(0,0); // left to right middle row
                
        indices_t path = path_search.get_path( index_t(1,2), index_t(0, 0) );
        EXPECT_EQ( 4, path.size() );
        EXPECT_EQ( index_t(0,0), path.front() );
        EXPECT_EQ( index_t(0,1), path[1] );
        EXPECT_EQ( index_t(1,1), path[2] );
        EXPECT_EQ( index_t(1,2), path.back() );
    }
}
