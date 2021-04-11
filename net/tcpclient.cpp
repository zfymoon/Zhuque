
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <array>
#include <unistd.h>
#include <thread>
#include <arpa/inet.h>
#include <chrono>
#include <signal.h>
#include <unistd.h>
#include "../common/log.cpp"


const int PORT_NUMBER = 9983;
const std::string HOST{"127.0.0.1"};
const std::string TAG{"TCPClient"};
int startClient(){
        int clientFD = socket(AF_INET,SOCK_STREAM,0);
        if(clientFD != -1){
            sockaddr_in clientAddr{};
            clientAddr.sin_family = AF_INET;
            clientAddr.sin_port = htons(PORT_NUMBER);
            int size = HOST.size();
            //set sign handler
            signal(SIGPIPE,SIG_IGN);
            if(inet_pton(AF_INET,HOST.c_str(),&clientAddr.sin_addr)!=-1){
                if(connect(clientFD,(sockaddr *)&clientAddr,sizeof(sockaddr)) !=-1){
                    Log::d(TAG,"Connect success");
                    std::string input;
                    while(getline(std::cin,input)){
                         write(clientFD,input.c_str(),input.size());
                    }
                }else{
                    std::cerr<<"Connect error "<<std::endl;
                }
            }
        }else{
            std::cerr<<"Create error "<<std::endl;
        }
    return 0;
}