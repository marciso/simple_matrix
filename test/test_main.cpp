#include "backtrace.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char**argv)
{
    testing::InitGoogleTest(&argc, argv);

    register_backtrace_handler_for_signals(
            {SIGABRT, SIGSEGV, SIGBUS, SIGILL, SIGFPE, SIGPIPE},
            true);

    return RUN_ALL_TESTS();
}
