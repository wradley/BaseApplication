#include "ByteBuffer.h"
#include <stdlib.h>
#include <iostream>
#include <algorithm>

#define START_BUFFER_SIZE 1024

App::ByteBuffer::ByteBuffer() : 
	_start(nullptr), _end(nullptr), _max(nullptr), _popPtr(nullptr)
{
	_start = (uint8_t*)malloc(START_BUFFER_SIZE);
	if (!_start)
		std::cout << "Bad Malloc [App::ByteBuffer::ByteBuffer()]" << std::endl;

	_end = _start;
	_popPtr = _start;
	_max = _start + (START_BUFFER_SIZE - 1);
}


App::ByteBuffer::ByteBuffer(const ByteBuffer &b) : _start(nullptr), _end(nullptr), _max(nullptr)
{
	_start = (uint8_t*)malloc(b._max - b._start);
	memcpy(_start, b._start, b._end - b._start);
	_end = _start + (b._end - b._start);
	_max = _start + (b._max - b._start);
	_popPtr = _start + (b._popPtr - b._start);
}


App::ByteBuffer::ByteBuffer(ByteBuffer &&b) : _start(b._start), _end(b._end), _max(b._max)
{
	b._start = nullptr;
	b._end = nullptr;
	b._max = nullptr;
	b._popPtr = nullptr;
}


App::ByteBuffer& App::ByteBuffer::operator= (const ByteBuffer &b)
{
	_start = nullptr;
	_end = nullptr;
	_max = nullptr;
	_popPtr = nullptr;

	_start = (uint8_t*)malloc(b._max - b._start);
	memcpy(_start, b._start, b._end - b._start);
	_end = _start + (b._end - b._start);
	_max = _start + (b._max - b._start);
	_popPtr = _start + (b._popPtr - b._start);

	return *this;
}


App::ByteBuffer::~ByteBuffer()
{
	if (_start) free(_start);
}


unsigned int App::ByteBuffer::size() const
{
	return (unsigned int)(_end - _start);
}


void* App::ByteBuffer::head() const
{
	return _start;
}


void App::ByteBuffer::expandMax(uint32_t newsize)
{
	while (size() < newsize)
		resize();
}


void App::ByteBuffer::pushBack(unsigned long size, const void *data)
{
	while (_end + size >= _max)
		resize();

	memcpy(_end, data, size);

	_end += size;
}


void* App::ByteBuffer::popFront(unsigned long size)
{
	if (_popPtr + size <= _end)
	{
		void *data = _popPtr;
		_popPtr += size;
		return data;
	}

	return nullptr;
}


void App::ByteBuffer::resize()
{
	unsigned long currmax = _max - _start;
	unsigned long currsize = _end - _start;
	_start = (uint8_t*)realloc(_start, currmax * 2);
	if (!_start)
		std::cout << "Bad Realloc [App::ByteBuffer::resize()]" << std::endl;

	_end = _start + currsize;
	_max = _start + (currmax * 2);
}
