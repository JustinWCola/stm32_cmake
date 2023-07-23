//
// Created by JustinWCola on 2023/7/23.
//

#include "lgpio.h"

void cGPIO::set(uint8_t state)
{
    if (state == Reset)
        HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
    else if (state == Set)
        HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
    else if (state == Toggle)
        HAL_GPIO_TogglePin(port, pin);
}

void cGPIO::get()
{
    HAL_GPIO_ReadPin(port, pin);
}

void cGPIO::lock()
{
    HAL_GPIO_LockPin(port, pin);
}



