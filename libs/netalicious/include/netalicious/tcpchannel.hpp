#pragma once

#include <boost/cstdint.hpp>
#include <boost/function.hpp>

namespace netalicious {

class TcpChannel {
public:
	virtual ~TcpChannel() {}

	// callback function type for read
	// return: return true to read more or false to stop reading
	typedef boost::function<bool ()> ReadDoneFunc;
	virtual void read(const ReadDoneFunc& aReadDoneFunc) = 0;
};

}
