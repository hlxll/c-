#pragma once
#include "clientServer.h"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
int ClientServer::CreateSocket() {
	Sleep(5);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		std::cerr << "创建失败" << std::endl;
		return -1;
	}
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);
	inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr));
	// 连接到服务器，第二个是传入参数，
	if (connect(sockfd, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
		std::cerr << "Failed to connect to server\n";
		closesocket(sockfd);
		return 1;
	}
	// 发送数据到服务器
	const char* message = "Hello, server!";
	if (send(sockfd, message, strlen(message), 0) == -1) {
		std::cerr << "Failed to send data\n";
		closesocket(sockfd);
		return 1;
	}
	// 接收服务器发送的数据
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	if (recv(sockfd, buffer, sizeof(buffer) - 1, 0) == -1) {
		std::cerr << "Failed to receive data\n";
		closesocket(sockfd);
		return 1;
	}

	std::cout << "Received from server: " << buffer << "\n";

	// 关闭套接字
	closesocket(sockfd);
	return 1;
}