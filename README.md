# ScrapeWeb
Application to read most viewed storied from a Time.com and provide results running as a service.

To run directly :
1. Download ScrapeWeb.exe, vcruntime140_1d.dll, libcurl-x64.dll and place in a folder or add the dlls to path for the exe to find them.
2. run ScrapeWeb.exe without any arguments for the service to start.
3. Open Browser or Postman and run the http GET call "localhost/getTimeStories" or "http://127.0.0.1/getTimeStories" to get the Most Read stories links and Titles as response.

To Build :
1. Download all .cpp and .h files.
2. To build using VS on windows, download ScrapeWeb.vcxproj, ScrapeWeb.sln files and edit the project and sln files to point the correct path of .cpp and .h files.
3. Download libcurl.dll.a static library file and add it to the solution file to link it to the executable beimg built.
4. Build and generate ScrapeWeb.exe exucutable (port number to run service on can be modified in main() in ScrapeWeb.cpp) and follow the steps provided in the above section to get the output.
5. If not using VS to build ... just download *.cpp, *.h and libcurl.dll.a files.
   Build all .cpp files and generate object files. Link all object files generated and libcurl.dll.a static library to generate ScrapeWeb.exe executable.
