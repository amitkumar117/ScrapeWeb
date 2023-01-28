#include"Host.h"
#include"CurlConnection.h"
using namespace std;

void parseFeed(string response, stories* story)
{
	size_t end = 0;
	size_t pos = 0;
	bool isFirst = true;
	while (true)
	{
		pos = response.find("most-popular-feed__item-section", pos);
		if (pos != string::npos)
		{
			if (isFirst)
			{
				isFirst = false;
			}
			else
			{
				story->next = new stories;
				story = story->next;
			}
			pos = response.find("<a href=", pos);
			if (pos != string::npos)
			{
				pos = pos + 9;
				end = response.find("\"", pos);
				if (end != string::npos)
				{
					story->url = response.substr(pos, end - pos);
					pos = end;
					pos = response.find("most-popular-feed__item-headline", pos);
					if (pos != string::npos)
					{
						pos = response.find("\">", pos);
						if (pos != string::npos)
						{
							pos = pos + 2;
							end = response.find("</", pos);
							if (end != string::npos)
							{
								story->headline = response.substr(pos, end - pos);
								pos = end;
							}
						}
					}
				}
			}
		}
		else
		{
			break;
		}
	}
}

string formJSONResponse(stories *story)
{
	string response;
	bool isFirst = true;
	response.append("[");
	while (story != NULL)
	{
		if (isFirst)
		{
			response.append("\r\n");
			isFirst = false;
		}
		else
		{
			response.append(",\r\n");
		}
		response.append("\t{\r\n");
		response.append("\t\t\"title\":\"");
		response.append(story->headline);
		response.append("\",\r\n");
		response.append("\t\t\"link\":\"");
		response.append(story->url);
		response.append("\"\r\n");
		response.append("\t}");
		story = story->next;
	}
	response.append("\r\n]");
	return response;
}

int main()
{
	Host host("localhost", 80);
	while (true)
	{
		string httpResponse = "HTTP/1.1 200 OK\r\n\
Content-Type: application/json; charset=utf-8\r\n\
Connection: keep-alive\r\n";
		string request;
		host.readData(&request);
		if (request.starts_with("GET /getTimeStories"))
		{
			string url = "https://time.com";
			CurlConnection curlConnection;
			curlConnection.setUrl(url);
			if (curlConnection.curlConnect() == QeSuccess)
			{
				string response = curlConnection.getResponse();
				stories* story = new stories;
				parseFeed(response, story);
				string result = formJSONResponse(story);
				httpResponse.append("Content-Length: ");
				char buff[16] = { 0 };
				sprintf_s(buff, "%d", result.length());
				httpResponse.append(buff);
				httpResponse.append("\r\n\r\n");
				httpResponse.append(result.c_str());
				httpResponse.append("\r\n");
			}
			else
			{
				httpResponse.append("Content-Length: 29\r\n\r\n");
				httpResponse.append("Can't connect to URL provided\r\n");
			}
		}
		else
		{
			httpResponse.append("Content-Length: 11\r\n\r\n");
			httpResponse.append("Bad Request\r\n");
		}
		host.sendData(httpResponse, host.getReadSocket());
	}
	cout << "Done";
	return 0;
}
