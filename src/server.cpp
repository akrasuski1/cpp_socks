#include <unistd.h>
#include "tcpserver.h"
#include "socket.h"


class ExHandler{
public:
	ExHandler(std::unique_ptr<Socket> _sock): 
		sock(std::move(_sock))
	{}
	void handle(){
		char buffer[256];
		*sock>>buffer;
		printf("Here is the message: %s\n",buffer);
		*sock<<"I got this";
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
