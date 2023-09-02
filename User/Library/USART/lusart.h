//
// Created by JustinWCola on 2023/7/24.
//

#ifndef STM32_CMAKE_LUSART_H
#define STM32_CMAKE_LUSART_H

#include <cstdint>
#include "main.h"

class cUsart
{
public:
    typedef enum
    {
        DMA_IDLE_IT = 0,    //DMA空闲中断
        DMA_CPLT_IT = 1     //DMA接收完成中断
    }eUsartType;

    cUsart(UART_HandleTypeDef *local_huart, uint16_t buf_size, eUsartType type, void (*rx_user_callback)());

    void init();
    void send(uint8_t *tx_buf, uint16_t tx_size);
    void rxCallback(UART_HandleTypeDef *huart);

    uint8_t rx_buf[255];

private:
    UART_HandleTypeDef *local_huart{};
    eUsartType type;
    uint16_t buf_size;

    void deinit();
    void (*rxUserCallback)(){};
};

#endif //STM32_CMAKE_LUSART_H
