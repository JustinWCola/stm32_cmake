//
// Created by JustinWCola on 2023/7/23.
//

#include "lgpio.h"

void cGPIO::set()
{
    HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_SET);
}

void cGPIO::reset()
{
    HAL_GPIO_WritePin(_port, _pin, GPIO_PIN_RESET);
}

void cGPIO::toggle()
{
    HAL_GPIO_TogglePin(_port, _pin);
}

void cGPIO::get()
{
    HAL_GPIO_ReadPin(_port, _pin);
}

void cGPIO::lock()
{
    HAL_GPIO_LockPin(_port, _pin);
}
