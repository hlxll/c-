#include "Download.h"
int Download::GetFileContent(LPCWSTR url, INTERNET_PORT port)
{
    DWORD dwSize = 0;
    DWORD dwDownloaded = 0;
    LPSTR pszOutBuffer;
    BOOL  bResults = FALSE;
    HINTERNET  hSession = NULL,
        hConnect = NULL,
        hRequest = NULL;

    

    // Use WinHttpOpen to obtain a session handle.
    hSession = WinHttpOpen(L"WinHTTP Example/1.0",
        WINHTTP_ACCESS_TYPE_NO_PROXY,
        WINHTTP_NO_PROXY_NAME,//代理服务器名称
        WINHTTP_NO_PROXY_BYPASS, //绕过代理的主机或IP地址列表
        0);

    // 指定HTTP请求的初始目标服务器
    if (hSession)
        hConnect = WinHttpConnect(hSession, url, port, 0);

    // 创建HTTP请求，返回句柄
    //!这里不使用缓存，就可以请求本地ip地址的项目了
    if (hConnect)
        hRequest = WinHttpOpenRequest(hConnect,
            L"GET", //请求谓词，GET，POST，HEAD等
            NULL,//目标资源的字符串指针
            NULL, //HTTP版本，null则指向HTTP/1.1
            WINHTTP_NO_REFERER,//第三个参数的指向文档的URL
            WINHTTP_DEFAULT_ACCEPT_TYPES,//指定接收的媒体类型
            WINHTTP_FLAG_REFRESH);//请求的一些请求头定义，当前参数是不使用缓存，类似cache-contrl:no-cache
    else
        printf("Error %u in WinHttpOpenRequest.\n",
            GetLastError());
    // 发送请求到服务器
    if (hRequest) {
        bResults = WinHttpSendRequest(hRequest,
            WINHTTP_NO_ADDITIONAL_HEADERS,//追加的请求头
            0,//请求头长度
            WINHTTP_NO_REQUEST_DATA,//包含请求头后发送的任何可选数据，通常用户post或PUT请求时发送的数据
            0,//可选数据的长度
            0,//所有发送的总数据长度，指定请求的Content-Length，不能在该API之间更改，如果要更改需要另外创建请求
            NULL//包含程序的参数，随句柄一起传递
            );
    }
    else {
        printf("Error %u in WinHttpSendRequest.\n", GetLastError()); 
        return -1;
    }

    // 接收WinHttpSendRequest发起请求的相应
    if (bResults)
        bResults = WinHttpReceiveResponse(hRequest, NULL);
    else {
        printf("Error %u in WinHttpReceiveResponse.\n", GetLastError());
        return -1;
    }
    if (bResults)
    {
        do
        {
            // Check for available data.
            dwSize = 0;
            //返回可使用WinHttpReadData读取的数据量
            if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
                printf("Error %u in WinHttpQueryDataAvailable.\n",
                    GetLastError());

            // Allocate space for the buffer.
            pszOutBuffer = new char[dwSize + 1];
            if (!pszOutBuffer)
            {
                printf("Out of memory\n");
                dwSize = 0;
            }
            else
            {
                // 清空一段地址的内存。
                ZeroMemory(pszOutBuffer, dwSize + 1);

                //从WinHttpOpenRequest返回的句柄中读取数据，
                if (!WinHttpReadData(hRequest, 
                    (LPVOID)pszOutBuffer,//指向接收数据的缓冲区指针
                    dwSize, //要读取的字节数
                    &dwDownloaded))//实际接收读取了字节数的指针
                    printf("Error %u in WinHttpReadData.\n", GetLastError());
                else
                    printf("%s", pszOutBuffer);
                    printf("读取文件");
                    std::ofstream writeFile;
                    writeFile.open(downName, std::ios::app);
                    if (writeFile.is_open()) {
                        writeFile << pszOutBuffer;
                    }
                    writeFile.close();

                // Free the memory allocated to the buffer.
                delete[] pszOutBuffer;
            }
        } while (dwSize > 0);
        //上面WinHttpQueryDataAvailable返回可以读取的数，为0就是读取完了
    }


    // Report any errors.
    if (!bResults)
        printf("Error %d has occurred.\n", GetLastError());

    // Close any open handles.
    if (hRequest) WinHttpCloseHandle(hRequest);
    if (hConnect) WinHttpCloseHandle(hConnect);
    if (hSession) WinHttpCloseHandle(hSession);
    return 1;
}


void Download::SetDownName(std::string name) {
    downName = name;
}
