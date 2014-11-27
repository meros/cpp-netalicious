#include <iostream>

#include <netalicious/netalicious.hpp>

#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>

using namespace std;
using namespace boost;
using namespace netalicious;

void accepted() {
	cout << "Accepted tcp socket" << endl;
}

int main (int argc, char** argv) {
	cout << "Will accept socket on port 8080" << endl;

	boost::shared_ptr<Netalicious> netalicious = Netalicious::getDefault();
	boost::shared_ptr<Loop> loop = netalicious->createLoop();
	boost::shared_ptr<TcpAcceptor> tcpAcceptor = netalicious->createTcpAcceptor(loop);

	tcpAcceptor->bind(8080);
	tcpAcceptor->accept(bind(accepted));

	loop->waitDone();
}
