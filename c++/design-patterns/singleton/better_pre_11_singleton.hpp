#include <iostream>
#include <string>
#include <mutex>


class Logger2{
private:
    static Logger2* instance; // shared between object instances
    static std::mutex mtx; // make logger thread safe

    Logger2();

    Logger2(const Logger2&) = delete; // copy constructor
    Logger2& operator=(const Logger2&) = delete; // copy asssignment

public:
    static Logger2& getInstance();
    void Log(std::string msg);
};