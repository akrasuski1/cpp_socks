#ifndef SOCKET_INCLUDED
#define SOCKET_INCLUDED

#include <sstream>
#include "socketexception.h"

class Socket{
public:
	Socket(int _sockfd);
	~Socket();
	template <typename T>
	Socket& operator<<(T input);
	template <typename T>
	Socket& operator>>(T& output);

private:
	int sockfd;
	void readsome();
	std::string buffer;
	std::stringstream ss;
};

#include "socket.cxx"

#endif
