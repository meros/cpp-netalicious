#pragma once

#include <netalicious/asio/loopasio.hpp>
#include <netalicious/tcpchannel.hpp>

#include <boost/asio.hpp>
#include <boost/function.hpp>

namespace netalicious {

class CharArrayReadableBuffer;

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
	void read_done(
			size_t bytesRead,
			const ReadDoneFunc& aReadDoneFunc,
			const boost::shared_ptr<CharArrayReadableBuffer>& aReadableBuffer);

private:
	boost::shared_ptr<LoopAsio> ourLoop;
	boost::asio::ip::tcp::socket mySocket;
};

}
