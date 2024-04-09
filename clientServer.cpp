#pragma once
#include "clientServer.h"
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
int ClientServer::CreateSocket() {
	Sleep(5);
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		std::cerr << "����ʧ��" << std::endl;
		return -1;
	}
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(8080);
	inet_pton(AF_INET, "127.0.0.1", &(serverAddress.sin_addr));
	// ���ӵ����������ڶ����Ǵ��������
	if (connect(sockfd, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
		std::cerr << "Failed to connect to server\n";
		closesocket(sockfd);
		return 1;
	}
	// �������ݵ�������
	const char* message = "Hello, server!";
	if (send(sockfd, message, strlen(message), 0) == -1) {
		std::cerr << "Failed to send data\n";
		closesocket(sockfd);
		return 1;
	}
	// ���շ��������͵�����
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	if (recv(sockfd, buffer, sizeof(buffer) - 1, 0) == -1) {
		std::cerr << "Failed to receive data\n";
		closesocket(sockfd);
		return 1;
	}

	std::cout << "Received from server: " << buffer << "\n";

	// �ر��׽���
	closesocket(sockfd);
	return 1;
}