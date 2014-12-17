netalicious
===========

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

Design decisions and random thoughts
------------------------------------
By choice the interface exposes very few errors (at the moment more or less none). The reason is that full range of errors is usually little help in implementing robust services. Better implement the binary 'worked/did not work' case fully than bother with lots of edge cases.

Never return null pointers, always wrap in optional if empty result is an option. Clear semantic signal on what user can expect and needs to take care of.

Build
-----
To build this, you need maker, another project of mine. Clone maker in a folder next to netalicious and it should work:

* /workspace/netalicious
* /workspace/maker

Then use cmake as usual using netalicious as root source folder. I recommend building out of source.
