#include <iostream>
#include "tcpserver.h"

class ExHandler: public Handler{
public:
	using Handler::Handler;
	void handle(){
		std::cout<<"Connected to: "<<ip_address<<" at port "<<port<<std::endl;
		set_timeout(30.0);
		out<<"Hello there! Type two integers now."<<std::endl;
		int a,b;
		in>>a>>b;
		out<<"Thanks. Here is their sum: "<<a+b<<std::endl;
		out<<"Now I'll just echo your line of text."<<std::endl;
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
