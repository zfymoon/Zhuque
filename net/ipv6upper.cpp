//ipv6大写转换程序
#include <iostream>
#include <string>
#include <thread>
#include <array>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
int ipv6upper(){


    int port = 9981;
    //本地地址
    std::string addr{"::1"};
    std::thread serverTask([&port,&addr](){
        int serverFD = socket(AF_INET6,SOCK_DGRAM,0);
        if(serverFD != -1){
            sockaddr_in6 serverAddr{};
            serverAddr.sin6_family = AF_INET6;
            serverAddr.sin6_port = htons(port);
            serverAddr.sin6_addr = in6addr_any;

            if(bind(serverFD,(sockaddr *)&serverAddr,sizeof(serverAddr)) != -1){
                std::array<char,1024> buffer{};
                sockaddr_in6 clientAddr{};

                int readNum;
                int addrLength = sizeof(clientAddr);
            
                while((readNum = recvfrom(serverFD,buffer.data(),10,0,(sockaddr *)&clientAddr,(socklen_t *)&addrLength)) != -1){

                    std::string message(buffer.cbegin(),readNum);
                
                    for(auto &i : message){
                        i = toupper(i);
                    }
                    sendto(serverFD,message.c_str(),message.size(),0,(sockaddr *) &clientAddr,sizeof(clientAddr));
                }
            }else{
                std::cerr<<"bind failed"<<std::endl;
            }
        }
    });

    std::thread clientTask([&port](){

        std::this_thread::sleep_for(std::chrono::seconds(1));
        int clientFD = socket(AF_INET6,SOCK_DGRAM,0);

        sockaddr_in6 serverAddr{};
        serverAddr.sin6_family = AF_INET6;
        serverAddr.sin6_port = htons(port);

        if(inet_pton(AF_INET6,"::1",&serverAddr.sin6_addr)!=-1){
            std::string input{};
            while(getline(std::cin,input)){
                sendto(clientFD,input.c_str(),input.size(),0,(sockaddr *) &serverAddr,sizeof(serverAddr));
                std::array<char,1024> readBuffer{};
                int readNum = recvfrom(clientFD,readBuffer.data(),readBuffer.size(),0,nullptr,nullptr);
                std::cout<<"[from server] "<<std::string(readBuffer.cbegin(),readNum)<<std::endl;
            }
        }else{
            std::cerr<<"Error in set"<<std::endl;
        }

    });
    serverTask.join();
    return 0;
}