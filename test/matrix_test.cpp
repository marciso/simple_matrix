#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "matrix.hpp"

using namespace ::testing;

struct matrix_test : ::testing::Test
{
};

// export GTEST_ALSO_RUN_DISABLED_TESTS=1 to enable disabled tests
TEST_F(matrix_test, DISABLED_test_fail)
{
    FAIL();
}

TEST_F(matrix_test, test_)
{
    EXPECT_THAT(0, Eq(false));
}
