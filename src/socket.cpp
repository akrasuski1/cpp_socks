#include <unistd.h>
#include <algorithm>
#include <sys/socket.h>
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
void Socket::set_timeout(double timeout){
	timeout=std::min(std::max(timeout,0.0),3600.0);
	timeval tv;
	tv.tv_sec=floor(timeout);
	timeout-=tv.tv_sec;
	timeout*=1000000;
	tv.tv_usec=floor(timeout);

	setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (timeval*)&tv, sizeof(tv));
}
