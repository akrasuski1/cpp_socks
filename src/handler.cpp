#include "handler.h"

Handler::Handler(std::unique_ptr<Socket> _sock, std::string ip, int _port): 
	out(_sock->os),
	in(_sock->is),
	sock(std::move(_sock)),
	ip_address(ip),
	port(_port)
{}
void Handler::set_timeout(double timeout){
	sock->set_timeout(timeout);
}
