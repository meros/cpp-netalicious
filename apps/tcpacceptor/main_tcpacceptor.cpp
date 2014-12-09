#include <iostream>

#include <netalicious/netalicious.hpp>

#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>

using namespace std;
using namespace boost;
using namespace netalicious;

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

bool accept_done(boost::optional<boost::shared_ptr<TcpChannel> > channel) {
	if (channel) {
		cout << "Accepted tcp socket" << endl;
		(*channel)->read(bind(read_done, _1, *channel, socketCounter++));
		return true;
	} else {
		cout << "Failed to accept tcp socket" << endl;
		return true;
	}
}

int main (int argc, char** argv) {
	cout << "Will accept socket on port 8080" << endl;

	boost::shared_ptr<Netalicious> netalicious = Netalicious::getDefault();
	boost::shared_ptr<Loop> loop = netalicious->createLoop();
	boost::shared_ptr<TcpAcceptor> tcpAcceptor = netalicious->createTcpAcceptor(loop);

	tcpAcceptor->bind(8080);
	tcpAcceptor->accept(bind(accept_done, _1));

	loop->waitDone();
}
