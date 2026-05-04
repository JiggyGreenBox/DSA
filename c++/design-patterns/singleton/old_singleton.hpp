#ifndef logger_h
#define logger_h
#include <string>
#include <mutex>

class Logger{
private:
    static int counter;
    static Logger* loggerInstance;
    static std::mutex mtx;
    Logger();

    Logger(const Logger&);
    Logger& operator=(const Logger&);
    
public:
    static Logger* getLogger();
    void Log(std::string msg);

    // Logger(Logger& rhs) = delete;
    // Logger& operator=(const Logger&) = delete;
};
#endif