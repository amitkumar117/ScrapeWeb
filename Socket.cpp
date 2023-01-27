#include "Socket.h"

using namespace std;

Socket::Socket()
{
    opt = 1;
    port = 80;
    addrlen = sizeof(addr);
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

void Socket::closeSocketDescriptor(SOCKET socket)
{
    if (sockfd >= 0)
    {
        closesocket(sockfd);
        sockfd = 0;
    }

    if (socket >= 0)
    {
        closesocket(socket);
        socket = 0;
    }
}

void Socket::setConnectionInfo()
{
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);
}

int Socket::connectSocket(addrinfo* addr)
{
    if (connect(sockfd, addr->ai_addr, addr->ai_addrlen) < 0)
    {
        return QeFailure;
    }
    return QeSuccess;
}

int Socket::sendData(string request, SOCKET socket)
{
   return send((socket == 0 ? sockfd : socket), request.c_str(), request.length(), 0);
}

void Socket::setSockOptions()
{
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt))) 
    {
        cout << "Error setting socket option" << endl;
    }
}

int Socket::setListener(SOCKET *readSock)
{
    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        cout << "Error binding socket";
        return QeFailure;
    }

    if (listen(sockfd, 3) < 0)
    {
        cout << "Error setting listen on socket";
        return QeFailure;
    }

   SOCKET readSocket = accept(sockfd, (sockaddr*)&addr, (socklen_t*)&addrlen);
   if (readSocket == INVALID_SOCKET)
   {
       cout << "accept failed";
       return QeFailure;
   }
   *readSock = readSocket;
   return QeSuccess;

}

void Socket::setPort(int port)
{
    this->port = port;
}