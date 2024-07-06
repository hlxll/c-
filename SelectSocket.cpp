//
//  SelectSocket.cpp
//  CDemoLearn
//
//  Created by huanglin on 2024/7/6.
//

#include "SelectSocket.hpp"

int SelectSocket::CreateSocket(){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock<0){
        std::cout << "初始化失败"<<std::endl;
        return -1;
    }
    int opt = 1;
    unsigned int len = sizeof(opt);
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, len);
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(3000);
    if(bind(sock, (struct sockaddr *)&servaddr, sizeof(servaddr))<0){
        std::cout << "绑定失败" << std::endl;
        return -1;
    }
    if(listen(sock, 5)<0){
        std::cout << "监听失败" << std::endl;
        return -1;
    }
    
    return sock;
}
void SelectSocket::SelectApi(){
    int socket = CreateSocket();
    fd_set readFds;
    __DARWIN_FD_ZERO(&readFds);
    __DARWIN_FD_SET(socket, &readFds);//将服务端用于监听的socket加入select的bitMap
    int maxFd = socket;
    while(true){
        fd_set fdRead = readFds;
        fd_set fdWrite = readFds;
        struct timeval timeout;
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
        int infds = select(maxFd+1, &fdRead, &fdWrite, NULL, &timeout);
        if(infds<0){
            std::cout << "select 创建失败" << std::endl;
        }
        if(infds == 0){
            std::cout << "select超时" << std::endl;
        }
        //__DARWIN_FD_ISSET是把事件写入到bitMap中，返回1写入成功，返回0写入失败
        for(int eventFd = 0;eventFd<=maxFd;eventFd++){
            if(__DARWIN_FD_ISSET(eventFd, &fdWrite)==0) continue;//有写事件
        }
        //如果infds>0表示有事件发生，数量就是事件个数,
        for(int eventFd=0;eventFd<=maxFd;eventFd++){
            if(__DARWIN_FD_ISSET(eventFd, &fdRead) == 0) continue;
            //socket是接收连接的套接字，有反应就是有人连接了
            if(eventFd == socket){
                struct sockaddr address;
                
                socklen_t len = sizeof(address);
                int clientSocket = accept(socket, (struct sockaddr*)&address, &len);
                if(clientSocket<0){
                    std::cout << "接收连接客户端失败" << std::endl;
                    continue;
                }
                //将连接的socket保存在bitMap中
                __DARWIN_FD_SET(clientSocket, &readFds);
                if(maxFd<clientSocket){
                    maxFd = clientSocket;
                }
            }else{//连接的客户端有消息
                char buffer[1024];
                memset(buffer, 0, sizeof(buffer));//???
                if(recv(eventFd, buffer, sizeof(buffer), 0)<=0){//接收失败
                    std::cout << "接收连接客户端失败" << std::endl;
                    close(eventFd);
                    __DARWIN_FD_CLR(eventFd, &readFds);//接收失败，清空bitmap相应位置数据
                    if (eventFd == maxFd)// ?????重新计算maxfd的值，注意，只有当eventfd==maxfd时才需要计算。
                      {
                        for (int ii=maxFd;ii>0;ii--)  // 从后面往前找。
                        {
                          if (__DARWIN_FD_ISSET(ii,&readFds))
                          {
                            maxFd = ii; break;
                          }
                        }
                      }
                    
                    continue;
                }else{
                    //接收成功，返回数据
                    send(eventFd, buffer, sizeof(buffer), 0);
                }
                
                
            }
        }
        
        
        
        
    }
    
}
