#ifndef LN_MSG_TYPES_h_
#define LN_MSG_TYPES_h_

#include "SocketBuffer.h"

using namespace std;

class PackageProtocol
{
public:

	//���л�
	virtual  SocketClientBuffer Serialize() = 0;		
	//�����л�
	virtual void Deserialization( const SocketClientBuffer & _in) = 0;
};

class TmpPkg : PackageProtocol
{
public:
	virtual SocketClientBuffer Serialize() 
	{
		SocketClientBuffer scb(20);
		scb.SetContent("hello world", sizeof("hello world"));
		return scb;
	}

	virtual void Deserialization(const SocketClientBuffer & _in)
	{

	}
};

#endif // LN_MSG_TYPES_h_
