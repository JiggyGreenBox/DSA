#include <iostream>
#include <thread>
// #include "old_singleton.hpp"
// #include "better_pre_11_singleton.hpp"
#include "meyers_singleton_c11.hpp"
using namespace std;


void thread1(){
    // Logger* logger1 = Logger::getLogger();
    // Logger2& logger1 = Logger2::getInstance();
    MLogger& logger1 = MLogger::getInstance();
    logger1.Log("this msg is from logger1");

    // Logger2* logger2 = logger1; // copy constructor not handled
}

void thread2(){
    // Logger* logger2 = Logger::getLogger();
    // Logger2& logger2 = Logger2::getInstance();
    MLogger& logger2 = MLogger::getInstance();
    logger2.Log("this msg is from logger2");

    // Logger2* logger3;
    // logger3 = logger2; // copy assignment not handled
}

int main(){
    
    thread t1(thread1);
    thread t2(thread2);

    t1.join();
    t2.join();

    
    return 0;
}