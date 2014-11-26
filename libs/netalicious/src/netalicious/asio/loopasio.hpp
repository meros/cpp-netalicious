#pragma once

#include <netalicious/loop.hpp>

#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>

namespace netalicious {

    class LoopAsio : public Loop {
    public:        
    	LoopAsio();
        ~LoopAsio();

    	void waitDone();

    	// Asio specific
    	boost::shared_ptr<boost::asio::io_service> getAsioIo();

    private:
    	// TODO: not like this. Run thread should be more flexible
    	boost::thread myRunThread;

    	boost::shared_ptr<boost::asio::io_service> myAsioIo;
    	boost::shared_ptr<boost::asio::io_service::work> myWork;
    };
}
