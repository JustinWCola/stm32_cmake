//
// Created by JustinWCola on 2023/7/19.
//
#include "main.h"
#include "gpio.h"
#include "led.h"
#include "tim.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_TIM5_Init();

    cLed led(&htim5);
    while (1)
    {
        led.rgbLoop();
    }
}