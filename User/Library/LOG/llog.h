//
// Created by JustinWCola on 2023/8/21.
//

#ifndef STM32_CMAKE_LLOG_H
#define STM32_CMAKE_LLOG_H

#include "main.h"

class cLog
{
public:
    typedef enum
    {
        INFO    = 0,
        WARN    = 1,
        ERROR   = 2
    }eLogLevel;

    cLog(eLogLevel level) : _log_level(level){}

    void setLevel(eLogLevel level);
    void info(const char *format, ...);
    void warn(const char *format, ...);
    void error(const char *format, ...);
private:
    eLogLevel _log_level;
};

#endif //STM32_CMAKE_LLOG_H
