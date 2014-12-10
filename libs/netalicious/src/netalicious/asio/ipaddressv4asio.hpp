#pragma once

#include <netalicious/ipaddress.hpp>

#include <boost/asio/ip/address_v4.hpp>

namespace netalicious {

class IpAddressV4Asio : public IpAddress {
public:
	// TODO: encapsulate?
	boost::asio::ip::address_v4 myAddress;
};

}
