#include <netalicious/netalicious.hpp>

#include <netalicious/asio/netaliciousasio.hpp>

namespace netalicious {

boost::shared_ptr<Netalicious>
Netalicious::getDefault() {
	return boost::shared_ptr<Netalicious>(new NetaliciousAsio());
}

}
