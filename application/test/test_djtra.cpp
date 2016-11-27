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

TEST( djtra, find_shortest_path1 )
{
    algo::matrix board(3, 3);
    board <<    1, 4, 3,
                5, 5, 7,
                7, 6, 9;
    djtra path_search( board, djtra::type::shortest_path );
    
    // path 1, 5, 5 & 6
    indices_t path = path_search.find( index_t(0,0), { index_t(2, 1) } );
    EXPECT_EQ( 4, path.size() );
    EXPECT_EQ( index_t(0,0), path.front() );
    EXPECT_EQ( index_t(1,0), path[1] );
    EXPECT_EQ( index_t(1,1), path[2] );
    EXPECT_EQ( index_t(2,1), path.back() );
}

TEST( djtra, find_longest_path1 )
{
    algo::matrix board(3, 3);
    board <<    1, 4, 3,
                5, 5, 7,
                7, 6, 9;
    djtra path_search( board, djtra::type::longest_path );
    
    // There is only one path
    // path 1, 5, 5 & 6
    indices_t path = path_search.find( index_t(0,0), { index_t(2, 1) } );
    EXPECT_EQ( 4, path.size() );
    EXPECT_EQ( index_t(0,0), path.front() );
    EXPECT_EQ( index_t(1,0), path[1] );
    EXPECT_EQ( index_t(1,1), path[2] );
    EXPECT_EQ( index_t(2,1), path.back() );
}

TEST( djtra, find_longest_path2 )
{
    algo::matrix board(3, 3);
    board <<    1, 7, 7,
                2, 6, 8,
                3, 5, 9;
    djtra path_search( board, djtra::type::longest_path );
    
    // There is only one path
    // path 1, 5, 5 & 6
    indices_t path = path_search.find( index_t(0,0), { index_t(2, 2) } );
    EXPECT_EQ( 9, path.size() );
    EXPECT_EQ( index_t(0,0), path.front() );
    EXPECT_EQ( index_t(2,2), path.back() );
}

TEST( djtra, find_same_source_and_target )
{
    algo::matrix board(3, 3);
    board <<    1, 7, 7,
                6, 4, 8,
                3, 5, 9;
    djtra path_search( board, djtra::type::longest_path );
    
    // There is only one path
    // path 1, 5, 5 & 6
    indices_t path = path_search.find( index_t(1,1), { index_t(1, 1) } );
    EXPECT_EQ( 1, path.size() );
    EXPECT_EQ( index_t(1,1), path.front() );
}

TEST( djtra, find_cannot_reach_target )
{
    algo::matrix board(3, 3);
    board <<    1, 7, 7,
                5, 6, 8,
                3, 5, 9;
    djtra path_search( board, djtra::type::longest_path );
    
    // There is only one path
    // path 1, 5, 6, 8
    indices_t path = path_search.find( index_t(0,0), { index_t(2, 1) } );
    EXPECT_EQ( 0, path.size() );
}

TEST( djtra, find_selecting_longest_path )
{
    algo::matrix board(5, 5);
    board <<    3, 4, 4, 4, 5,
                2, 6, 8, 2, 6,
                1, 6, 8, 2, 8,
                1, 2, 2, 2, 10,
                3, 5, 9, 3, 3;
                
    djtra path_search( board, djtra::type::longest_path );
    
    // There are two paths
    indices_t path = path_search.find( index_t(2,0), { index_t(3, 4) } );
    EXPECT_EQ( 10, path.size() );
    EXPECT_EQ( index_t(2,0), path.front() );
    EXPECT_EQ( index_t(3,4), path.back() );
}
TEST( djtra, find_selecting_shortest_path )
{
    algo::matrix board(5, 5);
    board <<    3, 4, 4, 4, 5,
                2, 6, 8, 2, 6,
                1, 6, 8, 2, 8,
                1, 2, 2, 2, 10,
                3, 5, 9, 3, 3;
                
    djtra path_search( board, djtra::type::shortest_path );
    
    // There are two paths
    indices_t path = path_search.find( index_t(2,0), { index_t(3, 4) } );
    EXPECT_EQ( 6, path.size() );
//     EXPECT_EQ( index_t(2,0), path.front() );
//     EXPECT_EQ( index_t(3,4), path.back() );
}

TEST( djtra, find_selecting_longest_path_of_two_targets )
{
    algo::matrix board(5, 5);
    board <<    3, 4, 4, 4, 5,
                2, 6, 8, 2, 6,
                1, 6, 8, 2, 8,
                1, 2, 2, 3, 10,
                3, 5, 9, 10, 3;
                
    djtra path_search( board, djtra::type::longest_path );
    
    // There are two paths
    indices_t path = path_search.find( index_t(2,0), { index_t(3, 4), index_t(4, 3) } );
    EXPECT_EQ( 10, path.size() );
    EXPECT_EQ( index_t(2,0), path.front() );
    EXPECT_EQ( index_t(3,4), path.back() );
}

TEST( djtra, find_selecting_shortest_path_of_two_targets )
{
    algo::matrix board(5, 5);
    board <<    3, 4, 4, 4, 5,
                2, 6, 8, 2, 6,
                1, 6, 8, 2, 8,
                1, 2, 2, 3, 10,
                3, 5, 9, 10, 3;
                
    djtra path_search( board, djtra::type::shortest_path );
    
    // There are two paths
    indices_t path = path_search.find( index_t(2,0), { index_t(3, 4), index_t(4, 3) } );
    EXPECT_EQ( 6, path.size() );
    EXPECT_EQ( index_t(2,0), path.front() );
    EXPECT_EQ( index_t(4,3), path.back() );
}