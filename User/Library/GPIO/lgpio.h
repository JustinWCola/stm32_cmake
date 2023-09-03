//
// Created by JustinWCola on 2023/7/23.
//

#ifndef LGPIO_H
#define LGPIO_H

#include <cstdint>
#include "main.h"

class cGPIO
{
public:
    cGPIO(GPIO_TypeDef *port, uint16_t pin): _port(port), _pin(pin){};

    void set();
    void reset();
    void toggle();
    void get();
    void lock();
private:
    GPIO_TypeDef *_port;
    uint16_t _pin;
};

#endif //LGPIO_H
