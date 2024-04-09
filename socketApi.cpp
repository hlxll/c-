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
		std::cerr << "��ʼ�� Winsock ʧ��" << std::endl;
		return -1;
	}
	// �����׽���,���ڼ���
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET) {
		std::cerr << "�����׽���ʧ�ܣ��������: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}

	//��IP��port
	sockaddr_in serverAddress{};
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(8810);
	if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
		std::cerr << "�󶨴���" << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}

	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << "����ʧ��" << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}

	std::cout << "���������������ȴ��ͻ�������..." << std::endl;

	// ���ܿͻ�������,���128������
	sockaddr_in clientAddress{};//�������ӵĿͻ��˵���Ϣ
	int clientAddressLength = sizeof(clientAddress);
	//����ֵ������ͨ�ŵ��ļ������������û�пͻ������ӣ�accept�������ġ����Ҫͬʱ����������ӣ�Ҫִ�ж��accept���ڶ����Ǵ�������
	SOCKET clientSocket = accept(serverSocket, reinterpret_cast<sockaddr*>(&clientAddress),
		&clientAddressLength);
	
	if (clientSocket == INVALID_SOCKET) {
		std::cerr << "���ܿͻ�������ʧ�ܣ��������: " << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}
	else {
		std::cout << "�����ӿͻ��˵Ķ˿ڣ�" << clientAddress.sin_port << std::endl;
	}

	const char* corsHeader = "Access-Control-Allow-Origin: *\r\n";
	send(clientSocket, corsHeader, strlen(corsHeader), 0);
	std::cout << "�ѽ��ܿͻ�������" << std::endl;

	

	// ���ͺͽ�������
	char buffer[1024];
	int bytesRead;//����ֵ����0��ʵ�ʽ��յ��������ֽ���������0�ǶԷ��Ͽ����ӣ�-1�ǽ�������ʧ��
	while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
		// ��ȡ WebSocket Key
		//std::string key;
		//const std::string requestHeader(buffer);
		//size_t keyStart = requestHeader.find("Sec-WebSocket-Key:") + 19;
		//size_t keyEnd = requestHeader.find("\r\n", keyStart);
		//if (keyStart != std::string::npos && keyEnd != std::string::npos) {
		//	key = requestHeader.substr(keyStart, keyEnd - keyStart);
		//}

		//// ���� WebSocket ������Ӧ
		//std::string response = "HTTP/1.1 101 Switching Protocols\r\n";
		//response += "Upgrade: websocket\r\n";
		//response += "Connection: Upgrade\r\n";
		//response += "Sec-WebSocket-Accept: " + key + "258EAFA5-E914-47DA-95CA-C5AB0DC85B11" + "\r\n\r\n";

		//// ����������Ӧ
		//if (send(clientSocket, response.c_str(), response.length(), 0) == -1) {
		//	std::cerr << "����������Ӧʧ��" << std::endl;
		//	closesocket(clientSocket);
		//	continue;
		//}

		// ������յ�������
		std::cout << "���յ������ݣ�" << buffer << std::endl;

		// ���ͻظ���send����ֵ����0��ʵ�ʷ����ֽ�����-1����ʧ��
		const char* str = "Hello from server!";
		send(clientSocket, str, strlen(str), 0);
	}
	if (bytesRead == 0) {
		std::cout << "�ͻ��˶Ͽ�����" << std::endl;
	}
	else if (bytesRead == SOCKET_ERROR) {
		std::cerr << "��������ʧ�ܣ��������: " << WSAGetLastError() << std::endl;
	}

	// �ر��׽���
	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
	return 0;
}

//�����Ӧͷ
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
	std::cout << "�ѽ��ܿͻ�������" << std::endl;
	char buffer[1024] = "\n";
	int bytesRead;



	while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
		std::cout << "���յ������ݣ�" << buffer << std::endl;


		HWND desktopWnd = GetDesktopWindow();
		YunRenderCV yunRender;
		std::string imageStr = yunRender.getWindow(desktopWnd);

		// �ϲ���Ӧͷ������
		std::string fullResponse = postHTTPHead(imageStr);
		int sentBytes = send(clientSocket, fullResponse.c_str(), fullResponse.length(), 0);
	}

	if (bytesRead == 0) {
		std::cout << "�ͻ��˶Ͽ�����" << std::endl;
	}
	else if (bytesRead == SOCKET_ERROR) {
		std::cerr << "��������ʧ�ܣ��������: " << WSAGetLastError() << std::endl;
	}
	// �ر��׽���
	closesocket(clientSocket);
	return -1;
}

void working(SOCKET socketServer) {
	while (true) {
		std::cout << "���������������ȴ��ͻ�������..." << std::endl;
		sockaddr_in clientAddress{};//�������ӵĿͻ��˵���Ϣ
		int clientAddressLength = sizeof(clientAddress);
		SOCKET clientSocket = accept(socketServer, reinterpret_cast<sockaddr*>(&clientAddress), &clientAddressLength);
		if (clientSocket == INVALID_SOCKET) {
			std::cerr << "���ܿͻ�������ʧ�ܣ��������: " << WSAGetLastError() << std::endl;
			break;
		}
		std::thread t(threadWork, clientSocket);
		t.detach();// �����̣߳�ʹ���ں�̨����
	}
}
//���߳�ִ��socket����accept���ӣ�recv��ȡ��sendд���⼸���ط������û����Ӧ�ͻ�����,��������ͨXHR���ӣ�����ws
int SocketApi::createThreadSocket() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "��ʼ�� Winsock ʧ��" << std::endl;
		return -1;
	}
	SOCKET socketServer = socket(AF_INET, SOCK_STREAM, 0);
	if (socketServer == INVALID_SOCKET) {
		std::cerr << "�����׽���ʧ��" << std::endl;
		return -1;
	}
	sockaddr_in serverAddress{};
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(8810);
	if (bind(socketServer, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR) {
		std::cerr << "�󶨴���" << WSAGetLastError() << std::endl;
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}
	if (listen(socketServer, SOMAXCONN) == SOCKET_ERROR) {
		std::cerr << "����ʧ��" << WSAGetLastError() << std::endl;
		closesocket(socketServer);
		WSACleanup();
		return -1;
	}
	working(socketServer);
	
	WSACleanup();
	closesocket(socketServer);
	return -1;
}


