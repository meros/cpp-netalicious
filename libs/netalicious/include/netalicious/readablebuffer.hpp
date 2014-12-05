#pragma once

#include <netalicious/readablebufferpart.hpp>

namespace netalicious {

class ReadableBuffer {
public:
	virtual ~ReadableBuffer() {}

	virtual size_t getSize() = 0;

	virtual ReadableBufferPart readPart(size_t aOffset) = 0;
};

}
