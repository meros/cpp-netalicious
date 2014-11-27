#pragma once

#include <netalicious/asio/loopasio.hpp>
#include <netalicious/tcpacceptor.hpp>

#include <boost/asio.hpp>
#include <boost/function.hpp>

namespace netalicious {

class TcpAcceptorAsio : public TcpAcceptor {
public:
	TcpAcceptorAsio(const boost::shared_ptr<LoopAsio>& aLoop);

	bool bind(uint16_t port);

	void accept(boost::function<void (bool ok)>);

private:
	boost::asio::ip::tcp::acceptor myAcceptor;
};

}
