#include "tcpconnectorasio.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <netalicious/asio/ipaddressv4asio.hpp>

namespace netalicious {

TcpConnectorAsio::TcpConnectorAsio(
		const boost::shared_ptr<LoopAsio>& aLoop)
	: ourLoop(aLoop) {

}

void
TcpConnectorAsio::connect(
		const boost::shared_ptr<IpAddress>& aIpAddress,
		uint16_t aPort,
		const ConnectDoneFunc& aConnectDoneFunc) {

	boost::shared_ptr<IpAddressV4Asio> asiov4addr =
			boost::dynamic_pointer_cast<IpAddressV4Asio>(aIpAddress);

	if (!asiov4addr) {
		aConnectDoneFunc(boost::optional<boost::shared_ptr<TcpChannel> >());
		// TODO: log, this is bad usage!
		return;
	}

	boost::shared_ptr<TcpChannelAsio> channel(new TcpChannelAsio(ourLoop));
	boost::asio::ip::tcp::endpoint ep(asiov4addr->myAddress, aPort);

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
