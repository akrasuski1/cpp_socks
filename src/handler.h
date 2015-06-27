#ifndef HANDLER_INCLUDED
#define HANDLER_INCLUDED

#include <istream>
#include <ostream>
#include <memory>
#include "socket.h"

class Handler{
public:
	Handler(std::unique_ptr<Socket> _sock);
	virtual void handle()=0;
protected:
	void set_timeout(double timeout);
	std::ostream& out;
	std::istream& in;
private:
	std::unique_ptr<Socket> sock;
};

#endif
