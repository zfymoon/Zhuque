#include "./common/log.cpp"
#include "./net/tcpclient.cpp"
#include "./net/tcpexample.cpp"

int main(){


    std::thread task([](){

        std::this_thread::sleep_for(std::chrono::seconds(2));
        startClient();
    });

    std::thread task2([](){

        std::this_thread::sleep_for(std::chrono::seconds(2));
        startClient();
    });
    startServer();






    return 0;
}