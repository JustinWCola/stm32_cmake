//
// Created by JustinWCola on 2023/7/24.
//

#ifndef STM32_CMAKE_LUSART_H
#define STM32_CMAKE_LUSART_H

#include <cstdint>
#include "main.h"

typedef enum
{
    DMA_IDLE_IT = 0,    //DMA空闲中断
    DMA_CPLT_IT = 1     //DMA接收完成中断
}eUsartType;

class cUsart
{
public:
    cUsart(UART_HandleTypeDef *local_huart, uint16_t buf_size, eUsartType type) :
            local_huart(local_huart), buf_size(buf_size), type(type) {}

    void open();
    void close();
    void rxCallback(UART_HandleTypeDef *huart);
    void txCallback(UART_HandleTypeDef *huart);
    void (*rxUserCallback)(){};
    void (*txUserCallback)(){};

private:
    UART_HandleTypeDef *local_huart{};
    eUsartType type;
    uint16_t buf_size;
    uint8_t rx_buf[255];
};

#endif //STM32_CMAKE_LUSART_H
