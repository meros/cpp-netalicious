#pragma once

#include <netalicious/netalicious.hpp>

namespace netalicious {

class NetaliciousAsio : public Netalicious {
public:
	~NetaliciousAsio();

	boost::shared_ptr<Loop> createLoop();

	boost::shared_ptr<EggClock> createEggclock(
			boost::shared_ptr<Loop> aLoop);

	boost::shared_ptr<TcpAcceptor> createTcpAcceptor(
			boost::shared_ptr<Loop> aLoop);
};

}
