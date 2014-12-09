#pragma once

#include <netalicious/eggclock.hpp>

#include <netalicious/asio/loopasio.hpp>

#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/function.hpp>

namespace netalicious {

class EggClockAsio : public EggClock {
public:
	EggClockAsio(
			const boost::shared_ptr<LoopAsio>& aLoop);
	~EggClockAsio();

	void setTimeout(
			boost::posix_time::time_duration aTimeout,
			boost::function<void (bool)> aCallback);

	void cancel();

private:
	boost::asio::deadline_timer myTimer;
};

}
