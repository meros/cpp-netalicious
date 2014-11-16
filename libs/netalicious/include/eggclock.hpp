#pragma once

#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/function.hpp>

#include "loop.hpp"

namespace netalicious {

class EggClockPimpl;

class EggClock {
public:
	EggClock(boost::shared_ptr<Loop> &aLoop);

	// Set timeout, aCallback will be called when time has expired
	// If there is already an outstanding timeout, it will be cancelled
	void setTimeout(int aTimeout, boost::function<void (bool)> aCallback);

	// Cancel any outstanding timeouts,
	// callback will be called with false as argument
	void cancel();

	boost::shared_ptr<EggClockPimpl> myPimpl;
};
}
