#pragma once

#include <netalicious/tcpconnector.hpp>
#include <netalicious/asio/loopasio.hpp>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

namespace netalicious {

class TcpConnectorAsio :
	public TcpConnector,
	public boost::enable_shared_from_this<TcpConnectorAsio>{
public:
	TcpConnectorAsio(const boost::shared_ptr<LoopAsio>& aLoop);

	void connect(const ConnectDoneFunc& aConnectDoneFunc);

private:
	boost::shared_ptr<LoopAsio> ourLoop;
};

}
