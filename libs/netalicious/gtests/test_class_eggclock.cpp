// SubtractTest.cpp
#include "gtest/gtest.h"
#include "loop.hpp"
#include "eggclock.hpp"

using namespace netalicious;
using namespace boost;

TEST(LoopTest, TestSimpleTimeout)
{
	shared_ptr<Loop> loop(new Loop());
	shared_ptr<EggClock> eggclock(new EggClock(loop));
	eggclock->setTimeout(1);
	loop->WaitDone();
}
