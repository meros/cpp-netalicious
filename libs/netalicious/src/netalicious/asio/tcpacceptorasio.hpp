#pragma once

#include <netalicious/asio/loopasio.hpp>
#include <netalicious/tcpacceptor.hpp>

#include <boost/asio.hpp>
#include <boost/function.hpp>

namespace netalicious {

class TcpAcceptorAsio :
	public TcpAcceptor,
	public boost::enable_shared_from_this<TcpAcceptorAsio>{
public:
	TcpAcceptorAsio(const boost::shared_ptr<LoopAsio>& aLoop);

	bool bind(uint16_t port);

	void accept(boost::function<void (bool ok)>);
private:
	void accept_done(
			boost::function<void (bool ok)> aCallback,
			boost::asio::ip::tcp::socket *socket);

private:
	boost::asio::ip::tcp::acceptor myAcceptor;
	boost::asio::io_service* ourIoService;
};

}
