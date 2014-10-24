#include "SocketPkg.h"
#include <stdint.h>

LoginPkg::LoginPkg() : userName_(""), pwd_("")
{
	length_ = 0;
}

LoginPkg::LoginPkg(std::string userName, std::string pwd) : userName_(userName), pwd_(pwd)
{
	
}

char * LoginPkg::Serialize()
{		
	char *c = new char[1024];

	sprintf(c + 4, "|user|%s|pwd|%s|", userName_.c_str(), pwd_.c_str());

	int32_t n = strlen(c + 4);

	memcpy(c, &n, 4);
	length_ = n + 4;
	return c;
}

void LoginPkg::Deserialization(const char * _in, unsigned int size)
{

}

unsigned int LoginPkg::length() const 
{
	return length_;
}
