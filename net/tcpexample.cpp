
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
#include "../common/log.cpp"

int startServer(){

    std::string TAG{"TCPServer"};

    std::thread serverTask([TAG](){

    constexpr int PORT_NUMBER = 9983;
    addrinfo * addrInfo;
    addrinfo addrHints{};

    addrHints.ai_addr = nullptr;
    addrHints.ai_next = nullptr;
    addrHints.ai_socktype = SOCK_STREAM;
    addrHints.ai_family = AF_INET;
    addrHints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;

    if(getaddrinfo(nullptr,std::to_string(PORT_NUMBER).c_str(),&addrHints,&addrInfo) == 0){
        while(addrInfo != nullptr){
            int sockFD = socket(addrInfo->ai_family,addrInfo->ai_socktype,addrInfo->ai_protocol);
            if(sockFD != -1){
                if(bind(sockFD,addrInfo->ai_addr,addrInfo->ai_addrlen) != -1){
                    if(listen(sockFD,5) != -1){
                        Log::d(TAG,"Start listen ");
                        int clientFD = 0;
                        sockaddr_storage  clientAddrInfo{};
                        int addrLength = sizeof(sockaddr_storage);
                        int number = 0;
                        Log::d(TAG,"Server start");
                        while((clientFD = accept(sockFD,(sockaddr *)&clientAddrInfo,(socklen_t *) &addrLength)) != -1){
                            number++;
                             std::cout<<"[client connect] new "<<std::endl;
                            //child task
                            std::thread childTask([
                                TAG,
                                clientFD,clientAddrInfo,
                                addrLength,number](){
                                char serviceInfo[NI_MAXSERV];
                                char hostInfo[NI_MAXHOST];
                                if(getnameinfo((sockaddr *)&clientAddrInfo,addrLength,hostInfo,NI_MAXHOST,serviceInfo,NI_MAXSERV,0) == 0){
                                    std::cout<<"[client connect]"<<hostInfo<<"#"<<serviceInfo<< std::endl;
                                }else{
                                    std::cout<<"[client connect] unknown"<<std::endl;
                                }
                                std::array<char,1024> buffer{};
                                int readNum = 0;
                                while((readNum = read(clientFD,buffer.data(),buffer.size())) != 0){
                                    std::string message(buffer.cbegin(),readNum);
                                    Log::d(TAG,std::string{"[Server #"} + std::to_string(number) +"][Receive ]"+message );
    
                                }
                            });

                            childTask.detach();
                            
                        }
                        std::cerr<<"Accept failed "<<std::endl;
                    }
                }
            }
            addrInfo = addrInfo->ai_next;

        }
    }

    freeaddrinfo(addrInfo);

    });



 

    serverTask.join();

    
    return 0;
}