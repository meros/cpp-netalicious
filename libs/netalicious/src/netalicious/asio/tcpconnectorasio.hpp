#pragma once

#include <netalicious/tcpconnector.hpp>
#include <netalicious/asio/loopasio.hpp>
#include <netalicious/asio/tcpchannelasio.hpp>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

namespace netalicious {

class TcpConnectorAsio :
	public TcpConnector,
	public boost::enable_shared_from_this<TcpConnectorAsio>{
public:
	TcpConnectorAsio(const boost::shared_ptr<LoopAsio>& aLoop);

	void connect(
			const boost::shared_ptr<IpAddress>& aTcpEndpoint,
			uint16_t aPort,
			const ConnectDoneFunc& aConnectDoneFunc);

private:

	void connect_done(
			const boost::shared_ptr<TcpChannelAsio>& aChannel,
			const ConnectDoneFunc& aConnectDoneFunc);

	boost::shared_ptr<LoopAsio> ourLoop;
};

}
