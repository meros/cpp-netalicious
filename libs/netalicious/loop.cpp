#include <iostream>

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "loop.hpp"

using namespace std;

namespace netalicious {
    class LoopPimpl {
    public:
        LoopPimpl()
        : myRunThread(boost::bind(&LoopPimpl::run, this)) {
        }
        
        ~LoopPimpl() {
            myAsioIo.stop();
            myRunThread.join();
            
            cout << "Done" << endl;
        }
        
    private:
        void run() {
            cout << "running" << endl;
            myAsioIo.run();
        }
        
        boost::asio::io_service myAsioIo;
        boost::thread myRunThread;
    };
}

netalicious::Loop::Loop() {
    myPimpl.reset(new LoopPimpl());
}

netalicious::Loop::~Loop() {
}