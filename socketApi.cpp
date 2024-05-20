#pragma once
#include "socketApi.h"
#include <iostream>
#include <winsock2.h>

#include <ws2tcpip.h>
#include <thread>
#include "yunRenderCV.h"
#include <mutex>
#include <condition_variable>
//#include <boost/algorithm/string.hpp>
#include <map>
//#include <boost/property_tree/json_parser.hpp>
//#include <boost/lexical_cast.hpp>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
//#pragma comment(lib, "ws2_32.lib")
int SocketApi::createSocket() {
	//�׽���������ʹ�õ���Winsock�⣬������Ҫ�ٿ�ͷ��ʼ����. WSACleanup�Ƴ�Winsock��
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

std::mutex mutextWindow;
std::condition_variable writeBase;
std::list<int> posiData;
void clickWindow(std::string position) {
	std::unique_lock<std::mutex> lock(mutextWindow);
	//�������
	std::cout << "�������" << std::endl;
	POINT point;
	std::string json_str = R"({"x":"12","y":"22"})";
	nlohmann::json j = nlohmann::json::parse(json_str);
	std::map<std::string, std::string> mapObj = j.get<std::map<std::string, std::string>>();
	point.x = std::stol(mapObj["x"]);
	point.y = std::stol(mapObj["y"]);
	std::cout << mapObj["x"] << std::endl;
	std::cout << mapObj["y"] << std::endl;
	SetCursorPos(point.x, point.y);
	DWORD data = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN;//˫�����
	DWORD x = point.x;
	DWORD y = point.y;
	DWORD val = 0;
	ULONG_PTR str = 0;
	mouse_event(data, x, y, val, str);

	//Sleep(2000);
	posiData.push_back(1);
	writeBase.notify_all();
}
//���ʹ��ڽ�ͼ��ǰ��
void sendBase(SOCKET clientSocket) {
	std::cout << "׼����ȡ��ͼ" << std::endl;
	std::unique_lock<std::mutex> lock(mutextWindow);
	writeBase.wait(lock, []{return posiData.size() > 0; });
	HWND desktopWnd = GetDesktopWindow();
	YunRenderCV yunRender;
	std::string imageStr = yunRender.getWindow(desktopWnd);
	std::cout << "��ȡ��ͼ" << std::endl;
	// �ϲ�get��Ӧͷ������
	std::string fullResponse = postHTTPHead(imageStr);
	int sentBytes = send(clientSocket, fullResponse.c_str(), fullResponse.length(), 0);
	posiData.front();
}
int threadWork(SOCKET clientSocket) {
	std::cout << "�ѽ��ܿͻ�������" << std::endl;
	char buffer[1024] = "\n";
	int bytesRead;



	while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
		//std::cout << "���յ������ݣ�" << buffer << std::endl;
		//ִ�е���¼�
		int x=0, y=0;
		std::string position(buffer);
		int index = position.find("{");
		std::string data = position.substr(index, position.size() - index);

		/*Json::Reader read;
		Json::Value value;
		read.parse(data, value);*/
		/*const char* json_str = R"({"x":"12", "y":"22"})";
		rapidjson::Document document;
		const rapidjson::Value& x = document.Parse(json_str);*/

		std::cout << data << std::endl;
		//ʹ�������������������֮�󣬲Ž��н�ͼ
		std::thread t1(clickWindow, data);
		std::thread t2(sendBase, clientSocket);
		t1.join();
		t2.join();
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
	//reinterpret_cast��������ת��
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


