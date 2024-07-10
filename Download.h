#pragma once
#include <iostream>
#include <Windows.h>
#include <winhttp.h>
#include <websocket.h>
#include <fstream>
#include <string>
#pragma comment(lib, "winhttp.lib")
#pragma comment(lib, "websocket.lib")
class Download
{
public:
	int GetFileContent(LPCWSTR url, INTERNET_PORT port);
	void SetDownName(std::string name);
private:
	std::string downName;
};

