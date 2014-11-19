#include "loop-asio.hpp"

#include <boost/bind.hpp>

#include <iostream>

using namespace std;
using namespace netalicious;

void runTrampooline(boost::shared_ptr<boost::asio::io_service> myAsioIo) {
	myAsioIo->run();
}

LoopAsio::LoopAsio()
	: myAsioIo(new boost::asio::io_service())
	, myWork(new boost::asio::io_service::work(*myAsioIo))
{
	myRunThread = boost::thread(boost::bind(runTrampooline, myAsioIo));
}

boost::shared_ptr<boost::asio::io_service>
LoopAsio::GetAsioIo() {
	return myAsioIo;
}

LoopAsio::~LoopAsio() {
	myAsioIo->stop();
	myRunThread.join();
}

void LoopAsio::WaitDone() {
	myWork.reset();
	myRunThread.join();
}
