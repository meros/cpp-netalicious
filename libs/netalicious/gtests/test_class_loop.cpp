// SubtractTest.cpp
#include "gtest/gtest.h"
#include <src/netalicious/asio/loopasio.hpp>


TEST(LoopTest, SimpleCreate)
{
    boost::shared_ptr<netalicious::Loop> loop (new netalicious::LoopAsio);
}
