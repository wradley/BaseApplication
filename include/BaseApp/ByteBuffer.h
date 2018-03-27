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
		void expandmax(uint32_t newsize);

		// push
		void pushstring(const std::string &b);
		void push(unsigned long size, const void *data);

		// pop
		std::string popstring(unsigned int numchars);
		void* pop(unsigned long size); // must free it

	private:

		void resize();
		uint8_t *_start, *_end, *_max;

	};
}