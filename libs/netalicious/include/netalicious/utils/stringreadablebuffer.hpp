#pragma once

#include <netalicious/readablebuffer.hpp>

#include <vector>
#include <assert.h>

namespace netalicious {

// A readablebuffer that is backed by a c++ string
// c++ strings are interresting because they can contain any character
// (including null) and are usable as an easier than vector buffer
// since it has nice append functions etc.
class StringReadableBuffer : public ReadableBuffer {
public:
	StringReadableBuffer()
	: myIsWritable(true) {}

	void commit() {
		myIsWritable = false;
	}

	std::string& getString() {
		assert(myIsWritable);
		return myData;
	}

	size_t getSize() {
		assert(!myIsWritable);
		return myData.size();
	}

	ReadableBufferPart readPart(
			size_t aOffset) {
		assert(!myIsWritable);
		if (aOffset > getSize()) {
			return ReadableBufferPart();
		}

		return ReadableBufferPart(
				((const uint8_t*)&myData[0]) + aOffset,
				myData.size() - aOffset);
	}


private:
	bool myIsWritable;
	std::string myData;
};

}
