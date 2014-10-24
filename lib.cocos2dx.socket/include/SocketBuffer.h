#ifndef SOCKETBUFFER_H_
#define SOCKETBUFFER_H_

#include "stdlib.h";
#include "memory"

class SocketClientBuffer
{
public:
	SocketClientBuffer();
	SocketClientBuffer( unsigned int initialSize );
	~SocketClientBuffer();


	// Set Content
	void SetContent(const void *src, size_t size);

	//return a pointer to the content buffer
	void *GetContent();

	size_t GetContentLength() { return length_; }
	size_t GetBufferSize() { return length_; }
private:
	char * buf_;
	size_t length_;
};

#endif // SOCKETBUFFER_H_
