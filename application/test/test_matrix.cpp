#include <limits>
#include <gtest/gtest.h>
#include "../matrix.h"
#include <iostream>

using namespace algo;

static constexpr uint_t vertical = 11;
static constexpr uint_t horizontal = 10;

TEST( matrix, move_from_center )
{
    algo::matrix board(3, 3);
    board <<    1, 5, 3,
                5, 5, 5,
                7, 5, 9;
                
//     std::cerr << "board: " << std::endl << board << std::endl;
    
    // Move from center, horizontal
    {
        array_t visited = board;
        visited.setZero();
        
        indices_t indices = board.move_from(index_t(1,1), horizontal, visited);
        EXPECT_EQ( 2, indices.size() );
        
        EXPECT_EQ( 1, indices.front().row );
        EXPECT_EQ( 0, indices.front().col );
        
        EXPECT_EQ( 1, indices.back().row );
        EXPECT_EQ( 2, indices.back().col );
        
        visited(1, 0) = 1;
        indices = board.move_from(index_t(1,1), horizontal, visited);
        EXPECT_EQ( 1, indices.size() );
        
        EXPECT_EQ( 1, indices.front().row );
        EXPECT_EQ( 2, indices.front().col );
        
        visited(1, 2) = 1;
        indices = board.move_from(index_t(1,1), horizontal, visited);
        EXPECT_EQ( 0, indices.size() );
        
        visited(1, 0) = 0;
        indices = board.move_from(index_t(1,1), horizontal, visited);
        EXPECT_EQ( 1, indices.size() );
        
        EXPECT_EQ( 1, indices.front().row );
        EXPECT_EQ( 0, indices.front().col );
    }
    
    // Move from center, vertical
    {
        array_t visited = board;
        visited.setZero();
        
        indices_t indices = board.move_from(index_t(1,1), vertical, visited);
        EXPECT_EQ( 2, indices.size() );
        
        EXPECT_EQ( 0, indices.front().row );
        EXPECT_EQ( 1, indices.front().col );
        
        EXPECT_EQ( 2, indices.back().row );
        EXPECT_EQ( 1, indices.back().col );
        
        visited(0, 1) = 1;
        indices = board.move_from(index_t(1,1), vertical, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(2, 1), indices.front() );
        
        visited(2, 1) = 1;
        indices = board.move_from(index_t(1,1), vertical, visited);
        EXPECT_EQ( 0, indices.size() );
        
        visited(0, 1) = 0;
        indices = board.move_from(index_t(1,1), vertical, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(0, 1), indices.front() );
    }
}

TEST( matrix, move_from_center_check_values )
{
    indices_t indices;
    
    {
        algo::matrix board(3, 3);
        board <<    1, 5, 3,
                    4, 5, 4,
                    7, 5, 9;
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(1,1), horizontal, visited);
        EXPECT_EQ( 0, indices.size() );
        
        board <<    1, 5, 3,
                    5, 5, 4,
                    7, 5, 9;
        indices = board.move_from(index_t(1,1), horizontal, visited);
        EXPECT_EQ( 1, indices.size() );
        
        board <<    1, 5, 3,
                    4, 5, 5,
                    7, 5, 9;
        indices = board.move_from(index_t(1,1), horizontal, visited);
        EXPECT_EQ( 1, indices.size() );
        
        board <<    1, 5, 3,
                    5, 5, 5,
                    7, 5, 9;
        indices = board.move_from(index_t(1,1), horizontal, visited);
        EXPECT_EQ( 2, indices.size() );
        
        board <<    1, 5, 3,
                    6, 5, 7,
                    7, 5, 9;
        indices = board.move_from(index_t(1,1), horizontal, visited);
        EXPECT_EQ( 2, indices.size() );
    }
    //vertical
    {
        algo::matrix board(3, 3);
        board <<    1, 2, 3,
                    4, 5, 6,
                    7, 4, 9;
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(1,1), vertical, visited);
        EXPECT_EQ( 0, indices.size() );
        
        board <<    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9;
        indices = board.move_from(index_t(1,1), vertical, visited);
        EXPECT_EQ( 1, indices.size() );
        
        board <<    1, 6, 3,
                    4, 5, 6,
                    7, 4, 9;
        indices = board.move_from(index_t(1,1), vertical, visited);
        EXPECT_EQ( 1, indices.size() );
        
        board <<    1, 5, 3,
                    4, 5, 6,
                    7, 5, 9;
        indices = board.move_from(index_t(1,1), vertical, visited);
        EXPECT_EQ( 2, indices.size() );
    }
}

