#include "tcpchannelasio.hpp"

namespace netalicious {

TcpChannelAsio::TcpChannelAsio(
		const boost::shared_ptr<LoopAsio>& aLoop,
		const boost::shared_ptr<boost::asio::ip::tcp::socket>& aSocket)
: ourIoService(aLoop->getAsioIo().get())
, mySocket(aSocket) {

}

}
