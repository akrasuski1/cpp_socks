#include "socketexception.h"

SocketException::SocketException(std::string _reason):
	reason(_reason)
{}
const char* SocketException::what() const noexcept{
	return reason.c_str();
}
