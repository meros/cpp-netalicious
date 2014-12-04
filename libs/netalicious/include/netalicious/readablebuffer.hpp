#pragma once

namespace netalicious {

class ReadableBuffer {
public:
	virtual ~ReadableBuffer() {}

	virtual size_t getSize() = 0;
};

}
