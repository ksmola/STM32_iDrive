#include "bmw_idrive.h"
#include "stdbool.h"

void Send_IGN_Status(uint8_t status, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox)
{
	TxHeader->DLC = 8;
	TxHeader->StdId = CAN_ID_IGN_STATUS;
	TxMailbox = 0;

	switch (status)
	{
	case 0: //Key in the ignition but all systems are off (i.e. no time or dash display visible)
		TxData[0] = 0x00;
		TxData[1] = 0x00;
		TxData[2] = 0x3F;
		break;
	case 1: //Key in the ignition and the system is in standby (If the clutch was pressed the car could start)
		TxData[0] = 0x00;
		TxData[1] = 0x40;
		TxData[2] = 0x7F;
		break;
	case 2: //Key in the ignition the engine is running (or start button has been pressed without foot on the clutch)
		TxData[0] = 0x40;
		TxData[1] = 0x40;
		TxData[2] = 0x7F;
		break;
	default:
		break;
	}

	TxData[3] = 0x50;
	TxData[4] = 0xFF;
	TxData[5] = 0xFF;
	TxData[6] = 0xFF;
	TxData[7] = 0xFF;
}

void Send_IGN_KEY_Status(uint8_t status, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox)
{
	TxHeader->DLC = 5;
	TxHeader->StdId = CAN_ID_IGN_KEY_STATUS;
	TxMailbox = 0;

	switch (status)
	{
	case 0:
		TxData[0] = 0x00;
		break;
	case 1:
		TxData[0] = 0x40;
		break;
	case 2:
		TxData[0] = 0x41;
		break;
	case 3:
		TxData[0] = 0x45;
		break;
	case 4:
		TxData[0] = 0x55;
	default:
		break;
	}

	switch (status)
	{
	case 0:
		TxData[1] = 0x00;
	case 1:
	case 2:
	case 3:
	case 4:
		TxData[1] = 0x42;
		//		TxData[1] = 0x40;
		break;
	default:
		break;
	}

	TxData[2] = 0x69;
	//    TxData[2] = 0x21;
	TxData[3] = 0x8F;
	TxData[4] = 0xE2; //counter
	//    TxData[4] = 0x50; //counter
}

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

void Set_MPH(uint16_t *mph, uint16_t *counter, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox)
{
	TxHeader->DLC = 8;
	TxHeader->StdId = CAN_ID_MPH;
	TxMailbox = 0;

	TxData[0] = *mph & 0xFF;
	TxData[1] = *mph >> 8;

	TxData[2] = *mph & 0xFF;
	TxData[3] = *mph >> 8;

	TxData[4] = *mph & 0xFF;
	TxData[5] = *mph >> 8;

	TxData[6] = *counter & 0xFF;
	TxData[7] = (*counter >> 8) | 0xF0;
}

void Set_Signals(uint8_t status, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox)
{
	TxHeader->DLC = 2;
	TxHeader->StdId = CAN_ID_SIGNALS;
	TxMailbox = 0;

	switch (status)
	{
	case 0: //Indicators Off (sent once)
		TxData[0] = 0x80;
		TxData[1] = 0xF0;
		break;
	case 1: // Left turn signal (sent after F2)
		TxData[0] = 0x91;
		TxData[1] = 0xF1;
		break;
	case 2: // Left turn signal (sent before F1)
		TxData[0] = 0x91;
		TxData[1] = 0xF2;
		break;
	case 3: // Right turn signal (sent after F2)
		TxData[0] = 0xA1;
		TxData[1] = 0xF1;
		break;
	case 4: // Right turn signal (sent before F1)
		TxData[0] = 0xA1;
		TxData[1] = 0xF2;
		break;
	case 5: // Hazzard Lights on (sent after F2)
		TxData[0] = 0xB1;
		TxData[1] = 0xF1;
		break;
	case 6: // Hazzard Lights on (sent before F1)
		TxData[0] = 0xB1;
		TxData[1] = 0xF2;
		break;
	default:
		break;
	}
}

void Set_Error(uint16_t signal, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox)
{
	TxHeader->DLC = 8;
	TxHeader->StdId = CAN_ID_ERROR;
	TxMailbox = 0;

	TxData[0] = 0x40;
	TxData[1] = signal;

	// TxData[2] = (signal >> 8) | 0xF0;
	TxData[2] = 0x00;
	TxData[3] = 0x30;

	TxData[4] = 0xFF;
	TxData[5] = 0xFF;
	TxData[6] = 0xFF;
	TxData[7] = 0xFF;
}

void Set_Fuel(uint8_t percent, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox)
{
	int val;
	val = percent * 99.97;
	if (val > 9997)
		val = 9997;

	TxHeader->DLC = 5;
	TxHeader->StdId = CAN_ID_FUEL;
	TxMailbox = 0;

	TxData[0] = val & 0xFF;
	TxData[1] = val >> 8;
	TxData[2] = val & 0xFF;
	TxData[3] = val >> 8;

	TxData[4] = 0x00;
}

