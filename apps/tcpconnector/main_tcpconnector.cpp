#include <iostream>

#include <netalicious/netalicious.hpp>
#include <netalicious/utils/stringreadablebuffer.hpp>

#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>

using namespace std;
using namespace boost;
using namespace netalicious;

void dummy() {

}

void write_done(boost::shared_ptr<TcpChannel> channel) {
	cout << "Writing done. Closing socket!" << endl;
	channel->close();
}

bool read_done(boost::shared_ptr<ReadableBuffer> buffer, boost::shared_ptr<TcpChannel> channel, int socketNum) {
	cout << "Got data on " << socketNum << ". Num bytes: " << buffer->getSize() << endl;

	// This here is how to read data from a buffer...
	// TODO: Utility functions for these things!
	size_t offset = 0;
	do {
		ReadableBufferPart part = buffer->readPart(offset);

		if (part.size == 0) {
			break;
		}

		for(size_t i = 0; i < part.size; i++) {
			cout << part.buffer[i];
		}

		offset += part.size;
	} while (true);

	channel->write(buffer, bind(write_done, channel));

	return buffer->getSize() > 0;
}

static int socketCounter = 0;

void connect_done(boost::optional<boost::shared_ptr<TcpChannel> > channel) {

	if (channel) {
		assert(*channel);
		cout << "Connected tcp socket" << endl;

		shared_ptr<StringReadableBuffer> initialWrite(new StringReadableBuffer());
		initialWrite->getString().append("GET / HTTP/1.0\r\n\r\n");
		initialWrite->commit();

		(*channel)->write(initialWrite, bind(dummy));
		(*channel)->read(bind(read_done, _1, *channel, socketCounter++));
	} else {
		cout << "Failed to connect" << endl;
	}
}

int main (int argc, char** argv) {
	cout << "Will connect socket on port 8080" << endl;

	boost::shared_ptr<Netalicious> netalicious = Netalicious::getDefault();
	boost::shared_ptr<Loop> loop = netalicious->createLoop();
	boost::shared_ptr<TcpConnector> tcpAcceptor = netalicious->createTcpConnector(loop);

	uint8_t google[] = {74, 125, 205, 106};
	uint8_t localhost[] = {127,0,0,1};
	tcpAcceptor->connect(
			netalicious->createIpAddress(google),
			80,
			bind(connect_done, _1));

	loop->waitDone();
}
