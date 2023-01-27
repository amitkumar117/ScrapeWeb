#pragma once
#include<iostream>
#include<Winsock2.h>
#include<ws2tcpip.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <curl/curl.h>

#pragma comment(lib, "Ws2_32.lib")

#define CURL_STATICLIB
#define QeSuccess 0
#define QeFailure -1
#define REQUEST_SIZE 1024

struct stories
{
	std::string url = "";
	std::string headline = "";
	stories* next = NULL;
};

void parseFeed(std::string, stories*);
std::string formJSONResponse(stories* story);
