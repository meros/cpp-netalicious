#pragma once

#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>

namespace netalicious {

    class LoopPimpl;
    
    class Loop {
    public:        
        Loop();
        ~Loop();

    	void WaitDone();
    private:
        friend class EggClock;
        
        /* Implementation specifics, use only internally */
	boost::shared_ptr<boost::asio::io_service> getAsioService();

        boost::shared_ptr<LoopPimpl> myPimpl;
    };
}
