#pragma once

#include <netalicious/loop.hpp>
#include <netalicious/eggclock.hpp>

#include <boost/shared_ptr.hpp>

namespace netalicious {

class Netalicious {
public:
	virtual ~Netalicious() {}

	static boost::shared_ptr<Netalicious> getDefault();

	virtual boost::shared_ptr<Loop> createLoop() = 0;

	virtual boost::shared_ptr<EggClock> createEggclock(
			boost::shared_ptr<Loop> aLoop) = 0;
};

}
