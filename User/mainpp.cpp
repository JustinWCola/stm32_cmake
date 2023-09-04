//
// Created by JustinWCola on 2023/7/19.
//

#include <cstring>
#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "usart.h"
#include "dma.h"
#include "can.h"

#include "lrgb.h"
#include "lusart.h"
#include "llog.h"
#include "lcan.h"

#define START 0x31
#define STOP  0x30
#define MAOHAO  0x3A
#define DEBUG_RX_BUF_SIZE 255

class cMotor
{
public:
    void setMotoInfo(int16_t pos, int16_t vel, int16_t cur, int16_t tmp)
    {
        _pos = pos;
        _vel = vel;
        _cur = cur;
        _tmp = tmp;
    }
private:
    int16_t _pos;
    int16_t _vel;
    int16_t _cur;
    int16_t _tmp;

    bool online;
    uint32_t times;
};

char debug_buf[DEBUG_RX_BUF_SIZE]{};
cMotor motor;

void USART_RxCallback(uint8_t *rx_buf);
void CAN_RxCallback(uint8_t *rx_buf);

cRgb rgb(&htim5);
cUsart usart1(&huart1, 255, USART_RxCallback);
cCan can1(&hcan1, 0x200, 0x02, 0x201, CAN_RxCallback);
cLog usart_log(cLog::INFO);

void CAN_RxCallback(uint8_t *rx_buf)
{
    int16_t pos, vel, cur, tmp;
    pos = (int16_t)(*(rx_buf + 0) << 8| *(rx_buf + 1));
    vel = (int16_t)(*(rx_buf + 2) << 8| *(rx_buf + 3));
    cur = (int16_t)(*(rx_buf + 4) << 8| *(rx_buf + 5));
    tmp = (int16_t)(*(rx_buf + 6));
    motor.setMotoInfo(pos, vel, cur, tmp);
}

void USART_RxCallback(uint8_t *rx_buf)
{
    //解包预处理
    //将串口收到的数据进行处理，新的数组以数字开头，便于之后字符转浮点数的运算
    memcpy(debug_buf, rx_buf + 5, 10);
    //电机启动
    if (*(rx_buf + 5) == MAOHAO && *(rx_buf + 6) == START)
        usart_log.info("1");
    else if (*(rx_buf + 5) == MAOHAO && *(rx_buf + 6) == STOP)
        usart_log.info("0");
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_TIM5_Init();
    MX_DMA_Init();
    MX_USART1_UART_Init();

    rgb.init();
    usart1.init();


    while (1)
    {
        rgb.loop();
        uint8_t send_buf[8] = {1,2,3,4,5,6,7,8};
        usart1.send(send_buf,8);
        HAL_Delay(1000);
    }
}