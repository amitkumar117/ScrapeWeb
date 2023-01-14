#include"Host.h"
#include"CurlConnection.h"
using namespace std;

int main()
{
	string request2 = "GET /websiteos/example_of_a_simple_html_page.htm HTTP/1.1\r\n\
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\n\
Accept-Encoding: gzip, deflate\r\n\
Accept-Language: en-US,en;q=0.9\r\n\
Cache-Control: max-age=0\r\n\
Connection: keep-alive\r\n\
Referer: https://www.yahoo.com/\r\n\
Upgrade-Insecure-Requests: 1\r\n\
User-Agent: PostmanRuntime/7.30.0\r\n\
Postman-Token: 76e74e77-4fab-4876-9fb3-0308f2486246c\r\n\
Host: help.websiteos.com\r\n\r\n";

	string request = "GET / HTTP/1.1\r\n\
Host: time.com\r\n\
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\r\n\
Accept-Encoding: gzip, deflate\r\n\
Accept-Language: en-US,en;q=0.9\r\n\r\n";

	/*Host url("time.com", 441);
	if (url.connect() == QeSuccess)
	{
		cout << "Connection successful \n";
		if (url.sendRequest(request) != request.length())
		{
			cout << "Error Sending Request \n";
		}
	}
	else
	{
		cout << "Connection failure \n";
	}*/

	string url = "https://time.com";
	CurlConnection curlConnection;
	curlConnection.setUrl(url);
	if (curlConnection.curlConnect() == QeSuccess)
	{
		FILE* fptr;
		fopen_s(&fptr,"C:\\Users\\jaina\\OneDrive\\Documents\\VS_Apps\\ScrapeWeb\\x64\\Debug\\log.txt","w");
		string response = curlConnection.getResponse();
		if (fptr)
		{
			fprintf(fptr, "%s", response.c_str());
			fclose(fptr);
		}
	}
	cout << "Done \n";
	return 0;
}
