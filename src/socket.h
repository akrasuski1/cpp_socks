#ifndef SOCKET_INCLUDED
#define SOCKET_INCLUDED

#include <sstream>
#include <iostream>
#include <ext/stdio_filebuf.h>
#include "socketexception.h"

class Socket{
public:
	Socket(int _sockfd);
	~Socket();
	template <typename T>
	Socket& operator<<(T& input);
	template <typename T>
	Socket& operator>>(T& output);

private:
	int sockfd;
	void readsome();

	__gnu_cxx::stdio_filebuf<char> filebuf;
	std::iostream io;
	std::stringstream ss;
};

#include "socket.cxx"

#endif
