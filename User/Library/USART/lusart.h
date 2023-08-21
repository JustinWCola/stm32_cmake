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
    cUsart(UART_HandleTypeDef *local_huart, uint16_t buf_size, eUsartType type, void (*rx_user_callback)());

    void send(uint8_t *tx_buf, uint16_t tx_size);
    void rxCallback(UART_HandleTypeDef *huart);

private:
    UART_HandleTypeDef *local_huart{};
    eUsartType type;
    uint16_t buf_size;
    uint8_t rx_buf[255];

    void open();
    void close();
    void (*rxUserCallback)(){};
};

#endif //STM32_CMAKE_LUSART_H
