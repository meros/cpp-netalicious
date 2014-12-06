#include "tcpchannelasio.hpp"

namespace netalicious {

class CharArrayReadableBuffer : public ReadableBuffer {
public:
	CharArrayReadableBuffer() :
		readableBytes(1024) {
	}

	boost::asio::mutable_buffers_1 getAsioBuffer() {
		return boost::asio::buffer(buffer);
	}

	size_t getSize() {
		return readableBytes;
	}

	ReadableBufferPart readPart(size_t aOffset) {
		if(aOffset >= readableBytes) {
			return ReadableBufferPart();
		}

		return ReadableBufferPart(
				buffer + aOffset,
				readableBytes - aOffset);
	}

	void truncate(size_t newSize) {
		readableBytes = newSize;
	}

private:
	uint8_t buffer[1024];
	size_t readableBytes;
};

TcpChannelAsio::TcpChannelAsio(
		const boost::shared_ptr<LoopAsio>& aLoop)
: ourLoop(aLoop)
, mySocket(*aLoop->getAsioIo().get())
, myStrand(*aLoop->getAsioIo().get()){

}

void
TcpChannelAsio::read(const ReadDoneFunc& aReadDoneFunc) {
	// TODO: pool these...
	boost::shared_ptr<CharArrayReadableBuffer> buffer(new CharArrayReadableBuffer());

	mySocket.async_receive(
			buffer->getAsioBuffer(),
			boost::bind(&TcpChannelAsio::read_done, shared_from_this(), _2, aReadDoneFunc, buffer));
}

void
TcpChannelAsio::write(
		const boost::shared_ptr<ReadableBuffer>& aReadableBuffer,
		const WriteDoneFunc& aWriteDoneFunc) {

	ourLoop->getAsioIo().get()->post(
			myStrand.wrap(bind(
					&TcpChannelAsio::stranded_add_write_request,
					shared_from_this(),
					aReadableBuffer,
					aWriteDoneFunc)));
}

void
TcpChannelAsio::stranded_add_write_request(
		const boost::shared_ptr<ReadableBuffer>& aReadableBuffer,
		const WriteDoneFunc& aWriteDoneFunc) {
	myPendingWriteRequests.push(
			WriteRequest(aReadableBuffer, aWriteDoneFunc));

	stranded_start_write_next_request();
}


void
TcpChannelAsio::stranded_start_write_next_request() {
	if (myCurrentWriteRequest) {
		return;
	}

	if (!myPendingWriteRequests.empty()) {
		WriteRequest writeRequest = myPendingWriteRequests.front();
		myPendingWriteRequests.pop();

		myCurrentWriteRequest.reset(writeRequest);
		stranded_continue_write_current_request(0);
	}
}

void
TcpChannelAsio::stranded_continue_write_current_request(size_t aOffset) {
	assert(myCurrentWriteRequest);

	ReadableBufferPart part = myCurrentWriteRequest->readableBuffer->readPart(aOffset);

	if (part.size == 0) {
		myCurrentWriteRequest->writeDoneFunc();
		myCurrentWriteRequest.reset();
		stranded_start_write_next_request();
	} else {
		mySocket.async_write_some(
				boost::asio::buffer(
						part.buffer,
						part.size),
				myStrand.wrap(
						bind(&TcpChannelAsio::stranded_write_done,
								shared_from_this(),
								aOffset,
								boost::asio::placeholders::bytes_transferred())));
	}
}

void
TcpChannelAsio::stranded_write_done(
		size_t aOffset,
		size_t aBytesTransferred) {
	assert(myCurrentWriteRequest);
	stranded_continue_write_current_request(aOffset + aBytesTransferred);
}



void
TcpChannelAsio::read_done(
		size_t bytesRead,
		const ReadDoneFunc& aReadDoneFunc,
		const boost::shared_ptr<CharArrayReadableBuffer>& aReadableBuffer) {

	//TODO: error checking
	aReadableBuffer->truncate(bytesRead);
	if (aReadDoneFunc(aReadableBuffer)) {
		read(aReadDoneFunc);
	}
}

}
