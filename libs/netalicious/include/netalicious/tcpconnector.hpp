#pragma once

#include <netalicious/tcpchannel.hpp>

#include <boost/cstdint.hpp>

namespace netalicious {

class TcpConnector {
public:
	virtual ~TcpConnector() {}

	// TODO: destination and callback
	typedef boost::function<void (const boost::shared_ptr<TcpChannel>& aTcpChannel)> ConnectDoneFunc;
	virtual void connect(const ConnectDoneFunc& aConnectDoneFunc) = 0;
};

}
