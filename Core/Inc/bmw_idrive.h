#include <stdint.h>
#include "main.h"

#ifndef __BMW_IDRIVE_H
#define __BMW_IDRIVE_H
#endif

#define CAN_ID_RPM      0x0AA
#define CAN_ID_MPH      0x1A6


void Set_RPM(uint16_t rpm, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_MPH(uint16_t mph, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
