//
// Created by JustinWCola on 2023/7/24.
//

#include "lusart.h"

#define USART_CNT_MAX 6

static uint8_t usart_cnt_idle = 0;
static cUsart *usart_list_idle[USART_CNT_MAX];

static uint8_t usart_cnt_cplt = 0;
static cUsart *usart_list_cplt[USART_CNT_MAX];

cUsart::cUsart(UART_HandleTypeDef *local_huart, uint16_t buf_size, eUsartType type, void (*rx_user_callback)()) :
        local_huart(local_huart), buf_size(buf_size), type(type), rxUserCallback(rx_user_callback)
{
    if(type == DMA_IDLE_IT)
        usart_list_idle[usart_cnt_idle++] = this;
    else if(type == DMA_CPLT_IT)
        usart_list_cplt[usart_cnt_cplt++] = this;
    open();
}

///串口类开启函数
void cUsart::open()
{
    if (type == DMA_CPLT_IT)
        HAL_UART_Receive_DMA(local_huart, rx_buf, buf_size);
    else if (type == DMA_IDLE_IT)
        HAL_UARTEx_ReceiveToIdle_DMA(local_huart, rx_buf, buf_size);
    __HAL_DMA_DISABLE_IT(local_huart->hdmarx, DMA_IT_HT);
}

///串口类关闭函数
void cUsart::close()
{
    HAL_UART_DMAStop(local_huart);
}

///串口类回调函数
void cUsart::rxCallback(UART_HandleTypeDef *huart)
{
    if (huart == local_huart)
    {
        close();
        rxUserCallback();   //修改用户回调即可
        open();
    }
}

///串口类发送函数
void cUsart::send(uint8_t *tx_buf, uint16_t tx_size)
{
    HAL_UART_Transmit_DMA(local_huart, tx_buf, tx_size);
}

/**
 * HAL库DMA空闲中断回调函数
 * @param huart 串口指针
 * @param Size  数据大小
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    for (int i=0;i<usart_cnt_idle-1;i++)
        usart_list_idle[i]->rxCallback(huart);
}

/**
 * HAL库DMA接收完成中断回调函数
 * @param huart 串口指针
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    for (int i=0;i<usart_cnt_cplt-1;i++)
        usart_list_cplt[i]->rxCallback(huart);
}