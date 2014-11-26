#pragma once

#include <boost/cstdint.hpp>

namespace netalicious {

class TcpAcceptor {
public:
	virtual ~TcpAcceptor() {}

	// TODO: address!
	virtual bool bind(uint16_t port) = 0;
};

}
