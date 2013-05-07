// SubtractTest.cpp
#include "gtest/gtest.h"
#include "loop.hpp"
#include "eggclock.hpp"
#include <boost/bind.hpp>
#include <iostream>

using namespace netalicious;
using namespace boost;
using namespace std;

void timeout(bool aNormalTimeout, bool *aOutNormalTimeout) {
	cout << "Timeout called!" << endl;
	*aOutNormalTimeout = aNormalTimeout;
}

TEST(EggclockTest, TestTimeoutBeforeDone) {
	shared_ptr<Loop> loop(new Loop());
	shared_ptr<EggClock> eggclock(new EggClock(loop));

	bool normalTimeOut = false;
	eggclock->setTimeout(1, bind(timeout, _1, &normalTimeOut));

	loop->WaitDone();
	EXPECT_TRUE(normalTimeOut);
}
