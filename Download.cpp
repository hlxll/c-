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
        WINHTTP_NO_PROXY_NAME,//�������������
        WINHTTP_NO_PROXY_BYPASS, //�ƹ������������IP��ַ�б�
        0);

    // ָ��HTTP����ĳ�ʼĿ�������
    if (hSession)
        hConnect = WinHttpConnect(hSession, url, port, 0);

    // ����HTTP���󣬷��ؾ��
    //!���ﲻʹ�û��棬�Ϳ������󱾵�ip��ַ����Ŀ��
    if (hConnect)
        hRequest = WinHttpOpenRequest(hConnect,
            L"GET", //����ν�ʣ�GET��POST��HEAD��
            NULL,//Ŀ����Դ���ַ���ָ��
            NULL, //HTTP�汾��null��ָ��HTTP/1.1
            WINHTTP_NO_REFERER,//������������ָ���ĵ���URL
            WINHTTP_DEFAULT_ACCEPT_TYPES,//ָ�����յ�ý������
            WINHTTP_FLAG_REFRESH);//�����һЩ����ͷ���壬��ǰ�����ǲ�ʹ�û��棬����cache-contrl:no-cache
    else
        printf("Error %u in WinHttpOpenRequest.\n",
            GetLastError());
    // �������󵽷�����
    if (hRequest) {
        bResults = WinHttpSendRequest(hRequest,
            WINHTTP_NO_ADDITIONAL_HEADERS,//׷�ӵ�����ͷ
            0,//����ͷ����
            WINHTTP_NO_REQUEST_DATA,//��������ͷ���͵��κο�ѡ���ݣ�ͨ���û�post��PUT����ʱ���͵�����
            0,//��ѡ���ݵĳ���
            0,//���з��͵������ݳ��ȣ�ָ�������Content-Length�������ڸ�API֮����ģ����Ҫ������Ҫ���ⴴ������
            NULL//��������Ĳ���������һ�𴫵�
            );
    }
    else {
        printf("Error %u in WinHttpSendRequest.\n", GetLastError()); 
        return -1;
    }

    // ����WinHttpSendRequest�����������Ӧ
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
            //���ؿ�ʹ��WinHttpReadData��ȡ��������
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
                // ���һ�ε�ַ���ڴ档
                ZeroMemory(pszOutBuffer, dwSize + 1);

                //��WinHttpOpenRequest���صľ���ж�ȡ���ݣ�
                if (!WinHttpReadData(hRequest, 
                    (LPVOID)pszOutBuffer,//ָ��������ݵĻ�����ָ��
                    dwSize, //Ҫ��ȡ���ֽ���
                    &dwDownloaded))//ʵ�ʽ��ն�ȡ���ֽ�����ָ��
                    printf("Error %u in WinHttpReadData.\n", GetLastError());
                else
                    printf("%s", pszOutBuffer);
                    printf("��ȡ�ļ�");
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
        //����WinHttpQueryDataAvailable���ؿ��Զ�ȡ������Ϊ0���Ƕ�ȡ����
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
