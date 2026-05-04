#include <iostream>
#include <string>
#include <mutex>
#include "better_pre_11_singleton.hpp"

Logger2* Logger2::instance = nullptr;
std::mutex Logger2::mtx;

Logger2::Logger2() {
    std::cout << "Logger2 created\n";
}

Logger2& Logger2::getInstance(){
    if(instance == nullptr){ // double checked lock
        std::lock_guard<std::mutex> lock(mtx); // safer than lock and unlock
        if(instance == nullptr){
            instance = new Logger2();
        }
    }
    return *instance;
}

void Logger2::Log(std::string msg){
    std::cout << msg << std::endl;
}
