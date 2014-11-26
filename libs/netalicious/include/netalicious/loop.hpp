#pragma once

#include <boost/smart_ptr.hpp>

namespace netalicious {

    class LoopPimpl;
    
    class Loop {
    public:        
        virtual ~Loop() {};

    	virtual void waitDone() = 0;
    };
}
