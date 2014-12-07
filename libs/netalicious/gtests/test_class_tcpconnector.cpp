#include "gtest/gtest.h"
#include <src/netalicious/asio/tcpconnectorasio.hpp>

#include <boost/shared_ptr.hpp>

using namespace boost;
using namespace netalicious;

TEST(TcpConnector, SimpleCreate)
{
	shared_ptr<LoopAsio> loop(new LoopAsio());
    shared_ptr<TcpConnectorAsio> tcpAcceptor (new TcpConnectorAsio(loop));
}
