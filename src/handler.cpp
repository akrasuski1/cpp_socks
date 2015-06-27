#include "handler.h"

Handler::Handler(std::unique_ptr<Socket> _sock): 
	out(_sock->os),
	in(_sock->is),
	sock(std::move(_sock))
{}
void Handler::set_timeout(double timeout){
	sock->set_timeout(timeout);
}
