//
// Created by JustinWCola on 2023/7/23.
//

#ifndef STM32_CMAKE_LGPIO_H
#define STM32_CMAKE_LGPIO_H

#include <cstdint>
#include "main.h"

typedef enum
{
    Reset   = 0,
    Set     = 1,
    Toggle  = 2
}eGPIOState;

class cGPIO
{
public:
    cGPIO(GPIO_TypeDef* port, uint16_t pin):port(port), pin(pin){};
    void set(uint8_t state);
    void get();
    void lock();
private:
    GPIO_TypeDef* port;
    uint16_t pin;
};


#endif //STM32_CMAKE_LGPIO_H
