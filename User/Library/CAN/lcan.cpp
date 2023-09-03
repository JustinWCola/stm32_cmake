//
// Created by JustinWCola on 2023/9/3.
//

#include <cstring>
#include "lcan.h"
#include "can.h"

#define CAN_CNT_MAX 16

static uint8_t can_cnt = 0;
static cCan *can_list[CAN_CNT_MAX];

cCan::cCan(CAN_HandleTypeDef *local_can, uint32_t tx_id, uint32_t rx_id, void (*rx_user_callback)()) : _local_can(local_can), _tx_id(tx_id), _rx_id(rx_id), rxUserCallback(rx_user_callback)
{
    can_list[can_cnt++] = this;
}

void cCan::init()
{
    CAN_FilterTypeDef can_filter;
    static uint8_t can1_filter_bank = 0, can2_filter_bank = 14;

    can_filter.FilterActivation = CAN_FILTER_ENABLE;
    can_filter.FilterMode = CAN_FILTERMODE_IDMASK;
    can_filter.FilterScale = CAN_FILTERSCALE_32BIT;
    can_filter.FilterIdHigh = 0x0000;
    can_filter.FilterIdLow = 0x0000;
    can_filter.FilterMaskIdHigh = 0x0000;
    can_filter.FilterMaskIdLow = 0x0000;
    can_filter.FilterBank = _local_can == &hcan1 ? (can1_filter_bank++) : (can2_filter_bank++); //这对吗
    can_filter.SlaveStartFilterBank = 14;
    can_filter.FilterFIFOAssignment = CAN_RX_FIFO0;//要分奇偶吗

    HAL_CAN_ConfigFilter(_local_can, &can_filter);

    HAL_CAN_Start(_local_can);
    HAL_CAN_ActivateNotification(_local_can, CAN_IT_RX_FIFO0_MSG_PENDING);
    HAL_CAN_ActivateNotification(_local_can, CAN_IT_RX_FIFO1_MSG_PENDING);
}

void cCan::send(uint8_t *tx_buf)
{
    CAN_TxHeaderTypeDef tx_header;
    uint8_t tx_data[8];
    uint32_t tx_mailbox;

    tx_header.StdId = _tx_id;
    tx_header.IDE = _tx_ide;
    tx_header.RTR = _tx_rtr;
    tx_header.DLC = _tx_dlc;
    memcpy(tx_buf, tx_data, _tx_dlc);

    HAL_CAN_AddTxMessage(_local_can, &tx_header, tx_data, &tx_mailbox);
}

void cCan::rxCallback(CAN_HandleTypeDef *hcan, CAN_RxHeaderTypeDef rx_header, uint8_t *rx_data)
{
    if (hcan == _local_can && rx_header.StdId == _rx_id)
    {
        memcpy(_rx_buf, rx_data, rx_header.IDE);
        rxUserCallback(_rx_buf);   //修改用户回调即可
    }
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rx_header;
    uint8_t rx_data[8];
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);

    for (uint8_t i = 0; i < can_cnt; i++)
        can_list[i]->rxCallback(hcan, rx_header, rx_data);
}


