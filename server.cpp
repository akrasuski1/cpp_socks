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

template <class Handler>
class TCPServer{
public:
	TCPServer(int _port):
		port(_port)
	{}
	void serve(){
		int sockfd, newsockfd, portno, clilen;
		struct sockaddr_in serv_addr, cli_addr;
		sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if(sockfd < 0){
			throw SocketException("Could not create socket");
		}
		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(port);
		int yes=1;
		setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
		if(bind(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
			throw SocketException("Error on binding");
		}
		listen(sockfd,10);
		clilen = sizeof(cli_addr);

		while(true){
			newsockfd = accept(sockfd, (sockaddr*)&cli_addr, (socklen_t*)&clilen);
			if (newsockfd < 0){
				throw SocketException("Error on accept");
			}
			
			std::thread([&]{
				Handler handler(std::make_unique<Socket>(newsockfd));
				handler.handle();
			}).detach();
		}
	}
private:
	int port;
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
