#include "gtest/gtest.h"
#include <src/netalicious/asio/tcpacceptorasio.hpp>

#include <boost/shared_ptr.hpp>

TEST(TcpAcceptor, SimpleCreate)
{
    boost::shared_ptr<netalicious::TcpAcceptorAsio> tcpAcceptor (new netalicious::TcpAcceptorAsio());
}
