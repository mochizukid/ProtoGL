#pragma once

#include <cstdio>

namespace pgl {

class Log {
public:
    enum LogLevel { DEBUG, INFO, ERROR, NONE };
    
    static void SetLevel(LogLevel level) { _level = level; }
    
    static void Debug(const char *msg) {
        if (_level <= DEBUG) printf("[D] %s\n", msg);
    }
    
    static void Info(const char *msg) {
        if (_level <= INFO) printf("[I] %s\n", msg);
    }
    
    static void Error(const char *msg) {
        if (_level <= ERROR) printf("[E] %s\n", msg);
    }
    

private:
    Log();

    static LogLevel _level;
};

Log::LogLevel Log::_level = DEBUG;

} // namespace pgl

