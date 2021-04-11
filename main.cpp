#include "./common/log.cpp"
#include "./net/tcpclient.cpp"
#include "./net/tcpexample.cpp"
#include "./net/socket.cpp"

int main(){

    Log::d("Socket","Local IP is "+Socket::getLocalIP());

    return 0;
}