#include "tcpacceptorasio.hpp"

#include <netalicious/asio/tcpchannelasio.hpp>

namespace netalicious {

TcpAcceptorAsio::TcpAcceptorAsio(
		const boost::shared_ptr<LoopAsio>& aLoop)
	: ourLoop(aLoop)
	, myAcceptor(*aLoop->getAsioIo()) {

}

bool
TcpAcceptorAsio::bind(uint16_t port) {
	boost::system::error_code ec;

	boost::asio::ip::tcp::endpoint endpoint(
						boost::asio::ip::tcp::v4(),
						port);

	if(myAcceptor.open(endpoint.protocol(), ec) ||
			myAcceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true), ec) ||
			myAcceptor.bind(endpoint, ec) ||
			myAcceptor.listen(boost::asio::socket_base::max_connections, ec)) {
		return false;
	}

	return true;
}


void
TcpAcceptorAsio::accept(const AcceptDoneFunc& aAcceptDoneFunc){
	boost::shared_ptr<boost::asio::ip::tcp::socket> socket(
      new boost::asio::ip::tcp::socket(*ourLoop->getAsioIo().get()));

    myAcceptor.async_accept(
    		*socket,
        boost::bind(
        		&TcpAcceptorAsio::accept_done,
				shared_from_this(),
				aAcceptDoneFunc,
				socket));
}

void
TcpAcceptorAsio::accept_done(
		const AcceptDoneFunc& aCallback,
		const boost::shared_ptr<boost::asio::ip::tcp::socket>& aSocket) {
	// TODO: check error
	boost::shared_ptr<TcpChannelAsio> tcpChannel(new TcpChannelAsio(ourLoop, aSocket));
	if (aCallback(tcpChannel)) {
		accept(aCallback);
	}
}



}
