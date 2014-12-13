#pragma once

#include <netalicious/ipresolver.hpp>
#include <netalicious/asio/loopasio.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace netalicious {

class IpResolverAsio :
	public IpResolver,
	public boost::enable_shared_from_this<IpResolverAsio>{
public:
	IpResolverAsio(
			const boost::shared_ptr<LoopAsio>& aLoop);
private:
	boost::shared_ptr<LoopAsio> ourLoop;

};

}
