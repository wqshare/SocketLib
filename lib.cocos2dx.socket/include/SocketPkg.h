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



#endif // LN_MSG_TYPES_h_
