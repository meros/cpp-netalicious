#include <netalicious/asio/ipresolverasio.hpp>

#include <netalicious/asio/ipaddressv4asio.hpp>

#include <boost/optional.hpp>

namespace netalicious {

IpResolverAsio::IpResolverAsio(
		const boost::shared_ptr<LoopAsio>& aLoop)
	: ourLoop(aLoop)
	, myResolver(*aLoop->getAsioIo()){


}


void
IpResolverAsio::resolve(
		const std::string& aHostName,
		const ResolveDoneFunc& aResolveDoneFunc) {
	// TODO: make async
	// TODO: what if more than one result? Replace optional with list probably
	boost::asio::ip::tcp::resolver::iterator i =
			myResolver.resolve(boost::asio::ip::tcp::resolver::query(aHostName, ""));

	boost::optional<boost::shared_ptr<IpAddress> > optionalIpAddress
		= boost::optional<boost::shared_ptr<IpAddress> >();

	if (i != boost::asio::ip::tcp::resolver::iterator()) {
	    boost::asio::ip::tcp::endpoint end = *i;

	    boost::shared_ptr<IpAddressV4Asio> ipAddress(new IpAddressV4Asio());

	    // TODO: what if ipv6?
	    ipAddress->myAddress = end.address().to_v4();

		optionalIpAddress.reset(ipAddress);
	}

	aResolveDoneFunc(optionalIpAddress);
}

}
