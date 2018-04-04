#pragma once
#include <stdint.h>
#include <string>

namespace App
{
	class ByteBuffer
	{
	public:

		ByteBuffer();
		ByteBuffer(const ByteBuffer &b);
		ByteBuffer(ByteBuffer &&b);
		ByteBuffer& operator= (const ByteBuffer &b);
		~ByteBuffer();

		unsigned int size() const;
		void* head() const;
		void expandMax(uint32_t newsize);

		// push
		void pushBack(unsigned long size, const void *data);

		// pop
		void* popFront(unsigned long size); // must free it

	private:

		void resize();
		uint8_t *_start, *_popPtr, *_end, *_max;

	};
}
