#include <iostream>

#include <netalicious/netalicious.hpp>

#include <boost/bind.hpp>
#include <boost/smart_ptr.hpp>

using namespace std;
using namespace boost;
using namespace netalicious;

void eggClockTimeout(boost::shared_ptr<EggClock> eggClock) {
	static int i = 15;
	cout << i << " more seconds!" << endl;
	if (i--) {
		eggClock->setTimeout(
				boost::posix_time::seconds(1),
				boost::bind(eggClockTimeout, eggClock));
	}
}

int main (int argc, char** argv) {
	cout << "Will wait for 15 seconds..." << endl;

	boost::shared_ptr<Netalicious> netalicious = Netalicious::getDefault();
	boost::shared_ptr<Loop> loop = netalicious->createLoop();
	boost::shared_ptr<EggClock> eggClock = netalicious->createEggclock(loop);

	eggClockTimeout(eggClock);

	loop->waitDone();
}
