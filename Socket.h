#pragma once
#include"Header.h"

using namespace std;
class Socket
{
	WSADATA wsa;
	bool sockInitialized;
	SOCKET sockfd;
	sockaddr_in sock;
	//void setConnectionInfo(in_addr ip, int port);
protected:
	int createSocketDescriptor();
	void closeSocketDescriptor();
	int connectSocket(addrinfo* addr);
public:
	int sendRequest(string request);
	Socket();
	~Socket();
};
