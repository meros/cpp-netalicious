#pragma once

#include <netalicious/ipaddress.hpp>

#include <boost/optional.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <string>


namespace netalicious {

class IpResolver {
public:
	virtual ~IpResolver() {}

	typedef boost::function<void (
			const boost::optional<boost::shared_ptr<IpAddress> >& aIpAddress)> ResolveDoneFunc;
	virtual void resolve(
			const std::string& aHostName,
			const ResolveDoneFunc& aResolveDoneFunc) = 0;

};

}
