#pragma once
#include "Header.h"

using namespace std;

struct MemoryStruct
{
	char* memory;
	size_t size;
};

class CurlConnection
{
	CURL* curl_handle;
	CURLcode res;
	MemoryStruct chunk;
	string url;
	string agent;
	static size_t WriteCallback(char*, size_t, size_t, void*);
	int curlSetup();
public:
	CurlConnection();
	int curlConnect();
	void setUrl(string url);
	void setAgent(string agent);
	string getResponse();
	~CurlConnection();
};

