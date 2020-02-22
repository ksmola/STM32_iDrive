#include "bmw_idrive.h"
#include "stdbool.h"

void Set_RPM(uint16_t rpm, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox)
{
    TxHeader->DLC = 8;
    TxHeader->StdId = CAN_ID_RPM;
    TxMailbox = 0;

    TxData[0] = 0x5F;
    TxData[1] = 0x59;

    TxData[2] = 0xFF; //TPS
    TxData[3] = 0x00; //TPS

    TxData[4] = (rpm << 2) & 0xFF;
    TxData[5] = (rpm) >> 6; 
    
    TxData[6] = 0x80; //not needed?
    TxData[7] = 0x99; //not needed?
}

void Set_MPH(uint16_t mph, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox)
{
    TxHeader->DLC = 8;
    TxHeader->StdId = CAN_ID_MPH;
    TxMailbox = 0;

}
