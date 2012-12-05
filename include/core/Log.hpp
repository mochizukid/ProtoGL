#pragma once

#include <cstdio>

namespace pgl {

class Log {
public:
    enum LogLevel { VERBOSE, DEBUG, INFO, ERROR, NONE };
    
    static void SetLevel(LogLevel level) { _level = level; }
    
    static void Verbose(const char *msg) {
        if (_level <= VERBOSE) printf("[V] %s\n", msg);
    }
    
    static void Debug(const char *msg) {
        if (_level <= DEBUG) printf("[D] %s\n", msg);
    }
    
    static void Info(const char *msg) {
        if (_level <= INFO) printf("[I] %s\n", msg);
    }
    
    static void Error(const char *msg) {
        if (_level <= ERROR) printf("[E] %s\n", msg);
    }
    
    static void Print(const char *msg) {
        printf("%s\n", msg);
    }
    

private:
    Log();

    static LogLevel _level;
};

Log::LogLevel Log::_level = DEBUG;

} // namespace pgl

