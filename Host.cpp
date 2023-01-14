#include"Host.h"

using namespace std;

Host::Host(const char* hostname, int port)
{
    this->hostname = hostname;
    this->port = port;
}

int Host::resolveHostName()
{
    addrinfo hints = {};
    int err;
    char port_str[16] = {};

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    sprintf_s(port_str, "%d", port);

    err = getaddrinfo(hostname, port_str, &hints, &addrs);
    if (err != 0)
    {
        printf("%s: %ls\n", hostname, gai_strerror(err));
        return QeFailure;
    }

    return QeSuccess;
}

Host::~Host()
{
    if (addrs)
    {
        freeaddrinfo(addrs);
    }
}

int Host::connect()
{
    if (resolveHostName() != QeSuccess)
    {
        cout << "Cannot resolve host name" << endl;
        return QeFailure;
    }
    for (addrinfo* addr = addrs; addr != NULL; addr = addr->ai_next)
    {
        if (createSocketDescriptor() != QeSuccess)
        {
            cout << "Error in socket descriptor creation" << endl;
            return QeFailure;
        }
        if (connectSocket(addr) == QeSuccess)
        {
            cout << "Connection Successful" << endl;
            return QeSuccess;
        }
        closeSocketDescriptor();
    }
    return QeFailure;
}