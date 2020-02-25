#include <stdint.h>
#include "main.h"

#ifndef __BMW_IDRIVE_H
#define __BMW_IDRIVE_H
#endif

//#define CAN_10HZ				10
//#define CAN_100HZ				100

#define CAN_UPDATE_IGN_STATUS	HAL_GetTick() >= (time_IGN_KEY + 100)
#define CAN_UPDATE_RPM			HAL_GetTick() >= (time_RPM + 100)

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
