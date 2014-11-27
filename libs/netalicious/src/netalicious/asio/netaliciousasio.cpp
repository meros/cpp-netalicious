#include "netaliciousasio.hpp"

#include <netalicious/asio/loopasio.hpp>
#include <netalicious/asio/eggclockasio.hpp>
#include <netalicious/asio/tcpacceptorasio.hpp>

namespace netalicious {

NetaliciousAsio::~NetaliciousAsio() {

}

boost::shared_ptr<Loop>
NetaliciousAsio::createLoop() {
	return boost::shared_ptr<Loop>(new LoopAsio());
}

boost::shared_ptr<EggClock>
NetaliciousAsio::createEggclock(
		boost::shared_ptr<Loop> aLoop) {
	boost::shared_ptr<LoopAsio> loopAsio =
			boost::static_pointer_cast<LoopAsio>(aLoop);

	return boost::shared_ptr<EggClock>(new EggClockAsio(loopAsio));
}

boost::shared_ptr<TcpAcceptor>
NetaliciousAsio::createTcpAcceptor(
		boost::shared_ptr<Loop> aLoop) {
	boost::shared_ptr<LoopAsio> loopAsio =
			boost::static_pointer_cast<LoopAsio>(aLoop);

	return boost::shared_ptr<TcpAcceptor> (new TcpAcceptorAsio(loopAsio));
}


}
