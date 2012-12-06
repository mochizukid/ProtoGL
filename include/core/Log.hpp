#pragma once

#include <stdio.h>

namespace pgl {

class Log {
public:
    enum LogLevel { LEVEL_VERBOSE, LEVEL_DEBUG, LEVEL_INFO, LEVEL_ERROR, LEVEL_NONE };
    
    static void SetLevel(LogLevel level) { _level = level; }
    
    static void Verbose(const char *msg) {
        if (_level <= LEVEL_VERBOSE) printf("[V] %s\n", msg);
    }
    
    static void Debug(const char *msg) {
        if (_level <= LEVEL_DEBUG) printf("[D] %s\n", msg);
    }
    
    static void Info(const char *msg) {
        if (_level <= LEVEL_INFO) printf("[I] %s\n", msg);
    }
    
    static void Error(const char *msg) {
        if (_level <= LEVEL_ERROR) printf("[E] %s\n", msg);
    }
    
    static void Print(const char *msg) {
        printf("%s\n", msg);
    }
    

private:
    Log();

    static LogLevel _level;
};

Log::LogLevel Log::_level = LEVEL_DEBUG;

} // namespace pgl

