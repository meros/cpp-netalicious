#pragma once

#include <netalicious/ipresolver.hpp>
#include <netalicious/asio/loopasio.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace netalicious {

class IpResolverAsio :
	public IpResolver,
	public boost::enable_shared_from_this<IpResolverAsio>{
public:
	IpResolverAsio(
			const boost::shared_ptr<LoopAsio>& aLoop);

	void resolve(
			const std::string& aHostName,
			const ResolveDoneFunc& aResolveDoneFunc);
private:
	boost::shared_ptr<LoopAsio> ourLoop;
	boost::asio::ip::tcp::resolver myResolver;
};

}
