#include "gtest/gtest.h"

#include <src/netalicious/asio/eggclockasio.hpp>
#include <src/netalicious/asio/loopasio.hpp>

#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include <iostream>

using namespace netalicious;
using namespace boost;
using namespace std;

void timeout(bool aNormalTimeout, bool *aOutNormalTimeout) {
	cout << "Timeout called!" << endl;
	*aOutNormalTimeout = aNormalTimeout;
}

TEST(EggclockTest, TestTimeout) {
	shared_ptr<LoopAsio> loop(new LoopAsio());
	shared_ptr<EggClockAsio> eggclock(new EggClockAsio(loop));

	bool normalTimeOut = false;
	eggclock->setTimeout(
			boost::posix_time::milliseconds(100),
			bind(timeout, _1, &normalTimeOut));

	loop->waitDone();
	EXPECT_TRUE(normalTimeOut);
}

TEST(EggclockTest, TestCancelDone) {
	shared_ptr<LoopAsio> loop(new LoopAsio());
	shared_ptr<EggClockAsio> eggclock(new EggClockAsio(loop));

	bool normalTimeOut = false;
	eggclock->setTimeout(
			boost::posix_time::milliseconds(100),
			bind(timeout, _1, &normalTimeOut));
	eggclock->cancel();
	loop->waitDone();
	EXPECT_FALSE(normalTimeOut);
}

TEST(EggclockTest, TestTimeoutBeforeTimeout) {
	shared_ptr<LoopAsio> loop(new LoopAsio());
	shared_ptr<EggClockAsio> eggclock(new EggClockAsio(loop));

	bool normalTimeOut = false;
	eggclock->setTimeout(
			boost::posix_time::milliseconds(500),
			bind(timeout, _1, &normalTimeOut));
	boost::this_thread::sleep(boost::posix_time::milliseconds(10));
	EXPECT_FALSE(normalTimeOut);
	boost::this_thread::sleep(boost::posix_time::milliseconds(500));
	EXPECT_TRUE(normalTimeOut);
	loop->waitDone();
}
