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

//WinSock.h �� Windows Sockets API ��ͷ�ļ�
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
#include "strText.h"//algorithm��
#include "container.h"//������
using namespace std;
namespace fs = boost::filesystem;

#define PI 3.1415926
#define MAXNUM(a, b)(a<b?a:b)
#define ChangeStr(x) #x //����x�� #x �ǽ����ݽ�ȥ��x������˫���Ű�������Ϊ�ַ���


//argc��ʾ�����в�������������argv��һ��ָ���ַ������ָ�����飬ÿ��Ԫ�ش洢һ�������в������ַ���
int main(int argc, char* argv[]) {
	/*WinApi getProcess;
	HWND windowHandle = FindWindow(nullptr, "�ǻ۷�������ƽ̨");
	getProcess.getWindow(windowHandle);*/

	//ѧϰ��Ļ��������Զ�̿���
	/*SocketApi getWindowImage;
	getWindowImage.createThreadSocket();*/
	container createContain;
	return 0;
}