#include <stdint.h>
#include "main.h"

#ifndef __BMW_IDRIVE_H
#define __BMW_IDRIVE_H
#endif

#define UPDATE_100HZ		HAL_GetTick() >= (time_100hz + 10)
#define UPDATE_10HZ			HAL_GetTick() >= (time_10hz + 100)
#define UPDATE_5HZ			HAL_GetTick() >= (time_5hz + 200)
#define UPDATE_2HZ			HAL_GetTick() >= (time_2hz + 500)
#define UPDATE_1P5HZ		HAL_GetTick() >= (time_1p5hz + 750)
#define UPDATE_TURNSIGNAL   HAL_GetTick() >= (time_turnsignal + 580) //~1.72Hz

#define UPDATE_1SEC         HAL_GetTick() >= (time_init + 1000)
#define UPDATE_2SEC         HAL_GetTick() >= (time_init + 2000)
#define UPDATE_LIGHTS       HAL_GetTick() >= (time_lights + 5000)

#define CAN_ID_RPM      		0x0AA
#define CAN_ID_MPH      		0x1A6
#define CAN_ID_IGN_KEY_STATUS	0x130
#define CAN_ID_IGN_STATUS   	0x26E
#define CAN_ID_SIGNALS			0x1F6
#define CAN_ID_ERROR			0x592
#define CAN_ID_FUEL				0x349
#define CAN_ID_TEMP				0x1D0
#define CAN_ID_DIMMER			0x202
#define CAN_ID_LIGHTS			0x21A
#define CAN_ID_SEATBELT_OFF 	0x581
#define CAN_ID_SEATBELT_ON  	0x394
#define CAN_ID_ABS			  	0x19E
#define CAN_ID_ABS_2			0x0C0
#define CAN_ID_COUNTER			0x0D7
#define CAN_ID_DSC  			0x0CE
#define CAN_ID_STEERINGPOS      0x0C8
#define CAN_ID_SET_TIME         0x39E
#define CAN_ID_EBRAKE           0x34F

void Send_IGN_Status(uint8_t status, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Send_IGN_Key_Status(uint8_t status, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_RPM(uint16_t rpm, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_MPH(uint16_t *mph, uint16_t *counter, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_Signals(uint8_t status, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_Error(uint16_t signal, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_Fuel(uint8_t percent, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_Temp(uint16_t temp, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_Lights(uint8_t val, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_Light_Switch(uint8_t val, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_Seatbelt_Light(uint8_t val, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_ABS(uint8_t val, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_ABS_2(uint8_t abs_counter, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_Counter(uint8_t counter, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_DSC(uint8_t *speed, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_Steeringwheel_pos(uint16_t *pos, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_Time(CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_Ebrake(uint8_t status, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);
void Set_Dimmer(uint8_t val, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox);