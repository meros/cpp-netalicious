#include "gtest/gtest.h"
#include <src/netalicious/asio/tcpchannelasio.hpp>

#include <boost/shared_ptr.hpp>

using namespace boost;
using namespace netalicious;

TEST(TcpChannel, SimpleCreate)
{
	shared_ptr<LoopAsio> loop(new LoopAsio());

	// A closed socket...
	shared_ptr<asio::ip::tcp::socket> socket(new asio::ip::tcp::socket(*loop->getAsioIo().get()));
    shared_ptr<TcpChannelAsio> tcpAcceptor (new TcpChannelAsio(loop, socket));
}
