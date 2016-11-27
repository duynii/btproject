#include <limits>
#include <gtest/gtest.h>
#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include "../matrix.h"
#include "../min_queue.h"

using namespace algo;
static std::ostream& operator<<( std::ostream& os, const cost_t& rhs) {
    os << '(' << rhs.row << ',' << rhs.col << ';' << rhs.cost << ')';
    return os;
}

TEST( priority_queue, min_queue_with_ints )
{
    typedef std::priority_queue< int, std::vector< int >, std::greater< int > > min_queue_int;
    min_queue_int queue;
    queue.push( 5 );
    queue.push( 1 );
    queue.push( 3 );
    queue.push( 9 );
    queue.push( std::numeric_limits< int >::max() );
    
    EXPECT_EQ( 1, queue.top() );
    queue.pop();
    EXPECT_EQ( 3, queue.top() );
    queue.pop();
    EXPECT_EQ( 5, queue.top() );
    queue.pop();
    EXPECT_EQ( 9, queue.top() );
    queue.pop();
    EXPECT_EQ( std::numeric_limits< int >::max(), queue.top() );
}

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
        
        queue.find_and_update( cost_t( 5, 5, 0 ) );
        EXPECT_EQ( cost_t(5, 5, 0), queue.top() );
        queue.pop();
        
        queue.find_and_update( cost_t( 2, 2, 0 ) );
        EXPECT_EQ( cost_t(2, 2, 0), queue.top() );
        queue.pop();
        
        EXPECT_EQ( cost_t(1, 1, 1), queue.top() );
        queue.pop();
        
        EXPECT_EQ( cost_t(0, 0, cost_t::max()), queue.top() );
    }
}