#include <cstring>
#include <string>
#include <iostream>
#include <ctime>
#include <csignal>
#include <fstream>
#include <sstream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <functional>
#include <vector>
#include <map>
#include <set>
#include <locale>
#include <codecvt>

#include "boostFilesystem.h"
//#include "learned.cpp"

//WinSock.h 是 Windows Sockets API 的头文件
#include <Windows.h>
#include <tlhelp32.h>
#include <psapi.h>

#include <filesystem>

#include "algorithmApi.h"
#include "windowAPi.h"
#include <list>
#include <stack>
#include "socketApi.h"
#include "winApi.h"
#include "mysqlConnect.h"
//#include "clientServer.h"
#include "doubleThread.h"
#include "strText.h"//algorithm库
#include "container.h"//容器库
using namespace std;
namespace fs = boost::filesystem;

#define PI 3.1415926
#define MAXNUM(a, b)(a<b?a:b)
#define ChangeStr(x) #x //参数x， #x 是将传递进去的x内容用双引号包裹起来为字符串


//argc表示命令行参数的数量，而argv是一个指向字符数组的指针数组，每个元素存储一个命令行参数的字符串
int main(int argc, char* argv[]) {
	/*WinApi getProcess;
	HWND windowHandle = FindWindow(nullptr, "智慧仿真运行平台");
	getProcess.getWindow(windowHandle);*/

	//学习屏幕截屏。做远程控制
	/*SocketApi getWindowImage;
	getWindowImage.createThreadSocket();*/
	container createContain;
	return 0;
}