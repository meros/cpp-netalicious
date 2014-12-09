#pragma once

#include <boost/function.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace netalicious {

class EggClock {
public:
	virtual ~EggClock() {}

	// Set timeout, aCallback will be called when time has expired
	// If there is already an outstanding timeout, it will be cancelled
	virtual void setTimeout(
			// TODO: time abstraction??
			boost::posix_time::time_duration aTimeout,
			boost::function<void (bool)> aCallback) = 0;

	// Cancel any outstanding timeouts,
	// callback will be called with false as argument
	virtual void cancel() = 0;
};

}
