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
			const boost::shared_ptr<LoopAsio>& aLoop);

	void read(const ReadDoneFunc& aReadDoneFunc);

	boost::asio::ip::tcp::socket &getAsioSocket() {
		return mySocket;
	}

private:
	void read_done(const ReadDoneFunc& aReadDoneFunc);

private:
	boost::shared_ptr<LoopAsio> ourLoop;
	boost::asio::ip::tcp::socket mySocket;

	//TODO: temporary...
	uint8_t read_buffer[1024];
};

}
