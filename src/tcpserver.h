#ifndef TCPSERVER_INCLUDED
#define TCPSERVER_INCLUDED

#include "handler.h"

template <class Handler>
class TCPServer{
public:
	TCPServer(int _port);
	void serve();
private:
	int port;
};

#include "tcpserver.cxx"

#endif
