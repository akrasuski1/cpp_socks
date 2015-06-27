#include <unistd.h>
#include "tcpserver.h"
#include "socket.h"


class ExHandler{
public:
	ExHandler(std::unique_ptr<Socket> _sock): 
		out(_sock->os),
		in(_sock->is),
		sock(std::move(_sock))
	{}
	void handle(){
		out<<"Hello"<<std::endl;
		int a,b;
		in>>a>>b;
		out<<"I got this"<<a<<b<<std::endl;
		std::string str;
		getline(in,str);
		getline(in,str);
		out<<str<<std::endl;
	}
private:
	std::ostream& out;
	std::istream& in;
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
