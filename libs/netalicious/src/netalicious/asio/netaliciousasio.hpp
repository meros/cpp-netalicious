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

	boost::shared_ptr<TcpConnector> createTcpConnector(
			boost::shared_ptr<Loop> aLoop);

	boost::shared_ptr<IpResolver> createIpResolver(
			boost::shared_ptr<Loop> aLoop);

	boost::shared_ptr<IpAddress> createIpAddress(
			uint8_t aOctets[4]);
};

}
