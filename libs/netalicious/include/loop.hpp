#pragma once

#include <boost/smart_ptr.hpp>

namespace netalicious {

    class LoopPimpl;
    
    class Loop {
    public:        
        Loop();
        ~Loop();
        
        boost::shared_ptr<LoopPimpl> myPimpl;
    };
}