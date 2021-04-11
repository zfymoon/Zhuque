
#ifndef __COMMON__UTILS__
#define __COMMON__UTILS__

#include <iostream>
#include <string>
#include <ctime>
#include <thread>
#include <sstream>
namespace Util{

    std::string getCurrentTime(){
        time_t cTime = time(0);
        tm *localTime = localtime(&cTime);
        std::string result{};
        result += std::to_string(localTime->tm_year + 1900);
        result += ("-"+std::to_string(localTime->tm_mon));
        result += ("-"+std::to_string(localTime->tm_mday));
        result += (" "+std::to_string(localTime->tm_hour));
        result += (":"+std::to_string(localTime->tm_min));
        result += (":"+std::to_string(localTime->tm_sec));
        return result;

    }

    std::string getCurrentThreadID(){
        std::ostringstream strStream;
        strStream << std::this_thread::get_id();
        return strStream.str();
    }
    
}

#endif