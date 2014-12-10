#pragma once

#include <netalicious/loop.hpp>
#include <netalicious/eggclock.hpp>
#include <netalicious/tcpacceptor.hpp>
#include <netalicious/tcpconnector.hpp>
#include <netalicious/ipaddress.hpp>

#include <boost/shared_ptr.hpp>

namespace netalicious {

class Netalicious {
public:
	virtual ~Netalicious() {}

	static boost::shared_ptr<Netalicious> getDefault();

	virtual boost::shared_ptr<Loop> createLoop() = 0;

	virtual boost::shared_ptr<EggClock> createEggclock(
			boost::shared_ptr<Loop> aLoop) = 0;

	virtual boost::shared_ptr<TcpAcceptor> createTcpAcceptor(
			boost::shared_ptr<Loop> aLoop) = 0;

	virtual boost::shared_ptr<TcpConnector> createTcpConnector(
			boost::shared_ptr<Loop> aLoop) = 0;

	virtual boost::shared_ptr<IpAddress> createIpAddress(
			uint8_t aOctets[4]) = 0;
};

}
