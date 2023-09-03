//
// Created by JustinWCola on 2023/7/19.
//
#include <cstring>
#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "usart.h"
#include "dma.h"

#include "lrgb.h"
#include "lusart.h"
#include "llog.h"

#define START 0x31
#define STOP  0x30
#define MAOHAO  0x3A
#define DEBUG_RX_BUF_SIZE 255

char debug_buf[DEBUG_RX_BUF_SIZE]{};
void test_rxcallback();

cUsart usart1(&huart1, 255, cUsart::IDLE, test_rxcallback);
cLog usart_log(cLog::INFO);

void test_rxcallback()
{
    //解包预处理
    //将串口收到的数据进行处理，新的数组以数字开头，便于之后字符转浮点数的运算
    memcpy(debug_buf, &usart1.rx_buf[5], 10);
    //电机启动
    if (usart1.rx_buf[5] == MAOHAO && usart1.rx_buf[6] == START)
        usart_log.info("1");
    else if (usart1.rx_buf[5] == MAOHAO && usart1.rx_buf[6] == STOP)
        usart_printf("0");
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_TIM5_Init();
    MX_DMA_Init();
    MX_USART1_UART_Init();

    cRgb led(&htim5);
    usart1.init();

    while (1)
    {
        led.loop();
        HAL_Delay(1);
    }
}