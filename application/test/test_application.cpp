#include <limits>
#include <gtest/gtest.h>
#include <comma/application/command_line_options.h>
#include <comma/application/signal_flag.h>

TEST( application, dj_algorithm )
{
    EXPECT_TRUE( 1 == 1 );
    EXPECT_FALSE( 1 != 1 );
    EXPECT_EQ( 5, 5 );
    // TODO: definitely more tests!
}

