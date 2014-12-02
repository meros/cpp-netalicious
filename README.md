netalicious
===========

What is this?
-------------
netalicious is a simple (as in easy to use) network lib that is still based on a modern asynchronous model that should be able to scale well. That said, the design does not aim for best in class performance, target audience is hobby projects that want an easy to use cross platform event driven network library.

Current status
--------------
This project is still in it's infancy, much is lacking.

As of now this is available:

* Loop - working
* EggClock - working
* TcpAcceptor - able to bind and accept socket
* TcpChannel - skeleton, implementation own a socket but there are no methods exposed
* TODO: TcpConnector
* TODO: SslChannel

Build
-----
To build this, you need maker, another project of mine. Clone maker in a folder next to netalicious and it should work:

* /workspace/netalicious
* /workspace/maker

Then use cmake as usual using netalicious as root source folder. I recommend building out of source.
