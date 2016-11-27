#include <limits>
#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include "../matrix.h"
#include "../min_queue.h"

using namespace algo;

TEST( priority_queue, min_queue_with_costs )
{
    {
        min_queue_t queue;
        
        queue.push( cost_t(0,0) );
        queue.push( cost_t(1,1, 1) );
        queue.push( cost_t(2,2, 2) );
        queue.push( cost_t(5,5, 5) );
        
        EXPECT_EQ( 1, queue.top().cost );
        queue.pop();
        EXPECT_EQ( 2, queue.top().cost );
        queue.pop();
        EXPECT_EQ( cost_t(5,5, 5), queue.top() );
        queue.pop();
        EXPECT_EQ( cost_t(0, 0, cost_t::max()), queue.top() );
    }
}
TEST( priority_queue, min_queue_with_find_and_update )
{
    {
        min_queue_t queue;
        
        queue.push( cost_t(0,0) );
        queue.push( cost_t(1,1, 1) );
        queue.push( cost_t(2,2, 2) );
        queue.push( cost_t(5,5, 5) );
        
        // No such cell in the queue
        EXPECT_FALSE( queue.find_and_update( cost_t(9, 9, 9) ) );
        
        EXPECT_TRUE( queue.find_and_update( cost_t(5, 5, 0) ) );
        EXPECT_EQ( cost_t(5, 5, 0), queue.top() );
        queue.pop();
        
        EXPECT_TRUE( queue.find_and_update( cost_t(2, 2, 0) ) );
        EXPECT_EQ( cost_t(2, 2, 0), queue.top() );
        queue.pop();
        
        EXPECT_EQ( cost_t(1, 1, 1), queue.top() );
        queue.pop();
        
        EXPECT_EQ( cost_t(0, 0, cost_t::max()), queue.top() );
    }
}