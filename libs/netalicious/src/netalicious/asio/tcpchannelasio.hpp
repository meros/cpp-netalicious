#pragma once

#include <netalicious/asio/loopasio.hpp>
#include <netalicious/tcpchannel.hpp>

#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/atomic.hpp>
#include <queue>
#include <boost/thread.hpp>

namespace netalicious {

class CharArrayReadableBuffer;

class TcpChannelAsio :
	public TcpChannel,
	public boost::enable_shared_from_this<TcpChannelAsio>{
public:
	TcpChannelAsio(
			const boost::shared_ptr<LoopAsio>& aLoop);

	void read(const ReadDoneFunc& aReadDoneFunc);

	void write(
			const boost::shared_ptr<ReadableBuffer>& aReadableBuffer,
			const WriteDoneFunc& aWriteDoneFunc);

	boost::asio::ip::tcp::socket &getAsioSocket() {
		return mySocket;
	}

private:
	void read_done(
			size_t bytesRead,
			const ReadDoneFunc& aReadDoneFunc,
			const boost::shared_ptr<CharArrayReadableBuffer>& aReadableBuffer);

private:
	// Writing, all done sequentially under strand:
	// add req. to queue
	void stranded_add_write_request(
			const boost::shared_ptr<ReadableBuffer>& aReadableBuffer,
			const WriteDoneFunc& aWriteDoneFunc);
	// if no current write outstanding, take first in queue
	void stranded_start_write_next_request();
	// Start/continue reading current request
	void stranded_continue_write_current_request(
			size_t aWriteOffset);
	void stranded_write_done(size_t aOffset, size_t aBytesTransferred);

private:

	struct WriteRequest {
		WriteRequest(
				boost::shared_ptr<ReadableBuffer> aReadableBuffer,
				WriteDoneFunc aWriteDoneFunc)
		: readableBuffer(aReadableBuffer)
		, writeDoneFunc(aWriteDoneFunc) {
		}

		WriteRequest() {}

		boost::shared_ptr<ReadableBuffer> readableBuffer;
		WriteDoneFunc writeDoneFunc;
	};

	boost::shared_ptr<LoopAsio> ourLoop;
	boost::asio::ip::tcp::socket mySocket;
	boost::asio::strand myStrand;

	// Access only in stranded methods
	std::queue<WriteRequest> myPendingWriteRequests;
	boost::optional<WriteRequest> myCurrentWriteRequest;
};

}
