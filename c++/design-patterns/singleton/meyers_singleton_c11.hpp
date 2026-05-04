#include <iostream>
#include <string>
#include <thread>

class MLogger{
public:
    static MLogger& getInstance();
    void Log(const std::string& msg);

    // Made public for better compiler error messages
    MLogger(const MLogger&) = delete;
    MLogger& operator=(const MLogger&) = delete;
private:
    MLogger();
    ~MLogger() = default;
};