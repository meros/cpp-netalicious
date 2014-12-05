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
TcpChannelAsio::write(
		const boost::shared_ptr<ReadableBuffer>& aReadableBuffer) {

	// TODO: this should obviously be async! This is just temporary...
	// What needs to be done is to place buffer in list, and start a new write
	// (if one is not already pending)
	// Also.... callback! :)
	size_t offset = 0;
	do {
		ReadableBufferPart part = aReadableBuffer->readPart(offset);

		if (part.size == 0) {
			break;
		}

		boost::asio::write(mySocket, boost::asio::buffer(part.buffer, part.size));
		offset += part.size;
	} while (true);
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
