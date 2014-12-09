#pragma once

namespace netalicious {

    class Loop {
    public:        
        virtual ~Loop() {};

    	virtual void waitDone() = 0;
    };
}
