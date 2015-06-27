#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h> 
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <thread>
#include <memory>
#include "tcpserver.h"

class Socket{
public:
	Socket(int _sockfd):
		sockfd(_sockfd)
	{printf("Socket\n");}
		
	~Socket(){
		printf("~Socket\n");
		close(sockfd);
	}
	int sockfd;
};

class SocketException: public std::exception{
public:
	SocketException(std::string _reason):
		reason(_reason)
	{}
	const char* what() const noexcept{
		return reason.c_str();
	}
private:
	std::string reason;
};

class ExHandler{
public:
	ExHandler(std::unique_ptr<Socket> _sock): 
		sock(std::move(_sock))
	{}
	void handle(){
		printf("%d\n",sock->sockfd);
		char buffer[256];
		bzero(buffer,256);
		int n = read(sock->sockfd,buffer,255);
		if (n < 0){
			throw SocketException("ERROR reading from socket");
		}
		printf("Here is the message: %s\n",buffer);
		n = write(sock->sockfd,"I got your message",18);
		if (n < 0){
			throw SocketException("ERROR writing to socket");
		}
	}
private:
	std::unique_ptr<Socket> sock;
};



int main(int argc, char *argv[]){
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
	 TCPServer<ExHandler> server(atoi(argv[1]));
	 server.serve();
     return 0; 
}
