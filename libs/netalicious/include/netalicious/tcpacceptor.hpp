#pragma once

#include <netalicious/tcpchannel.hpp>

#include <boost/cstdint.hpp>

namespace netalicious {

class TcpAcceptor {
public:
	virtual ~TcpAcceptor() {}

	// TODO: address!
	virtual bool bind(uint16_t port) = 0;

	// callback function type for accept
	// arguments: aTcpChannel, accepted channel or none if failed
	// return: return true to accept another channel or false to abort
	typedef boost::function<bool (const boost::shared_ptr<TcpChannel>& aTcpChannel)> AcceptDoneFunc;
	virtual void accept(const AcceptDoneFunc& aAcceptDoneFunc) = 0;
};

}
