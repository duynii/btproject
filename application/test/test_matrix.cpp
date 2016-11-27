#include <limits>
#include <gtest/gtest.h>
#include "../matrix.h"
#include <iostream>

using namespace algo;
TEST( matrix, move_from_center )
{
    algo::matrix board(3, 3);
    board <<    1, 2, 3,
                4, 5, 6,
                7, 8, 9;
                
    std::cerr << "board: " << std::endl << board << std::endl;
//     std::cerr << "visited: " << std::endl << visited << std::endl;
       
    
    // Move in center, horizontal
    {
        array_t visited = board;
        visited.setZero();
        
        indices_t indices = board.move_from(index_t(1,1), 10, visited);
        EXPECT_EQ( 2, indices.size() );
        
        EXPECT_EQ( 1, indices.front().row );
        EXPECT_EQ( 0, indices.front().col );
        
        EXPECT_EQ( 1, indices.back().row );
        EXPECT_EQ( 2, indices.back().col );
        
        visited(1, 0) = 1;
        indices = board.move_from(index_t(1,1), 10, visited);
        EXPECT_EQ( 1, indices.size() );
        
        EXPECT_EQ( 1, indices.front().row );
        EXPECT_EQ( 2, indices.front().col );
        
        visited(1, 2) = 1;
        indices = board.move_from(index_t(1,1), 10, visited);
        EXPECT_EQ( 0, indices.size() );
        
        visited(1, 0) = 0;
        indices = board.move_from(index_t(1,1), 10, visited);
        EXPECT_EQ( 1, indices.size() );
        
        EXPECT_EQ( 1, indices.front().row );
        EXPECT_EQ( 0, indices.front().col );
    }
    
    // Move in center, vertical
    {
        array_t visited = board;
        visited.setZero();
        
        indices_t indices = board.move_from(index_t(1,1), 11, visited);
        EXPECT_EQ( 2, indices.size() );
        
        EXPECT_EQ( 0, indices.front().row );
        EXPECT_EQ( 1, indices.front().col );
        
        EXPECT_EQ( 2, indices.back().row );
        EXPECT_EQ( 1, indices.back().col );
        
        visited(0, 1) = 1;
        indices = board.move_from(index_t(1,1), 11, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(2, 1), indices.front() );
        
        visited(2, 1) = 1;
        indices = board.move_from(index_t(1,1), 11, visited);
        EXPECT_EQ( 0, indices.size() );
        
        visited(0, 1) = 0;
        indices = board.move_from(index_t(1,1), 11, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(0, 1), indices.front() );
    }
}


TEST( matrix, move_from_corner )
{
    algo::matrix board(3, 3);
    board <<    1, 2, 3,
                4, 5, 6,
                7, 8, 9;
                
    std::cerr << "board: " << std::endl << board << std::endl;
    indices_t indices;
    // Move in top left, horizontal
    {
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(0,0), 10, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(0, 1), indices.front() );
        
        visited(0, 1) = 1;
        indices = board.move_from(index_t(0,0), 10, visited);
        EXPECT_TRUE( indices.empty() );
    }
    // Move in top left, vertical
    {
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(0,0), 9, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(1, 0), indices.front() );
        
        visited(1, 0) = 1;
        indices = board.move_from(index_t(0,0), 9, visited);
        EXPECT_TRUE( indices.empty() );
    }
    // Move in top right, horizontal
    {
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(0,2), 10, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(0, 1), indices.front() );
        
        visited(0, 1) = 1;
        indices = board.move_from(index_t(0,2), 10, visited);
        EXPECT_TRUE( indices.empty() );
    }
    // Move in top right, vertical
    {
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(0,2), 9, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(1, 2), indices.front() );
        
        visited(1, 2) = 1;
        indices = board.move_from(index_t(0,2), 9, visited);
        EXPECT_TRUE( indices.empty() );
    }
    
    
    // Move in bottom right, horizontal
    {
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(2,2), 10, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(2, 1), indices.front() );
        
        visited(2, 1) = 1;
        indices = board.move_from(index_t(2,2), 10, visited);
        EXPECT_TRUE( indices.empty() );
    }
    // Move in bottom right, vertical
    {
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(2,2), 9, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(1, 2), indices.front() );
        
        visited(1, 2) = 1;
        indices = board.move_from(index_t(2,2), 9, visited);
        EXPECT_TRUE( indices.empty() );
    }
    
    // Move in bottom left, horizontal
    {
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(2,0), 10, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(2, 1), indices.front() );
        
        visited(2, 1) = 1;
        indices = board.move_from(index_t(2,0), 10, visited);
        EXPECT_TRUE( indices.empty() );
    }
    // Move in bottom right, vertical
    {
        array_t visited = board;
        visited.setZero();
        
        indices = board.move_from(index_t(2,0), 9, visited);
        EXPECT_EQ( 1, indices.size() );
        EXPECT_EQ(index_t(1, 0), indices.front() );
        
        visited(1, 0) = 1;
        indices = board.move_from(index_t(2,0), 9, visited);
        EXPECT_TRUE( indices.empty() );
    }
}