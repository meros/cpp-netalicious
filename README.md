netalicious
===========

A small asynchronous network library for C++, with an event loop, timers and TCP. The application sees only a minimal interface; Boost.Asio does the work behind it.

Written 2013–2014; unmaintained.

What is this?
-------------
netalicious aims to be a simple (as in easy to use) network lib that is still based on a modern asynchronous model that should be able to scale well. That said, the design does not aim for best in class performance, target audience is hobby projects that want an easy to use cross platform event driven network library.

The library consists of a minimal interface with an asio implementation (hidden from application) as well as utilities to extend in ease of use. 

Current status
--------------
* Loop - main event source - fully working but limited in flexibility concerning threading etc
* EggClock - timed event callbacks, fully working 
* TcpAcceptor - listen on port and callback for each connecting tcp socket, working but lacking advanced options like choosing binding interface
* TcpChannel - connected tcp socket, able to write/read/close - what more do you need? :)
* ReadableBuffer - inteface for readable buffer fully working, need good utility iplementations for applications to use 
* TcpConnector - connect tcp to ip/port, fullly working 
* Resolver - resolve dns to ip - currently limed to 1 result and ipv4
* TODO: SslChannel
 
Utilities:

* String backed ReadableBuffer

The repository also has three example apps in `apps/` (eggclock, tcpacceptor, tcpconnector) and Google Test tests in `libs/netalicious/gtests/`.

Design decisions and random thoughts
------------------------------------
By choice the interface exposes very few errors (at the moment more or less none). The reason is that full range of errors is usually little help in implementing robust services. Better implement the binary 'worked/did not work' case fully than bother with lots of edge cases.

Never return null pointers, always wrap in optional if empty result is an option. Clear semantic signal on what user can expect and needs to take care of.

Build
-----
You need Boost 1.53 or later (thread, system, chrono) and [maker](https://github.com/meros/cpp-maker), another project of mine. Clone maker into a folder named `maker` next to netalicious:

* /workspace/netalicious
* /workspace/maker

```sh
mkdir workspace && cd workspace
git clone https://github.com/meros/cpp-netalicious.git netalicious
git clone https://github.com/meros/cpp-maker.git maker
mkdir build && cd build
cmake ../netalicious
make
```

The build files declare `cmake_minimum_required(VERSION 2.6)`, which CMake 4.x rejects. With CMake 4.x, add `-DCMAKE_POLICY_VERSION_MINIMUM=3.5` to the `cmake` command or use an older CMake. The build has not been tried with current compilers and Boost versions.

License
-------
0BSD. See `LICENSE`.
