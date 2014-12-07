#include "tcpconnectorasio.hpp"

#include <netalicious/asio/tcpchannelasio.hpp>

#include <boost/asio/ip/tcp.hpp>

namespace netalicious {

TcpConnectorAsio::TcpConnectorAsio(const boost::shared_ptr<LoopAsio>& aLoop)
	: ourLoop(aLoop) {

}

void
TcpConnectorAsio::connect(const ConnectDoneFunc& aConnectDoneFunc) {
	// TOOD: change from sync to async!
	// TODO: no hard coded endpoints!
	boost::shared_ptr<TcpChannelAsio> channel(new TcpChannelAsio(ourLoop));
	boost::asio::ip::tcp::endpoint ep(
			boost::asio::ip::address::from_string("127.0.0.1"), 8080);

	channel->getAsioSocket().connect(ep);

	// TODO: handle errors
	if (!channel->isOpen()) {
		channel.reset();
	}

	aConnectDoneFunc(channel);
}

}
