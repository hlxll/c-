//
//  SelectSocket.hpp
//  CDemoLearn
//
//  Created by huanglin on 2024/7/6.
//

#ifndef SelectSocket_hpp
#define SelectSocket_hpp

#include <stdio.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/fcntl.h>
class SelectSocket{
public:
    int CreateSocket();
    void SelectApi();
};
#endif /* SelectSocket_hpp */
