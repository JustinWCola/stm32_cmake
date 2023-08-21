//
// Created by JustinWCola on 2023/8/21.
//

#include <string>
#include "llog.h"
#include "usart.h"

void cLog::setLevel(eLogLevel level)
{
    _log_level = level;
}

void cLog::info(const char *format, ...)
{
    if(_log_level <= INFO)
    {
        std::string tmp = std::string((const char*)"[INFO]:") + std::string(format);
        usart_printf(tmp.c_str());
    }
}

void cLog::warn(const char *format, ...)
{
    if(_log_level <= WARN)
    {
        std::string tmp = std::string((const char*)"[INFO]:") + std::string(format);
        usart_printf(tmp.c_str());
    }
}

void cLog::error(const char *format, ...)
{
    if(_log_level <= ERROR)
    {
        std::string tmp = std::string((const char*)"[INFO]:") + std::string(format);
        usart_printf(tmp.c_str());
    }
}
