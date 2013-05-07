#include "eggclock.hpp"

#include <iostream>
#include <boost/bind.hpp>

using namespace boost;
using namespace netalicious;
using namespace std;

namespace netalicious {
class EggClockPimpl {
public:
	EggClockPimpl(boost::asio::io_service &io_service) :
			myTimer(new asio::deadline_timer(io_service)) {
		cout << "Created EggClock" << endl;
	}

	shared_ptr<asio::deadline_timer> myTimer;
};
}

netalicious::EggClock::EggClock(shared_ptr<Loop> &aLoop) :
		myPimpl(new EggClockPimpl(*aLoop->getAsioService())) {
}

void timeoutTrampoline(const boost::system::error_code& err,
		boost::function<void(bool)> aCallback) {
	bool normalTimeOut = true;

	if (err == boost::asio::error::operation_aborted) {
		normalTimeOut = false;
	}

	aCallback(normalTimeOut);
}

void netalicious::EggClock::setTimeout(int aTimeout,
		boost::function<void(bool)> aCallback) {
	myPimpl->myTimer->expires_from_now(boost::posix_time::seconds(aTimeout));
	myPimpl->myTimer->async_wait(boost::bind(timeoutTrampoline, _1, aCallback));
}
