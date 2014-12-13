#include <netalicious/asio/ipresolverasio.hpp>

namespace netalicious {

IpResolverAsio::IpResolverAsio(
		const boost::shared_ptr<LoopAsio>& aLoop)
	: ourLoop(aLoop) {

}


}
