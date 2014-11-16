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

TEST(EggclockTest, TestTimeout) {
	shared_ptr<Loop> loop(new Loop());
	shared_ptr<EggClock> eggclock(new EggClock(loop));

	bool normalTimeOut = false;
	eggclock->setTimeout(1, bind(timeout, _1, &normalTimeOut));

	loop->WaitDone();
	EXPECT_TRUE(normalTimeOut);
}

TEST(EggclockTest, TestCancelDone) {
	shared_ptr<Loop> loop(new Loop());
	shared_ptr<EggClock> eggclock(new EggClock(loop));

	bool normalTimeOut = false;
	eggclock->setTimeout(1, bind(timeout, _1, &normalTimeOut));
	eggclock->cancel();
	loop->WaitDone();
	EXPECT_FALSE(normalTimeOut);
}

TEST(EggclockTest, TestTimeoutBeforeTimeout) {
	shared_ptr<Loop> loop(new Loop());
	shared_ptr<EggClock> eggclock(new EggClock(loop));

	bool normalTimeOut = false;
	eggclock->setTimeout(5, bind(timeout, _1, &normalTimeOut));
	boost::this_thread::sleep(boost::posix_time::seconds(3));
	EXPECT_FALSE(normalTimeOut);
	boost::this_thread::sleep(boost::posix_time::seconds(3));
	EXPECT_TRUE(normalTimeOut);
	loop->WaitDone();
}
