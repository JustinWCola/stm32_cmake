//
// Created by JustinWCola on 2023/9/3.
//

#ifndef LCAN_H
#define LCAN_H

#include <cstdint>
#include "main.h"

class cCan
{
public:
    cCan(CAN_HandleTypeDef *local_can, uint32_t tx_id, uint32_t rx_id, void (*rx_user_callback)(uint8_t *rx_buf));

    void init();
    void send(uint8_t *tx_data);
    void rxCallback(CAN_HandleTypeDef *hcan, CAN_RxHeaderTypeDef rx_header, uint8_t *rx_data);


private:
    CAN_HandleTypeDef *_local_can;

    uint32_t _tx_id;
    uint32_t _tx_ide;
    uint32_t _tx_rtr;
    uint32_t _tx_dlc;
    uint8_t *_tx_buf;

    uint32_t _rx_id;
    uint8_t *_rx_buf;

    void (*rxUserCallback)(uint8_t *rx_buf){};
};


#endif //LCAN_H
