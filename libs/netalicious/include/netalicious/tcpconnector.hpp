#pragma once

#include <netalicious/tcpchannel.hpp>

#include <boost/cstdint.hpp>
#include <boost/optional.hpp>

namespace netalicious {

class TcpConnector {
public:
	virtual ~TcpConnector() {}

	// TODO: destination
	typedef boost::function<void (
			const boost::optional<boost::shared_ptr<TcpChannel> >& aTcpChannel)> ConnectDoneFunc;
	virtual void connect(
			const ConnectDoneFunc& aConnectDoneFunc) = 0;
};

}
