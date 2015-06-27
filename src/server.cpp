#include "tcpserver.h"

class ExHandler: public Handler{
public:
	using Handler::Handler;
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
