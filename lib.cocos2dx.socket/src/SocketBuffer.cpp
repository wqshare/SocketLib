#include "SocketConfig.h"
#include "SocketBuffer.h"
#include <exception>
#include <stdexcept>

SocketClientBuffer::SocketClientBuffer() try: buf_( new char[SOCKBUF_DEFAULT_SIZE]), length(SOCKBUF_DEFAULT_SIZE)
{

}
catch(std::exception &e)
{
	delete[] buf_;
};

SocketClientBuffer::SocketClientBuffer(unsigned int initialSize)
{
	if ( initialSize > SOCKBUF_MAX_SIZE)
		initialSize = SOCKBUF_MAX_SIZE;
	
	try
	{
		buf_ = new char[initialSize];
		length_ = initialSize;
	}
	catch (std::exception &e)
	{
		LOGI("realloc buffer exception in "__FUNCTION__);
		delete[] buf_;
		throw e;
	}

}

SocketClientBuffer::~SocketClientBuffer()
{
	delete[] buf_;
}

// Max Size , see SOCKBUF_MAX_SIZE in SocketConfig.h
void SocketClientBuffer::SetContent(const void *src, size_t size)
{
	try
	{
		if (size > SOCKBUF_MAX_SIZE)
			size = SOCKBUF_MAX_SIZE;
		if ( length_ < size )
		{
			delete[] buf_;
			buf_ = new char[size];
			memcpy(buf_, src, size);
		}
	}
	catch (std::exception &e)
	{
		LOGI("realloc buffer exception in "__FUNCTION__);
		throw e;
	}	
}

void * SocketClientBuffer::GetContent() 
{
	return buf_;
}


