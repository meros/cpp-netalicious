#include "tcpchannelasio.hpp"

namespace netalicious {

TcpChannelAsio::TcpChannelAsio(
		const boost::shared_ptr<LoopAsio>& aLoop)
: ourLoop(aLoop)
, mySocket(*aLoop->getAsioIo().get()) {

}

void
TcpChannelAsio::read(const ReadDoneFunc& aReadDoneFunc) {
	mySocket.async_receive(
			boost::asio::buffer(read_buffer),
			boost::bind(&TcpChannelAsio::read_done, shared_from_this(), aReadDoneFunc));
}

void
TcpChannelAsio::read_done(const ReadDoneFunc& aReadDoneFunc) {
	//TODO: error checking
	if (aReadDoneFunc()) {
		read(aReadDoneFunc);
	}
}

}
