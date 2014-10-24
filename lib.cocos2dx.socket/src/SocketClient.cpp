#include "SocketClient.h"
#include <assert.h>
#include <fcntl.h>
#ifdef ANDROID
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#endif // _WIN32

SocketClient::SocketClient() : 
	_socket_fd(-1), 
	_port(-1), 
	_url(""),
	_ip(""),
	_isConnected(false),
	_errorCode(ErrorCode::NORMAL)
{
	
}

SocketClient::SocketClient(unsigned int port,const std::string & url) : 
	_socket_fd(-1), 
	_port(-1), 
	_url(url),
	_ip(""),
	_isConnected(false),
	_errorCode(ErrorCode::NORMAL)
{

}

SocketClient::~SocketClient()
{
#ifdef _WIN32
	WSACleanup();
#endif // _WIN32

}


bool SocketClient::init()
{
#ifdef _WIN32
	WSADATA inet_WsaData;
	WSAStartup(MAKEWORD(2, 0), &inet_WsaData);

	if (LOBYTE(inet_WsaData.wVersion) != 2 || HIBYTE(inet_WsaData.wVersion) != 0)
	{
		LOGI("WSAStartup error:%d "  , WSAGetLastError() );
		return false;
	}
#endif // _WIN32

	_socket_fd = socket(AF_INET, SOCK_STREAM, 0);	//阻塞socket， tcp	
	if (_socket_fd == INVALID_SOCKET)
	{
		LOGI("create socket fd error");
		_errorCode = CREATE_SOCKET_FAILED;		
		_isConnected = false;
		return false;
	}	
	
	return true;
}

bool SocketClient::DNS()
{
	assert(!_url.empty() && _url.length() > 0);
	struct hostent *hostInfo = gethostbyname(_url.c_str());
	if (hostInfo == NULL)
	{
		_errorCode = ErrorCode::DNS_FAILED;
		return false;
	}
	_ip = std::string(inet_ntoa(* (in_addr *)hostInfo->h_addr_list[0]));
	return true;
}

bool SocketClient::ConnectWithURL()
{
	_isConnected = false;
	if (DNS())
		return ConnectWithIP();
	else
		return false;
}

bool SocketClient::ConnectWithIP()
{
	if (_socket_fd == INVALID_SOCKET)
	{
		_isConnected = false;
		return _isConnected;
	}

	LOGI (__FUNCTION__);
	assert(_port >= 0 && !_ip.empty());
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(_port);
	addr.sin_addr.s_addr = inet_addr(_ip.c_str());

#if defined(_WIN32)
	unsigned long mode = 1;	// 0 - 阻塞模式; 非0 - 为非阻塞模式
	if(ioctlsocket(_socket_fd, FIONBIO, &mode) == SOCKET_ERROR)	// 设置非阻塞socket
	{
		_errorCode = ErrorCode::SET_NOBLOCK_ERROR;
		return false;
	}
#elif defined(ANDROID)
	int flag = fcntl(_socket_fd, F_GETFL, 0);
	if (flag == SOCKET_ERROR)
	{
		_errorCode = ErrorCode::SET_NOBLOCK_ERROR;
		return false;
	}
	flag |= O_NONBLOCK;
	if (fcntl(_socket_fd, F_SETFL, flag) == SOCKET_ERROR)	// 设置非阻塞socket
	{
		_errorCode = ErrorCode::SET_NOBLOCK_ERROR;
		return false;
	}
#endif
	struct timeval sendTimeout, recvTimeout;	
	sendTimeout.tv_sec = _sendTimeout; sendTimeout.tv_usec = 0;
	recvTimeout.tv_sec = _recvTimeout; recvTimeout.tv_usec = 0;

	if (setsockopt(_socket_fd, SOL_SOCKET, SO_SNDTIMEO, (const char *)&sendTimeout, sizeof(sendTimeout)) == SOCKET_ERROR)	//设置发送超时
	{
		_errorCode = ErrorCode::SET_SENDTIMEOUT_ERROR;
		return false;
	}
	if (setsockopt(_socket_fd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&recvTimeout, sizeof(recvTimeout)) == 0)	//设置发送超时
	{
		_errorCode = ErrorCode::SET_RECVTIMEOUT_ERROR;
		return false;
	}		

	struct timeval connTimeout;
	connTimeout.tv_sec = _connectTimeout;
	connTimeout.tv_usec = 0;
	fd_set rset;
	fd_set wset;

	FD_ZERO(&rset);
	FD_ZERO(&wset);
	FD_SET(_socket_fd, &rset);
	FD_SET(_socket_fd, &wset);

	if (connect(_socket_fd, (sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		if (errno != EINPROGRESS)	// connect返回-1且errno == EINPROGRESS - 正在连接中，否则为出错
		{
			_errorCode = CONNECT_FAILED;
			_isConnected = false;
			return;
		}
		switch (select(_socket_fd + 1, &rset, &wset, NULL, &connTimeout))
		{
		case -1:	// select出错
			_errorCode = ErrorCode::SELETE_ERROR;
			return false;
		case 0:		// timeout
			_errorCode = ErrorCode::CONNECT_TIMEOUT;
			return false;
			case 

		} 
		_isConnected = false;		
	}
	else
	{
		_isConnected = true;
	}
	return _isConnected;
}


void SocketClient::Close()
{
	if (_socket_fd != -1)
#ifdef _WIN32
		closesocket(_socket_fd);
#endif // _WIN32
#ifdef ANDROID
		close(_socket_fd);
#endif // ANDROID

}

void SocketClient::SetConnectTimeout(float timeout)
{
	_connectTimeout = timeout;
}

void SocketClient::SetSendTimeout(float timeout)
{
	_sendTimeout = timeout;
}

void SocketClient::SetRecvTimeout(float timeout)
{
	_recvTimeout = timeout;
}

