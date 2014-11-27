#include "gtest/gtest.h"
#include <src/netalicious/asio/tcpacceptorasio.hpp>

#include <boost/shared_ptr.hpp>

using namespace boost;
using namespace netalicious;

TEST(TcpAcceptor, SimpleCreate)
{
	shared_ptr<LoopAsio> loop(new LoopAsio());
    shared_ptr<TcpAcceptorAsio> tcpAcceptor (new TcpAcceptorAsio(loop));
}
