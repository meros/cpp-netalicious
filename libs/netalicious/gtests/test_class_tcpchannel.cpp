#include "gtest/gtest.h"
#include <src/netalicious/asio/tcpchannelasio.hpp>

#include <boost/shared_ptr.hpp>

using namespace boost;
using namespace netalicious;

TEST(TcpChannel, SimpleCreate)
{
	shared_ptr<LoopAsio> loop(new LoopAsio());

    shared_ptr<TcpChannelAsio> tcpAcceptor (new TcpChannelAsio(loop));
}
