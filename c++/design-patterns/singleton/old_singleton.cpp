#include "old_singleton.hpp"
#include <iostream>
using namespace std;

int Logger::counter = 0;
Logger* Logger::loggerInstance = nullptr;
mutex Logger::mtx;


Logger::Logger(){
    counter++;
    cout << "New instance created. Instance #"<<counter << endl;
}

void Logger::Log(std::string msg) {
    cout << msg << endl;
}

Logger* Logger::getLogger(){
    // first approach locks each time

    // mtx.lock();
    // if(loggerInstance == nullptr){
    //     loggerInstance = new Logger();
    // }
    // mtx.unlock();
    // return loggerInstance;

    // Double-Checked Locking
    if(loggerInstance == nullptr){
        // A lock is only acquired if the instance hasn't been created yet,
        // 2 threads may enter here (worst case scenario)
        mtx.lock(); // they are in queue not
        if(loggerInstance == nullptr){
            loggerInstance = new Logger(); // only 1 enters here
        }
        mtx.unlock();
    }
    // the lock is expensive, this approach ensures subsequent calls are cheaper
    return loggerInstance;
}