#include <unistd.h>
#include <cstdio>
#include <ext/stdio_filebuf.h>
#include "socket.h"

Socket::Socket(int _sockfd):
	sockfd(_sockfd),
	filebufi(_sockfd,std::ios::in),
	filebufo(_sockfd,std::ios::out),
	is(&filebufi),
	os(&filebufo)
{}
Socket::~Socket(){
	close(sockfd);
}