TEST( matrix, move_from_corner )
{
    algo::matrix board(3, 3);
    board <<    2, 2, 2,
                2, 5, 2,
                2, 2, 2;
                
//     std::cerr << "board: " << std::endl << board << std::endl;
    indices_t indices;
    // Move in top left, horizontal
    {
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(0,0), horizontal, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(0, 1), indices.front() );
        
        visited(0, 1) = 1;
        indices = board.move_from(index_t(0,0), horizontal, visited);
        EXPECT_TRUE( indices.empty() );
    }
    // Move in top left, vertical
    {
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(0,0), vertical, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(1, 0), indices.front() );
        
        visited(1, 0) = 1;
        indices = board.move_from(index_t(0,0), vertical, visited);
        EXPECT_TRUE( indices.empty() );
    }
    // Move in top right, horizontal
    {
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(0,2), horizontal, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(0, 1), indices.front() );
        
        visited(0, 1) = 1;
        indices = board.move_from(index_t(0,2), horizontal, visited);
        EXPECT_TRUE( indices.empty() );
    }
    // Move in top right, vertical
    {
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(0,2), vertical, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(1, 2), indices.front() );
        
        visited(1, 2) = 1;
        indices = board.move_from(index_t(0,2), vertical, visited);
        EXPECT_TRUE( indices.empty() );
    }
    
    
    // Move in bottom right, horizontal
    {
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(2,2), horizontal, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(2, 1), indices.front() );
        
        visited(2, 1) = 1;
        indices = board.move_from(index_t(2,2), horizontal, visited);
        EXPECT_TRUE( indices.empty() );
    }
    // Move in bottom right, vertical
    {
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(2,2), vertical, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(1, 2), indices.front() );
        
        visited(1, 2) = 1;
        indices = board.move_from(index_t(2,2), vertical, visited);
        EXPECT_TRUE( indices.empty() );
    }
    
    // Move in bottom left, horizontal
    {
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(2,0), horizontal, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(2, 1), indices.front() );
        
        visited(2, 1) = 1;
        indices = board.move_from(index_t(2,0), horizontal, visited);
        EXPECT_TRUE( indices.empty() );
    }
    // Move in bottom right, vertical
    {
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(2,0), vertical, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(1, 0), indices.front() );
        
        visited(1, 0) = 1;
        indices = board.move_from(index_t(2,0), vertical, visited);
        EXPECT_TRUE( indices.empty() );
    }
}

TEST( matrix, move_from_corner_and_check_values )
{
                
    indices_t indices;
    // Move in top left, horizontal
    {
        algo::matrix board(3, 3);
        board <<    2, 1, 2,
                    1, 5, 2,
                    2, 2, 2;
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(0,0), horizontal, visited);
        EXPECT_EQ( 0, indices.size() );
        
        board <<    2, 2, 2,
                    1, 5, 2,
                    2, 2, 2;
        indices = board.move_from(index_t(0,0), horizontal, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(0, 1), indices.front() );
        
        board <<    2, 3, 2,
                    1, 5, 2,
                    2, 2, 2;
        indices = board.move_from(index_t(0,0), horizontal, visited);
        EXPECT_EQ( 1, indices.size() );
    }
    // Move in top left, vertical
    {
        algo::matrix board(3, 3);
        board <<    2, 1, 2,
                    -1, 5, 2,
                    2, 2, 2;
        array_t visited = board;
        visited.setZero();
                    
        indices = board.move_from(index_t(0,0), vertical, visited);
        EXPECT_EQ( 0, indices.size() );
        
        board <<    2, 1, 2,
                    2, 5, 2,
                    2, 2, 2;
        indices = board.move_from(index_t(0,0), vertical, visited);
        EXPECT_EQ( 1, indices.size() );
        
        board <<    2, 1, 2,
                    4, 5, 2,
                    2, 2, 2;
        indices = board.move_from(index_t(0,0), vertical, visited);
        EXPECT_EQ( 1, indices.size() );
    }
    
    // Move in bottom right, horizontal
    {
        algo::matrix board(3, 3);
        board <<    2, 1, 2,
                    1, 5, 1,
                    2, 1, 2;
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(2,2), horizontal, visited);
        EXPECT_EQ( 0, indices.size() );
        
        board <<    2, 1, 2,
                    1, 5, 1,
                    2, 2, 2;
        indices = board.move_from(index_t(2,2), horizontal, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(2, 1), indices.front() );
        
        board <<    2, 1, 2,
                    1, 5, 1,
                    2, 3, 2;
        indices = board.move_from(index_t(2,2), horizontal, visited);
        EXPECT_EQ( 1, indices.size() );
    }
    // Move in bottom right, vertical
    {
        algo::matrix board(3, 3);
        board <<    2, 1, 2,
                    1, 5, 1,
                    2, 1, 2;
        array_t visited = board;
        visited.setZero();
                    
        indices = board.move_from(index_t(2,2), vertical, visited);
        EXPECT_EQ( 0, indices.size() );
        
        board <<    2, 1, 2,
                    1, 5, 2,
                    2, 1, 2;
        indices = board.move_from(index_t(2,2), vertical, visited);
        EXPECT_EQ( 1, indices.size() );
        
        board <<    2, 1, 2,
                    1, 5, 3,
                    2, 3, 2;
        indices = board.move_from(index_t(2,2), vertical, visited);
        EXPECT_EQ( 1, indices.size() );
    }
}

TEST( matrix, move_from_side )
{
    algo::matrix board(3, 3);
    board <<    5, 2, 3,
                4, 9, 6,
                7, 8, 9;
                
//     std::cerr << "board: " << std::endl << board << std::endl;
    indices_t indices;
    // left middle, horizontal
    {
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(1,0), horizontal, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(1, 1), indices.front() );
    }
    
    // middle bottom, horizontal
    {
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(2,1), vertical, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(1, 1), indices.front() );
    }
}