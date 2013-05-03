#pragma once

#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>

#include "Loop.hpp"

namespace netalicious {

class EggClockPimpl;

class EggClock {
public:
	EggClock(boost::shared_ptr<Loop> &aLoop);

	void setTimeout(int timeout);

	boost::shared_ptr<EggClockPimpl> myPimpl;
};
}
