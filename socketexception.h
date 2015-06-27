#ifndef SOCKETEXCEPTION_INCLUDED
#define SOCKETEXCEPTION_INCLUDED

#include <string>

class SocketException: public std::exception{
public:
	SocketException(std::string _reason);
	const char* what() const noexcept;
private:
	std::string reason;
};

#endif
