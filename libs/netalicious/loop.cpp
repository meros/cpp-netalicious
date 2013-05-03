#include <iostream>

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "loop.hpp"

using namespace std;

namespace netalicious {
class LoopPimpl {
public:
	LoopPimpl() :
			myAsioIo(new boost::asio::io_service), myWork(
					new boost::asio::io_service::work(*myAsioIo)), myRunThread(
					boost::bind(&LoopPimpl::run, this)) {
	}

	~LoopPimpl() {
		myAsioIo->stop();
		myRunThread.join();

		cout << "Done" << endl;
	}

private:
	friend class netalicious::Loop;
	void run() {
		cout << "running" << endl;
		myAsioIo->run();
		cout << "done" << endl;

	}

	boost::shared_ptr<boost::asio::io_service> myAsioIo;
	boost::thread myRunThread;
	boost::shared_ptr<boost::asio::io_service::work> myWork;
};
}

netalicious::Loop::Loop() {
	myPimpl.reset(new LoopPimpl());
}

netalicious::Loop::~Loop() {
}

void netalicious::Loop::WaitDone() {
	myPimpl->myWork.reset();
	myPimpl->myRunThread.join();
}

boost::shared_ptr<boost::asio::io_service> netalicious::Loop::getAsioService() {
	return myPimpl->myAsioIo;
}

