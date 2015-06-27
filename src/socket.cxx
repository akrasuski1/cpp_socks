#include <unistd.h>
#include "socket.h"

Socket::Socket(int _sockfd):
	sockfd(_sockfd)
{}
Socket::~Socket(){
	close(sockfd);
}

template <typename T>
Socket& Socket::operator<<(T input){
	ss.str("");
	ss.clear();
	ss<<input;
	std::string str=ss.str();
	while(str.size()){
		int n=write(sockfd, str.c_str(), str.size());
		if(n<0){
			throw SocketException("Error writing to socket");
		}
		str=str.substr(n);
	}
	return *this;
}
template <typename T>
Socket& Socket::operator>>(T& output){
	int i=0;
	while(i<buffer.size()&& 
			(buffer[i]==' ' || buffer[i]=='\t' || buffer[i]=='\n')){
		i++;
	}
	buffer=buffer.substr(i);
	while(buffer.find(' ')==std::string::npos 
		&& buffer.find('\n')==std::string::npos 
		&& buffer.find('\t')==std::string::npos){
		readsome();
		int i=0;
		while(i<buffer.size()&& 
				(buffer[i]==' ' || buffer[i]=='\t' || buffer[i]=='\n')){
			i++;
		}
		buffer=buffer.substr(i);
	}
	std::string word;
	ss.str("");
	ss.clear();
	ss<<buffer;
	ss>>word;
	buffer=ss.str().substr(word.size());
	ss.str(word);
	ss.clear();
	ss>>output;
	return *this;
}

void Socket::readsome(){
	char buff[256]={0};
	int n=read(sockfd, buff, 255);
	if(n<0){
		throw SocketException("Error reading from socket");
	}
	buffer=buffer+buff;
}
