#ifndef SOCKETCONFIG_H_
#define SOCKETCONFIG_H_

#if defined(_WIN32) 
#define LOGI(format, ...) printf(format, __VA_ARGS__); \
						  printf("\n");
#elif defined(ANDROID)
#define  LOG_TAG    "lib.net"  
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__) 

#define INVALID_SOCKET	(-1)
#define SOCKET_ERROR	(-1)
#endif

#define SOCKBUF_DEFAULT_SIZE	1024
#define SOCKBUF_MAX_SIZE	8184

#endif // SOCKETCONFIG_H_
