#pragma once

#include <netalicious/tcpacceptor.hpp>

#include <boost/function.hpp>

namespace netalicious {

class TcpAcceptorAsio : public TcpAcceptor {
public:
	bool bind(uint16_t port);

	void accept(boost::function<void (bool ok)>);
};

}
