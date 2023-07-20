//
// Created by JustinWCola on 2023/7/19.
//

#ifndef STM32_CMAKE_LED_H
#define STM32_CMAKE_LED_H

#include <cstdint>

class cLed
{
public:
    void rgbLoop();
private:
    void rgbSet(uint32_t argb);
};

#endif //STM32_CMAKE_LED_H
