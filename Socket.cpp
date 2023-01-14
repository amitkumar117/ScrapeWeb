#include "Socket.h"

using namespace std;

Socket::Socket()
{
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        sockInitialized = false;
    }
    else
    {
        sockInitialized = true;
    }
}
Socket::~Socket()
{
    closeSocketDescriptor();
    if (sockInitialized)
    {
        WSACleanup();
    }
}

int Socket::createSocketDescriptor()
{
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout << "Socket creation error" << endl;
        return QeFailure;
    }
    return QeSuccess;
}

void Socket::closeSocketDescriptor()
{
    if (sockfd >= 0)
    {
        closesocket(sockfd);
    }
}

/*void Socket::setConnectionInfo(addrinfo* addr, int port)
{
    sock.sin_addr = addr->ai_addr;
    sock.sin_port = htons(port);
    sock.sin_family = AF_INET;
}*/

int Socket::connectSocket(addrinfo* addr)
{
    if (connect(sockfd, addr->ai_addr, addr->ai_addrlen) < 0)
    {
        return QeFailure;
    }
    return QeSuccess;
}

int Socket::sendRequest(string request)
{
   return send(sockfd, request.c_str(), request.length(), 0);
}
