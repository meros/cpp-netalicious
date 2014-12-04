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
, mySocket(*aLoop->getAsioIo().get()) {

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