void Set_Temp(uint16_t temp, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox)
{

	float temp_f;
	if (temp < 160)
		temp = 160;
	if (temp > 340)
		temp = 340;
	temp_f = (temp - 32) * 0.5556;
	temp = (int)temp_f + 49;

	TxHeader->DLC = 8;
	TxHeader->StdId = CAN_ID_TEMP;
	TxMailbox = 0;

	TxData[0] = 0xFF; // coolant temp
	TxData[1] = temp; // oil temp
	TxData[2] = 0x63;
	TxData[3] = 0xCD;

	TxData[4] = 0x5D;
	TxData[5] = 0x37;
	TxData[6] = 0xCD;
	TxData[7] = 0xA8;
}

void Set_Lights(uint8_t val, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox)
{
	TxHeader->DLC = 3;
	TxHeader->StdId = CAN_ID_LIGHTS;
	TxMailbox = 0;

	TxData[0] = 0x85;
	TxData[1] = 0x12;
	TxData[2] = 0xF7;
}

void Set_Light_Switch(uint8_t val, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox)
{
	TxHeader->DLC = 2;
	TxHeader->StdId = 0x1E3;
	TxMailbox = 0;

	if (val)
		TxData[0] = 0xF1;
	else
		TxData[0] = 0xF0;

	TxData[1] = 0xFF;
}

void Set_Seatbelt_Light(uint8_t val, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox) //not working?
{
	TxHeader->DLC = 8;

	if (val)
		TxHeader->StdId = CAN_ID_SEATBELT_ON;
	else
		TxHeader->StdId = CAN_ID_SEATBELT_OFF;

	TxMailbox = 0;

	TxData[0] = 0x40;
	TxData[1] = 0x4D;
	TxData[2] = 0x00;

	if (val)
		TxData[3] = 0x29;
	else
		TxData[3] = 0x28;

	TxData[4] = 0xFF;
	TxData[5] = 0xFF;
	TxData[6] = 0xFF;
	TxData[7] = 0xFF;
}

void Set_ABS(uint8_t val, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox)
{
	TxHeader->DLC = 8;
	TxHeader->StdId = CAN_ID_ABS;
	TxMailbox = 0;

	TxData[0] = 0x00;
	TxData[1] = 0xE0;
	TxData[2] = 0xB3;
	TxData[3] = 0xFC;
	TxData[4] = 0xF0;
	TxData[5] = 0x00;
	TxData[6] = 0x00;
	TxData[7] = 0x65;
}

void Set_ABS_2(uint8_t *abs_counter, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox)
{

	TxHeader->DLC = 2;
	TxHeader->StdId = CAN_ID_ABS_2;
	TxMailbox = 0;

	TxData[0] = 0xF0 + *abs_counter;
	TxData[1] = 0xFF;
}

void Set_Counter(uint8_t *counter, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox)
{
	TxHeader->DLC = 2;
	TxHeader->StdId = CAN_ID_COUNTER;
	TxMailbox = 0;

	TxData[0] = *counter;
	TxData[1] = 0xFF;
}

void Set_DSC(uint8_t *speed, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox)
{
	uint8_t c_speed;
	c_speed = *speed * 730;

	TxHeader->DLC = 8;
	TxHeader->StdId = CAN_ID_DSC;
	TxMailbox = 0;

	TxData[0] = c_speed & 0xFF;
	TxData[1] = c_speed >> 8;
	TxData[2] = c_speed & 0xFF;
	TxData[3] = c_speed >> 8;
	TxData[4] = c_speed & 0xFF;
	TxData[5] = c_speed >> 8;
	TxData[6] = c_speed & 0xFF;
	TxData[7] = c_speed >> 8;
}
void Set_Steeringwheel_pos(uint16_t *pos, CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox)
{
	TxHeader->DLC = 6;
	TxHeader->StdId = CAN_ID_STEERINGPOS;
	TxMailbox = 0;

	TxData[0] = *pos & 0xFF;
	TxData[1] = *pos >> 8;
	TxData[2] = 0xFC;
	TxData[3] = 0x00;
	TxData[4] = 0x00;
	TxData[5] = 0xFF;
}

void Set_Time(CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *TxHeader, uint8_t TxData[], uint32_t *TxMailbox)
{
	TxHeader->DLC = 8;
	TxHeader->StdId = CAN_ID_SET_TIME;
	TxMailbox = 0;

	TxData[0] = 0x09;
	TxData[1] = 0x2C;
	TxData[2] = 0x00;
	TxData[3] = 0x09;
	TxData[4] = 0x4F;
	TxData[5] = 0xDF;
	TxData[6] = 0x07;
	TxData[6] = 0xF2;
}
