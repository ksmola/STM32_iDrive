#include <stdint.h>
#include "main.h"

#ifndef __BMW_IDRIVE_H
#define __BMW_IDRIVE_H
#endif

#define UPDATE_100HZ		HAL_GetTick() >= (time_100hz + 10)
#define UPDATE_10HZ			HAL_GetTick() >= (time_10hz + 100)
#define UPDATE_5HZ			HAL_GetTick() >= (time_5hz + 200)

#define CAN_ID_RPM      		0x0AA
#define CAN_ID_MPH      		0x1A6
#define CAN_ID_IGN_KEY_STATUS	0x130
#define CAN_ID_IGN_STATUS   	0x26E
#define CAN_ID_SIGNALS			0x1F6
#define CAN_ID_ERROR			0x592

void Send_IGN_Status(uint8_t status, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Send_IGN_Key_Status(uint8_t status, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_RPM(uint16_t rpm, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_MPH(uint16_t mph, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_Signals(uint8_t status, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_Error(uint8_t signal, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
