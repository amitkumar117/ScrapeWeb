#include "Socket.h"
class Host :
    public Socket
{
    const char* hostname;
    int port;
    addrinfo* addrs;
    SOCKET readSock;
    int resolveHostName();
public:  
    int connect();
    SOCKET getReadSocket();
    int readData(string*);
    ~Host();
    Host(const char* hostname, int port);
};

