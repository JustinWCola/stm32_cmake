//
// Created by JustinWCola on 2023/7/24.
//

#include "lusart.h"

#define USART_CNT_MAX 6

static uint8_t usart_cnt_idle = 0;
static cUsart *usart_list_idle[USART_CNT_MAX];

static uint8_t usart_cnt_cplt = 0;
static cUsart *usart_list_cplt[USART_CNT_MAX];

cUsart::cUsart(UART_HandleTypeDef *local_huart, uint16_t buf_size, void (*rx_user_callback)()) :
        _local_huart(local_huart), _buf_size(buf_size), rxUserCallback(rx_user_callback)
{
    _type = IDLE;
    usart_list_idle[usart_cnt_idle++] = this;
}

cUsart::cUsart(UART_HandleTypeDef *local_huart, uint16_t buf_size, eUsartType type, void (*rx_user_callback)()) :
        _local_huart(local_huart), _buf_size(buf_size), _type(type), rxUserCallback(rx_user_callback)
{
    if(type == IDLE)
        usart_list_idle[usart_cnt_idle++] = this;
    else if(type == CPLT)
        usart_list_cplt[usart_cnt_cplt++] = this;
}

///串口类开启函数
void cUsart::init()
{
    if (_type == CPLT)
        HAL_UART_Receive_DMA(_local_huart, rx_buf, _buf_size);
    else if (_type == IDLE)
        HAL_UARTEx_ReceiveToIdle_DMA(_local_huart, rx_buf, _buf_size);
    __HAL_DMA_DISABLE_IT(_local_huart->hdmarx, DMA_IT_HT);
}

///串口类关闭函数
void cUsart::deinit()
{
    HAL_UART_DMAStop(_local_huart);
}

///串口类回调函数
void cUsart::rxCallback(UART_HandleTypeDef *huart)
{
    if (huart == _local_huart)
    {
        deinit();
        rxUserCallback();   //修改用户回调即可
        init();
    }
}

///串口类发送函数
void cUsart::send(uint8_t *tx_buf, uint16_t tx_size)
{
    HAL_UART_Transmit_DMA(_local_huart, tx_buf, tx_size);
}

/**
 * HAL库DMA空闲中断回调函数
 * @param huart 串口指针
 * @param Size  数据大小
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    for (uint8_t i=0;i<usart_cnt_idle;i++)
        usart_list_idle[i]->rxCallback(huart);
}

/**
 * HAL库DMA接收完成中断回调函数
 * @param huart 串口指针
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    for (uint8_t i=0;i<usart_cnt_cplt;i++)
        usart_list_cplt[i]->rxCallback(huart);
}