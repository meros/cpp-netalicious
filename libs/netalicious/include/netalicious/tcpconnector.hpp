#pragma once

#include <netalicious/ipaddress.hpp>
#include <netalicious/tcpchannel.hpp>

#include <boost/cstdint.hpp>
#include <boost/optional.hpp>

namespace netalicious {

class TcpConnector {
public:
	virtual ~TcpConnector() {}

	typedef boost::function<void (
			const boost::optional<boost::shared_ptr<TcpChannel> >& aTcpChannel)> ConnectDoneFunc;
	virtual void connect(
			const boost::shared_ptr<IpAddress>& aIpAddress,
			uint16_t port,
			const ConnectDoneFunc& aConnectDoneFunc) = 0;
};

}
