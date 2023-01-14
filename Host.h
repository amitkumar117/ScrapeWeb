#include "Socket.h"
class Host :
    public Socket
{
    const char* hostname;
    int port;
    addrinfo* addrs;
    int resolveHostName();
public:  
    int connect();
    ~Host();
    Host(const char* hostname, int port);
};

