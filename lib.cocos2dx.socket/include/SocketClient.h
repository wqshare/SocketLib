#ifndef LN_SOCKET_h_
#define LN_SOCKET_h_

#ifdef _WIN32
#include <WinSock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")
#endif

#ifdef ANDROID
#include <string>  
#include <sys/socket.h>  
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <arpa/inet.h>
#include <android/log.h>  

#endif

#include <iostream>
#include <assert.h>
#include <string>
#include <stdint.h>

#include "uncopyable.h"
#include "SocketConfig.h"
#include "SocketBuffer.h"

#define MAX_BUFF_SIZE 1024

class SocketClient : private uncopyable
{
public:
	enum ErrorCode
	{
		NORMAL,
		CONNECT_SUCCESS,
		SEND_SUCCESS,
		RECV_SUCCESS,

		CREATE_SOCKET_FAILED,
		DNS_FAILED,
		CONNECT_FAILED,
		SELETE_ERROR,

		SET_NOBLOCK_ERROR,
		SET_SENDTIMEOUT_ERROR,
		SET_RECVTIMEOUT_ERROR,

		CONNECT_TIMEOUT,
	};

public:
	SocketClient();
	SocketClient(unsigned int port, const std::string & url);
	~SocketClient();

	bool ConnectWithURL();
	bool ConnectWithIP();
	void Close();

	//before used , you must init this socket
	bool init();

// 	//T must base on class LNMessageBase
// 	template<typename T>
// 	void Send(T &msg);
// 
// 	//T must base on class LNMessageBase
// 	template<typename T>
// 	T Recv();


	bool Send(SocketClientBuffer &src);
	bool Recv(SocketClientBuffer *dest);	

	void SetConnectTimeout(float timeout);
	void SetSendTimeout(float timeout);
	void SetRecvTimeout(float timeout);

	inline void SetHostURL(const std::string & url) { _url = url; }

	inline std::string GetHostURL() { return _url; }

	inline void SetPort(unsigned int port){ _port = port; }

	inline unsigned int GetPort() { return _port; }

	inline bool isConnected() { return _isConnected; }

private:

	bool DNS();

private:
	int _socket_fd;		//socket fd
	int _port;			//port

	bool _isConnected; //flag

	long _connectTimeout;
	long _sendTimeout;
	long _recvTimeout;

	std::string _url;	//host url
	std::string _ip;	//host ip

	ErrorCode _errorCode;

};


// template<typename T>
// void SocketClient::Send(T &msg)
// {
// 	assert(msg.GetType() == "PackageType"); 
// 
// 	if (!isConnected())
// 	{
// 		LOGI("connection is not build yet");
// 		return;
// 	}
// 
// 	int32_t ret = 0;
// 	int32_t n = 0;
// 
// 	char *buf = msg.Serialize();
// 	while (n < msg.length())
// 	{
// 		ret = send(socket_fd_, buf + n, msg.length() - n, 0);
// 		if (ret < 0)
// 		{
// 			//TODO 错误事件分发
// 			delete[] buf;
// 			return;
// 		}
// 		n += ret;
// 	}	
// 	delete[] buf;
// 	
// }
// 
// template<typename T>
// T SocketClient::Recv()
// {
// 	T t;
// 	assert(t.GetType() == "PackageType"); 
// 
// 	if (!isConnected())
// 	{
// 		LOGI("connection is not build yet");
// 		return t;
// 	}
// 
// 	int32_t n = 0, ret = 0, pkgLength = 0;
// 	char buff[4];
// 	char *mallocBuff;
// label:
// 	//获取包头
// 	ret = n = 0;
// 	memset(buff, 0, 4);
// 	while (n < 4)
// 	{
// 		ret = recv(socket_fd_, buff + n, 4 - n, 0);
// 		if (ret < 0)
// 		{
// 			//TODO 添加错误事件分发
// 			return t;
// 		}
// 		n += ret;
// 	}
// 
// 	pkgLength = ntohl(*((int32_t *) buff));	//release
// 	//pkgLength = *((int32_t *) buff);	//debug
// 	mallocBuff = new char[pkgLength + 1];
// 	memset(mallocBuff,'\0', pkgLength + 1);
// 	ret = n = 0;
// 	while(n < pkgLength)
// 	{
// 		ret = recv(socket_fd_, mallocBuff + n, pkgLength - n, 0);
// 		if (ret < 0)
// 		{
// 			//TODO 添加错误事件分发
// 			return t;
// 		}
// 		LOGI("PING");
// 		//printf(mallocBuff);
// 		n += ret;
// 	}	
// 	if (!strcmp(mallocBuff, "PING"))	//回应心跳检测
// 	{
// 		struct _data_ {
// 			int32_t a;
// 			char b[4];
// 		} tmp;
// 		tmp.a = htonl(4);
// 		strncpy(tmp.b, "PONG", 4);
// 		send(socket_fd_, (char *)&tmp, 8, 0);
// 		delete mallocBuff;
// 		goto label;
// 	}
// 
// 	t.Deserialization(mallocBuff, pkgLength);
// 	delete mallocBuff;
// 	mallocBuff = NULL;
// 	return t;
// }


#endif // LN_SOCKET_h_
