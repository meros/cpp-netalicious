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

void print(const boost::system::error_code& /*e*/)
{
  std::cout << "Hello, world!\n";
}

void netalicious::EggClock::setTimeout(int timeout) {
	myPimpl->myTimer->expires_from_now(boost::posix_time::seconds(timeout));
	myPimpl->myTimer->async_wait(print);
}
