#pragma once

#include <netalicious/readablebuffer.hpp>

#include <boost/cstdint.hpp>
#include <boost/function.hpp>

namespace netalicious {

class TcpChannel {
public:
	virtual ~TcpChannel() {}

	virtual bool isOpen() = 0;
	virtual void close() = 0;

	// callback function type for read
	// return: return true to read more or false to stop reading
	typedef boost::function<bool (
			const boost::shared_ptr<ReadableBuffer>& aReadableBuffer)> ReadDoneFunc;
	virtual void read(
			const ReadDoneFunc& aReadDoneFunc) = 0;

	// callback function type for write
	// TODO: error handling?
	typedef boost::function<void ()> WriteDoneFunc;
	virtual void write(
			const boost::shared_ptr<ReadableBuffer>& aReadableBuffer,
			const WriteDoneFunc& aWriteDoneFunc) = 0;
};

}
