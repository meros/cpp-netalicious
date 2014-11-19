#pragma once

#include <netalicious/loop.hpp>

#include <boost/smart_ptr.hpp>
#include <boost/function.hpp>


namespace netalicious {

class EggClock {
public:
	virtual ~EggClock() {}

	// Set timeout, aCallback will be called when time has expired
	// If there is already an outstanding timeout, it will be cancelled
	virtual void setTimeout(
			int aTimeout,
			boost::function<void (bool)> aCallback) = 0;

	// Cancel any outstanding timeouts,
	// callback will be called with false as argument
	virtual void cancel() = 0;
};

}
