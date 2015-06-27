#include <cstring>
#include <netinet/in.h>
#include <thread>
#include <memory>
#include "socket.h"

template <typename Handler> TCPServer<Handler>::TCPServer (int _port):
	port(_port)
{}
template <typename Handler> void TCPServer<Handler>::serve(){
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
