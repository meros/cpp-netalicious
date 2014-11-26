#include "eggclockasio.hpp"

#include <netalicious/asio/loopasio.hpp>

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

EggClockAsio::EggClockAsio(const boost::shared_ptr<LoopAsio>& aLoop)
	: myTimer(*aLoop->getAsioIo()) {
}

EggClockAsio::~EggClockAsio() {

}

void EggClockAsio::setTimeout(
		boost::posix_time::time_duration aTimeout,
		boost::function<void(bool)> aCallback) {
	myTimer.expires_from_now(aTimeout);
	myTimer.async_wait(boost::bind(timeoutTrampoline, _1, aCallback));
}

void EggClockAsio::cancel() {
	myTimer.cancel();
}
