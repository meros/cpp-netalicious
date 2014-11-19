#include "eggclock-asio.hpp"

#include <netalicious/asio-impl/loop-asio.hpp>

#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>

using namespace boost;
using namespace netalicious;
using namespace std;

void timeoutTrampoline(const boost::system::error_code& err,
		boost::function<void(bool)> aCallback) {
	bool normalTimeOut = true;

	if (err == boost::asio::error::operation_aborted) {
		normalTimeOut = false;
	}

	aCallback(normalTimeOut);
}

EggClockAsio::EggClockAsio(const boost::shared_ptr<Loop>& aLoop)
	: myTimer(*boost::static_pointer_cast<LoopAsio>(aLoop)->GetAsioIo()) {

}

EggClockAsio::~EggClockAsio() {

}

void EggClockAsio::setTimeout(int aTimeout,
		boost::function<void(bool)> aCallback) {
	myTimer.expires_from_now(boost::posix_time::seconds(aTimeout));
	myTimer.async_wait(boost::bind(timeoutTrampoline, _1, aCallback));
}

void EggClockAsio::cancel() {
	myTimer.cancel();
}
