#pragma once
#include"Header.h"

using namespace std;
class Socket
{
	WSADATA wsa;
	bool sockInitialized;
	SOCKET sockfd;
	int port;
	sockaddr_in sock;
	int opt;
	int addrlen;
	sockaddr_in addr;
protected:
	void setConnectionInfo();
	void setSockOptions();
	int createSocketDescriptor();
	void closeSocketDescriptor(SOCKET socket = 0);
	int connectSocket(addrinfo* addr);
	int setListener(SOCKET*);
	void setPort(int);
public:
	int sendData(string request, SOCKET socket=0);
	Socket();
	~Socket();
};
