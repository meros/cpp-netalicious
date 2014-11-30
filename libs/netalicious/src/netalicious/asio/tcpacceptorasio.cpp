#include "tcpacceptorasio.hpp"

namespace netalicious {

TcpAcceptorAsio::TcpAcceptorAsio(
		const boost::shared_ptr<LoopAsio>& aLoop)
	: myAcceptor(*aLoop->getAsioIo())
	, ourIoService(aLoop->getAsioIo().get()) {

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
TcpAcceptorAsio::accept(boost::function<void (bool ok)> aCallback) {
    boost::asio::ip::tcp::socket *socket =
      new boost::asio::ip::tcp::socket(*ourIoService);

    myAcceptor.async_accept(
    		*socket,
        boost::bind(
        		&TcpAcceptorAsio::accept_done,
				shared_from_this(),
				aCallback,
				socket));
}

void
TcpAcceptorAsio::accept_done(
		boost::function<void (bool ok)> aCallback,
		boost::asio::ip::tcp::socket *socket) {
	aCallback(true);
}



}
