#include <unistd.h>
#include "tcpserver.h"
#include "socket.h"


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
