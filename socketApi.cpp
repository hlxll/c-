#pragma once
#include "socketApi.h"
#include <iostream>
#include <winsock2.h>

#include <ws2tcpip.h>
#include <thread>
#include "yunRenderCV.h"
//#pragma comment(lib, "ws2_32.lib")
int SocketApi::createSocket() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "初始化 Winsock 失败" << std::endl;
		return -1;
	}
	// 创建套接字,用于监听
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET) {
		std::cerr << "创建套接字失败，错误代码: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}

	//绑定IP和port
	sockaddr_in serverAddress{};
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(8810);
	if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
		std::cerr << "绑定错误" << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}

	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << "监听失败" << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}

	std::cout << "服务器已启动，等待客户端连接..." << std::endl;

	// 接受客户端连接,最大128个连接
	sockaddr_in clientAddress{};//保存连接的客户端的信息
	int clientAddressLength = sizeof(clientAddress);
	//返回值是用于通信的文件描述符，如果没有客户端连接，accept是阻塞的。如果要同时建立多个连接，要执行多次accept，第二个是传出参数
	SOCKET clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress),
		&clientAddressLength);
	
	if (clientSocket == INVALID_SOCKET) {
		std::cerr << "接受客户端连接失败，错误代码: " << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}
	else {
		std::cout << "已连接客户端的端口：" << clientAddress.sin_port << std::endl;
	}

	const char* corsHeader = "Access-Control-Allow-Origin: *\r\n";
	send(clientSocket, corsHeader, strlen(corsHeader), 0);
	std::cout << "已接受客户端连接" << std::endl;

	

	// 发送和接收数据
	char buffer[1024];
	int bytesRead;//返回值大于0是实际接收到的数据字节数，等于0是对方断开连接，-1是接收数据失败
	while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
		// 获取 WebSocket Key
		//std::string key;
		//const std::string requestHeader(buffer);
		//size_t keyStart = requestHeader.find("Sec-WebSocket-Key:") + 19;
		//size_t keyEnd = requestHeader.find("\r\n", keyStart);
		//if (keyStart != std::string::npos && keyEnd != std::string::npos) {
		//	key = requestHeader.substr(keyStart, keyEnd - keyStart);
		//}

		//// 构建 WebSocket 握手响应
		//std::string response = "HTTP/1.1 101 Switching Protocols\r\n";
		//response += "Upgrade: websocket\r\n";
		//response += "Connection: Upgrade\r\n";
		//response += "Sec-WebSocket-Accept: " + key + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11" + "\r\n\r\n";

		//// 发送握手响应
		//if (send(clientSocket, response.c_str(), response.length(), 0) == -1) {
		//	std::cerr << "发送握手响应失败" << std::endl;
		//	closesocket(clientSocket);
		//	continue;
		//}

		// 处理接收到的数据
		std::cout << "接收到的数据：" << buffer << std::endl;

		// 发送回复，send返回值大于0是实际发送字节数，-1发送失败
		const char* str = "Hello from server!";
		send(clientSocket, str, strlen(str), 0);
	}
	if (bytesRead == 0) {
		std::cout << "客户端断开连接" << std::endl;
	}
	else if (bytesRead == SOCKET_ERROR) {
		std::cerr << "接收数据失败，错误代码: " << WSAGetLastError() << std::endl;
	}

	// 关闭套接字
	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
	return 0;
}

//添加响应头
std::string postHTTPHead(std::string imageStr) {
	std::string response = "HTTP/1.1 200 OK\r\n";
	//response += "Method: GET\r\n";
	response += "Content-Type: text/plain\r\n";
	response += "Content-Length: " + std::to_string(imageStr.size()) + "\r\n";
	response += "Connection: close\r\n";
	response += "\r\n";
	std::string fullResponse = response + imageStr;
	return fullResponse;
}


std::string getHTTPHead() {
	return "";
}
int threadWork(SOCKET clientSocket) {
	std::cout << "已接受客户端连接" << std::endl;
	char buffer[1024] = "\n";
	int bytesRead;



	while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
		std::cout << "接收到的数据：" << buffer << std::endl;


		HWND desktopWnd = GetDesktopWindow();
		YunRenderCV yunRender;
		std::string imageStr = yunRender.getWindow(desktopWnd);

		// 合并响应头和数据
		std::string fullResponse = postHTTPHead(imageStr);
		int sentBytes = send(clientSocket, fullResponse.c_str(), fullResponse.length(), 0);
	}

	if (bytesRead == 0) {
		std::cout << "客户端断开连接" << std::endl;
	}
	else if (bytesRead == SOCKET_ERROR) {
		std::cerr << "接收数据失败，错误代码: " << WSAGetLastError() << std::endl;
	}
	// 关闭套接字
	closesocket(clientSocket);
	return -1;
}

void working(SOCKET socketServer) {
	while (true) {
		std::cout << "服务器已启动，等待客户端连接..." << std::endl;
		sockaddr_in clientAddress{};//保存连接的客户端的信息
		int clientAddressLength = sizeof(clientAddress);
		SOCKET clientSocket = accept(socketServer, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength);
		if (clientSocket == INVALID_SOCKET) {
			std::cerr << "接受客户端连接失败，错误代码: " << WSAGetLastError() << std::endl;
			break;
		}
		std::thread t(threadWork, clientSocket);
		t.detach();// 分离线程，使其在后台运行
	}
}
//单线程执行socket，在accept连接，recv读取，send写入这几个地方，如果没有响应就会阻塞,创建的普通XHR连接，不是ws
int SocketApi::createThreadSocket() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "初始化 Winsock 失败" << std::endl;
		return -1;
	}
	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, 0);
	if (socketServer == INVALID_SOCKET) {
		std::cerr << "创建套接字失败" << std::endl;
		return -1;
	}
	sockaddr_in serverAddress{};
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(8810);
	if (bind(socketServer, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
		std::cerr << "绑定错误" << WSAGetLastError() << std::endl;
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}
	if (listen(socketServer, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << "监听失败" << WSAGetLastError() << std::endl;
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}
	working(socketServer);
	
	WSACleanup();
	closesocket(socketServer);
	return -1;
}


