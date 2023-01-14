#include "CurlConnection.h"

CurlConnection::CurlConnection()
{
	url = "www.test.com";
	agent = "libcurl-agent/1.0";
	chunk.memory = (char*)malloc(1);
	chunk.size = 0;
	if (curl_global_init(CURL_GLOBAL_ALL) == CURLE_OK)
	{
		curl_handle = curl_easy_init();
	}
	else
	{
		curl_handle = NULL;
	}
}

int CurlConnection::curlSetup()
{
	if (curl_handle)
	{
		if (curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str()) != CURLE_OK)
		{
			cout << "setting CURLOPT_URL failed\n";
		}
		if (curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, false) != CURLE_OK)
		{
			cout << "setting CURLOPT_SSL_VERIFYPEER failed";
		}
		//if (curl_easy_setopt(curl_handle, CURLOPT_SSLCERT, "C:\\Users\\jaina\\Downloads\\cacert.pem") != CURLE_OK)
		//{
		//	cout << "setting CURLOPT_SSLCERT failed\n";
		//}
		if (curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteCallback) != CURLE_OK)
		{
			cout << "setting CURLOPT_WRITEFUNCTION failed\n";
		}
		if (curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk) != CURLE_OK)
		{
			cout << "setting CURLOPT_WRITEDATA failed\n";
		}
		if (curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, agent.c_str()) != CURLE_OK)
		{
			cout << "setting CURLOPT_USERAGENT failed\n";
		}
		return QeSuccess;
	}
	else
	{
		cout << "curl_handle not initialized\n";
		return QeFailure;
	}
}

int CurlConnection::curlConnect()
{
	if (curlSetup() != QeFailure)
	{
		res = curl_easy_perform(curl_handle);
		if (res != CURLE_OK)
		{
			cout << "curl_easy_perform failed : " << curl_easy_strerror(res) << endl;
			return QeFailure;
		}
		else
		{
			cout << "Connection successful ... Data Fetched\n";
			return QeSuccess;
		}
	}
	else
	{
		return QeFailure;
	}
}

size_t CurlConnection::WriteCallback(char* contents, size_t size, size_t count, void* buffer)
{
	size_t realsize = size * count;
	MemoryStruct* mem = (MemoryStruct*)buffer;
	char* ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);
	if (!ptr)
	{
		cout << "Failed to allocate sufficient memory to store data\n";
		return 0;
	}
	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

void CurlConnection::setUrl(string url)
{
	this->url = url;
}

void CurlConnection::setAgent(string agent)
{
	this->agent = agent;
}

string CurlConnection::getResponse()
{
	return (string)chunk.memory;
}

CurlConnection::~CurlConnection()
{
	if (curl_handle)
	{
		curl_easy_cleanup(curl_handle);
	}
	free(chunk.memory);
	curl_global_cleanup();
}
