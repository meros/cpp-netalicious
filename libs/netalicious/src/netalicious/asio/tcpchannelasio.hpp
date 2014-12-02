#pragma once

#include <netalicious/asio/loopasio.hpp>
#include <netalicious/tcpchannel.hpp>

#include <boost/asio.hpp>
#include <boost/function.hpp>

namespace netalicious {

class TcpChannelAsio :
	public TcpChannel,
	public boost::enable_shared_from_this<TcpChannelAsio>{
public:
	TcpChannelAsio(
			const boost::shared_ptr<LoopAsio>& aLoop,
			const boost::shared_ptr<boost::asio::ip::tcp::socket>& aSocket);

private:
	boost::asio::io_service* ourIoService;
	boost::shared_ptr<boost::asio::ip::tcp::socket> mySocket;
};

}
