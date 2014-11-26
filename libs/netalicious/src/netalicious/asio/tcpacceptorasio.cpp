#include "tcpacceptorasio.hpp"

namespace netalicious {

bool
TcpAcceptorAsio::bind(uint16_t port) {
	// TODO:
	return true;
}

void
TcpAcceptorAsio::accept(boost::function<void (bool ok)> aCallback) {
	// TODO:
	aCallback(false);
}


}
