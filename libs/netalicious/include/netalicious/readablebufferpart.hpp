#pragma once

namespace netalicious {

// Simple class to hold
class ReadableBufferPart {
public:
	ReadableBufferPart()
	: buffer(0)
	, size(0) {}

	ReadableBufferPart(
			const uint8_t* aBuffer,
			const size_t aSize)
	: buffer(aBuffer)
	, size(aSize) {}

	const uint8_t* buffer;
	const size_t size;
};

}
