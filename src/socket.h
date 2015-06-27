#ifndef SOCKET_INCLUDED
#define SOCKET_INCLUDED

#include "socketexception.h"

class Socket{
public:
	Socket(int _sockfd);
	~Socket();
	int sockfd;
};

#endif
