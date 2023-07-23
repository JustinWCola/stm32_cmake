//
// Created by JustinWCola on 2023/7/19.
//

#ifndef STM32_CMAKE_LLED_H
#define STM32_CMAKE_LLED_H

#include <cstdint>
#include "main.h"

class cLed
{
public:
    cLed(TIM_HandleTypeDef *tim):rgb_tim(tim)
    {
        rgbInit(rgb_tim);
    }
    void rgbLoop();
private:
    TIM_HandleTypeDef *rgb_tim;
    void rgbInit(TIM_HandleTypeDef *tim);
    void rgbSet(uint32_t argb);
};

#endif //STM32_CMAKE_LLED_H
