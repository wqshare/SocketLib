#include "SocketConfig.h"
#include "SocketBuffer.h"
#include <exception>
#include <stdexcept>

SocketClientBuffer::SocketClientBuffer() try: _buf( new char[SOCKBUF_DEFAULT_SIZE]), _length(0), _buff_size(SOCKBUF_DEFAULT_SIZE)
{
	memset(_buf, 0, SOCKBUF_DEFAULT_SIZE);
}
catch(std::exception &e)
{
	LOGI("realloc buffer exception in "__FUNCTION__);
	delete[] _buf;
};

SocketClientBuffer::SocketClientBuffer(unsigned int initialSize) : _length(0)
{
	if ( initialSize > SOCKBUF_MAX_SIZE)
		initialSize = SOCKBUF_MAX_SIZE;

	try
	{
		_buf = new char[initialSize];
		_buff_size = initialSize;
		memset(_buf, 0, _buff_size);
	}
	catch (std::exception &e)
	{
		LOGI("realloc buffer exception in "__FUNCTION__);
		delete[] _buf;
		throw e;
	}

}

SocketClientBuffer::SocketClientBuffer(const SocketClientBuffer &_other)
{
	try
	{
		_buff_size = _other._buff_size;
		_length = _other._length;

		_buf = new char[_buff_size];
		memcpy(_buf, _other._buf, _buff_size);
	}
	catch (std::exception &e)
	{
		LOGI("realloc buffer exception in "__FUNCTION__);		
		throw e;
	}	
}

SocketClientBuffer::~SocketClientBuffer()
{
	delete[] _buf;
}

// Max Size , see SOCKBUF_MAX_SIZE in SocketConfig.h
void SocketClientBuffer::SetContent(const void *src, size_t size)
{
	try
	{
		if (size > SOCKBUF_MAX_SIZE)
			size = SOCKBUF_MAX_SIZE - 4;

		if ( _buff_size < size)
		{
			delete[] _buf;
			_buf = new char[size];
		}
		memcpy(_buf, src, size);
		_length = size;
	}
	catch (std::exception &e)
	{
		LOGI("realloc buffer exception in "__FUNCTION__);
		throw e;
	}	
}

void * SocketClientBuffer::GetContent() 
{
	return _buf;
}


