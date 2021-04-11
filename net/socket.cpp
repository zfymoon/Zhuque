#ifndef __NET__SOCKET__
#define __NET__SOCKET__

#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "../common/log.cpp"


namespace Socket{
    /**
     * 获取IP地址
     **/
    std::string getLocalIP(){
        std::string DNSAddr{"8.8.8.8"};
        int dnsPort = 53;
        int tmpFD = socket(AF_INET,SOCK_STREAM,0);
        if(tmpFD != -1){
            sockaddr_in serverAddr{};
            serverAddr.sin_family = AF_INET;
            serverAddr.sin_port = htons(dnsPort);
            if(inet_pton(AF_INET,DNSAddr.c_str(),&serverAddr.sin_addr) >= 0){
                if(connect(tmpFD,(sockaddr *)&serverAddr,sizeof(serverAddr))>= 0){
                    sockaddr_in clientAddr{};
                    int length = sizeof(clientAddr);
                    char buffer[NI_MAXHOST];
                    if(getsockname(tmpFD,(sockaddr *)&clientAddr,(socklen_t *)&length) >= 0){
                        inet_ntop(AF_INET,&clientAddr.sin_addr,buffer,NI_MAXHOST);
                        close(tmpFD);
                        return std::string(buffer);
                    }
                }
            }
        }
        return std::string();
    }

    void readn(char *buffer,size_t size){

    }


}

#endif