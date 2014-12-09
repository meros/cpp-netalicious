#include "tcpconnectorasio.hpp"

#include <boost/asio/ip/tcp.hpp>

namespace netalicious {

TcpConnectorAsio::TcpConnectorAsio(
		const boost::shared_ptr<LoopAsio>& aLoop)
	: ourLoop(aLoop) {

}

void
TcpConnectorAsio::connect(
		const ConnectDoneFunc& aConnectDoneFunc) {
	// TOOD: change from sync to async!
	// TODO: no hard coded endpoints!
	boost::shared_ptr<TcpChannelAsio> channel(new TcpChannelAsio(ourLoop));
	boost::asio::ip::tcp::endpoint ep(
			boost::asio::ip::address::from_string("127.0.0.1"), 8080);

	channel->getAsioSocket().async_connect(
			ep,
			bind(&TcpConnectorAsio::connect_done,
					shared_from_this(),
					channel,
					aConnectDoneFunc));

}

void
TcpConnectorAsio::connect_done(
		const boost::shared_ptr<TcpChannelAsio>& aChannel,
		const ConnectDoneFunc& aConnectDoneFunc) {

	boost::optional<boost::shared_ptr<TcpChannel> > connectedChannel;

	// TODO: handle errors
	if (aChannel->isOpen()) {
		connectedChannel.reset(aChannel);
	}

	aConnectDoneFunc(connectedChannel);
}

}
