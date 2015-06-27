#include <unistd.h>
#include "socket.h"

Socket::Socket(int _sockfd):
	sockfd(_sockfd)
{}
Socket::~Socket(){
	close(sockfd);
}
