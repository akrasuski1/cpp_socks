#ifndef SOCKET_INCLUDED
#define SOCKET_INCLUDED

#include <istream>
#include <ostream>
#include <ext/stdio_filebuf.h>

class Socket{
public:
	Socket(int _sockfd);
	~Socket();

	std::istream is;
	std::ostream os;
private:
	int sockfd;
	__gnu_cxx::stdio_filebuf<char> filebufi, filebufo;
};

#endif
