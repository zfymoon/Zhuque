
#ifndef __COMMON__LOG__
#define __COMMON__LOG__
#include <string>
#include <iostream>
#include "utils.cpp"
#include <thread>
namespace Log{

    enum Level{
        DEBUG = 0,
        ERROR
    };

    void printLog(Level level,const std::string & tag, const std::string & message){

        std::string timeTAG =  Util::getCurrentTime();

        std::string info{};

        info += ("["+timeTAG+"]"+"["+Util::getCurrentThreadID()+"]"+"["+tag+"]"+message);

        switch (level){
            case DEBUG:
                std::cout<<info<<std::endl;
                break;
            case ERROR:
                std::cerr<<info<<std::endl;
                break;
            default:
                break;
        }
    }
    void e(const std::string & tag,const std::string & message){

        printLog(ERROR,tag,message);

    }
    void d(const std::string & tag,const std::string & message){
         printLog(DEBUG,tag,message);

    }

}
#endif