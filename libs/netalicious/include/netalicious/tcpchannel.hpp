#pragma once

#include <netalicious/readablebuffer.hpp>

#include <boost/cstdint.hpp>
#include <boost/function.hpp>

namespace netalicious {

class TcpChannel {
public:
	virtual ~TcpChannel() {}

	// callback function type for read
	// return: return true to read more or false to stop reading
	typedef boost::function<bool (const boost::shared_ptr<ReadableBuffer>& aReadableBuffer)> ReadDoneFunc;
	virtual void read(const ReadDoneFunc& aReadDoneFunc) = 0;

	// TODO: callback!
	virtual void write(const boost::shared_ptr<ReadableBuffer>& aReadableBuffer) = 0;
};

}
