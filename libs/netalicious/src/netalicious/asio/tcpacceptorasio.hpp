#pragma once

#include <netalicious/asio/loopasio.hpp>
#include <netalicious/asio/tcpchannelasio.hpp>
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

	void accept(const AcceptDoneFunc& aAcceptDoneFunc);
private:
	void accept_done(
			const AcceptDoneFunc& aCallback,
			const boost::shared_ptr<TcpChannelAsio>& aTcpChannel);

private:
	boost::shared_ptr<LoopAsio> ourLoop;

	boost::asio::ip::tcp::acceptor myAcceptor;
};

}
