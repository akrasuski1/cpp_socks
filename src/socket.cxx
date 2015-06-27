#include <unistd.h>
#include <cstdio>
#include <ext/stdio_filebuf.h>
#include "socket.h"

Socket::Socket(int _sockfd):
	sockfd(_sockfd),
	filebuf(_sockfd,std::ios::in|std::ios::out),
	io(&filebuf)
{}
Socket::~Socket(){
	close(sockfd);
}

template <typename T>
Socket& Socket::operator<<(T& input){
	io<<input;
	return *this;
}
template <typename T>
Socket& Socket::operator>>(T& output){
	io>>output;
	return *this;
}
