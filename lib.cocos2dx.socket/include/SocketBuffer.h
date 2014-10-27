#ifndef SOCKETBUFFER_H_
#define SOCKETBUFFER_H_

#include "stdlib.h"
#include "memory"

class SocketClientBuffer
{
public:
	SocketClientBuffer();
	SocketClientBuffer( unsigned int initialSize );
	SocketClientBuffer( const SocketClientBuffer &);
	~SocketClientBuffer();


	// Set Content
	void SetContent(const void *src, size_t size);

	//return a pointer to the content buffer
	void *GetContent();

	size_t GetContentLength() { return _length; }
	size_t GetBufferSize() { return _buff_size; }
private:
	char * _buf;
	size_t _length;
	size_t _buff_size;
};

#endif // SOCKETBUFFER_H_
