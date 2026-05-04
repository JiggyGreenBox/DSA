#include "meyers_singleton_c11.hpp"

MLogger& MLogger::getInstance(){
    static MLogger instance; 
    return instance;
}

void MLogger::Log(const std::string& msg){

}

MLogger::MLogger() {
    std::cout << "--- Logger Initialized on Thread: " << std::this_thread::get_id() << " ---" << std::endl;
}