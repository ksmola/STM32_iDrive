/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;

/* USER CODE BEGIN PV */
CAN_FilterTypeDef	sFilterConfig;
CAN_TxHeaderTypeDef	TxHeader;
CAN_RxHeaderTypeDef RxHeader;
uint8_t				TxData[8];
uint8_t				RxData[8];
uint32_t			TxMailbox;

uint32_t time_1p5hz;
uint32_t time_2hz;
uint32_t time_5hz;
uint32_t time_10hz;
uint32_t time_100hz;

uint32_t rpmcount;
uint32_t current_time;
uint32_t light_timer;
uint32_t abs_timer;
uint8_t abs_counter;
uint16_t mph_counter;
uint32_t mph_timer;
uint16_t mph_last;

bool turnsignal_left;
bool lights_on;

uint32_t rpmcount;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */
//  TxHeader.DLC = 8;
//  TxHeader.StdId = 0x501;
//  TxData[0] = 0x01;
//  TxData[1] = 0x00;
//  TxData[2] = 0x00;
//  TxData[3] = 0x00;
//  TxData[4] = 0x00;
//  TxData[5] = 0x00;
//  TxData[6] = 0x00;
//  TxData[7] = 0x00;
//
//  TxMailbox = 0;


//  Send_IGN_KEY_Status(3, &hcan, &TxHeader, &TxData, &TxMailbox);
//  Set_Light_Switch(1, &hcan, &TxHeader, &TxData, &TxMailbox);
//  if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
//  {
//	  Error_Handler();
//  }
//  light_timer = HAL_GetTick();

  time_100hz = HAL_GetTick();
  time_10hz = HAL_GetTick();
  time_5hz = HAL_GetTick();
  time_2hz = HAL_GetTick();
  time_1p5hz = HAL_GetTick();
  abs_timer = HAL_GetTick();

  turnsignal_left = false;
  lights_on = false;
  rpmcount = 500;
  abs_counter = 0;
  mph_counter = 0;
  mph_last = 0;
  mph_timer = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if (UPDATE_5HZ) //updates every 200ms
	  {
		  Send_IGN_Status(2, &hcan, &TxHeader, &TxData, &TxMailbox);
		  if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
		  {
			  Error_Handler();
		  }


		  time_5hz = HAL_GetTick();
	  }

	  if (UPDATE_10HZ) //updates every 100ms
	  {
		  Send_IGN_KEY_Status(3, &hcan, &TxHeader, &TxData, &TxMailbox); //T15
		  if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
		  {
			  Error_Handler();
		  }

		  Set_Fuel(40, &hcan, &TxHeader, &TxData, &TxMailbox);
		  if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
		  {
			  Error_Handler();
		  }
		  Set_Temp(250, &hcan, &TxHeader, &TxData, &TxMailbox);
		  if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
		  {
			  Error_Handler();
		  }
		  Send_Speed_Msg();
//		  Set_Seatbelt_Light(0, &hcan, &TxHeader, &TxData, &TxMailbox);
//		  if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
//		  {
//			  Error_Handler();
//		  }
//		  Set_ABS(0, &hcan, &TxHeader, &TxData, &TxMailbox);
//		  if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
//		  {
//			  Error_Handler();
//		  }
//
//		  if (HAL_GetTick() >= (abs_timer + 200))
//		  {
//			  abs_counter ++;
//			  abs_timer = HAL_GetTick();
//		  }
//		  if (abs_counter > 15)
//			  abs_counter = 0;
//		  Set_ABS_2(&abs_counter,  &hcan, &TxHeader, &TxData, &TxMailbox);
//		  if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
//		  {
//			  Error_Handler();
//		  }

		  time_10hz = HAL_GetTick();
	  }

//	  if (UPDATE_100HZ) //updates every 10ms
//	  {
//		  Set_RPM(rpmcount, &hcan, &TxHeader, &TxData, &TxMailbox);
//		  if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
//		  {
//			  Error_Handler();
//		  }
//		  rpmcount++;
//		  if (rpmcount > 7000)
//			  rpmcount = 0;
//		  time_100hz = HAL_GetTick();
//	  }

	  if (UPDATE_2HZ)
	  {
		  Set_Error(207, &hcan, &TxHeader, &TxData, &TxMailbox);
		  if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
		  {
			  Error_Handler();
		  }

		  Set_Error(281, &hcan, &TxHeader, &TxData, &TxMailbox);
		  if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
		  {
			  Error_Handler();
		  }

		  Set_Error(60, &hcan, &TxHeader, &TxData, &TxMailbox);
		  if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
		  {
			  Error_Handler();
		  }
		  Set_Error(167, &hcan, &TxHeader, &TxData, &TxMailbox);
		  if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
		  {
			  Error_Handler();
		  }
		  Set_Error(97, &hcan, &TxHeader, &TxData, &TxMailbox);
		  if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
		  {
			  Error_Handler();
		  }
		  Set_Error(300, &hcan, &TxHeader, &TxData, &TxMailbox);
		  if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
		  {
			  Error_Handler();
		  }

		  time_2hz = HAL_GetTick();
	  }

	  if(HAL_GPIO_ReadPin(GPIOA, LIGHT_Pin)==1)
	  {
		  if (!lights_on)
		  {
			  Set_Lights(1, &hcan, &TxHeader, &TxData, &TxMailbox); //this might need to be repeated as lights otherwise turn off after a few seconds
			  if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
			  {
				  Error_Handler();
			  }
			  lights_on = true;
		  }

	  }
	  if(HAL_GPIO_ReadPin(GPIOA, TURN_LEFT_Pin)==1)
	  {
		  if (UPDATE_1P5HZ)
		  {
			  Turnsignal_Left();
			  time_1p5hz = HAL_GetTick();
		  }
	  }

	  if(HAL_GPIO_ReadPin(GPIOA, TURN_RIGHT_Pin)==1)
	  {
		  if (UPDATE_1P5HZ)
		  {
			  Turnsignal_Right();
			  time_1p5hz = HAL_GetTick();
		  }

	  }


  }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 20;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_16TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */
  sFilterConfig.FilterBank = 0; // 0..13 for CAN1, 14..27 for CAN2
  //sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  sFilterConfig.SlaveStartFilterBank = 14;
  sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
  sFilterConfig.FilterIdHigh = 0x0000;
  sFilterConfig.FilterIdLow = 0x0000;
  sFilterConfig.FilterMaskIdHigh = 0x0000;
  sFilterConfig.FilterMaskIdLow = 0x0000;
  sFilterConfig.FilterActivation = ENABLE;
  if (HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK)
  {
    /* Filter configuration Error */
    Error_Handler();
  }
  // now start the can peripheral
  if (HAL_CAN_Start(&hcan) != HAL_OK)
  {
  	Error_Handler();
  }
  // activate CAN RX IRQ
  if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
  {
  	Error_Handler();
  }
  // send test message
//   TxHeader.DLC = 8;
//   TxHeader.StdId = 0x273;
//   TxData[0] = 0x1D;
//   TxData[1] = 0xE1;
//   TxData[2] = 0x00;
//   TxData[3] = 0xF0;
//   TxData[4] = 0xFF;
//   TxData[5] = 0x7F;
//   TxData[6] = 0xDE;
//   TxData[7] = 0x04;
//   TxMailbox = 0;
//
//   if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
//   {
//   	Error_Handler();
//   }
//
//   HAL_Delay(250);
//
//   if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
//   {
//	   Error_Handler();
//   }

  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LIGHT_Pin TURN_LEFT_Pin TURN_RIGHT_Pin */
  GPIO_InitStruct.Pin = LIGHT_Pin|TURN_LEFT_Pin|TURN_RIGHT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void Compose_CAN_msg(uint8_t offset, uint8_t mtype, uint8_t fromid, uint8_t toid, uint8_t table, uint8_t length, uint64_t data)
{
//  TxData[0] = AFR_to_ADC_counts(o2_sensor[0].AFR) >> 8;
//  TxData[1] = AFR_to_ADC_counts(o2_sensor[0].AFR) & 0xFF;
//  TxData[2] = AFR_to_ADC_counts(o2_sensor[1].AFR) >> 8;
//  TxData[3] = AFR_to_ADC_counts(o2_sensor[1].AFR) & 0xFF;
//  TxData[4] = AFR_to_ADC_counts(o2_sensor[2].AFR) >> 8;
//  TxData[5] = AFR_to_ADC_counts(o2_sensor[2].AFR) & 0xFF;
//  TxData[6] = AFR_to_ADC_counts(o2_sensor[3].AFR) >> 8;
//  TxData[7] = AFR_to_ADC_counts(o2_sensor[3].AFR) & 0xFF;
  // TxData[2] = o2_sensor.function_code >> 8;
  // TxData[3] = o2_sensor.function_code & 0xFF;
  // TxData[4] = o2_sensor.warmup >> 8;
  // TxData[5] = o2_sensor.warmup & 0xFF;
  // TxData[6] = o2_sensor.error_code >> 8;
  // TxData[7] = o2_sensor.error_code & 0xFF;
//  TxHeader.DLC = length;
//  TxMailbox = 0;
//  TxHeader.ExtId = (offset << 18) | (mtype << 15) | (fromid << 11) | (toid << 7) | (table << 3);
//  TxHeader.IDE = CAN_ID_EXT;
//  if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
//  {
//    Error_Handler();
//  }
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) != HAL_OK)
	{
		Error_Handler();
	}
	else
	{
//		Parse_CAN_data();
		//got valid can data
	}
}

void Turnsignal_Left()
{
		Set_Signals(2, &hcan, &TxHeader, &TxData, &TxMailbox);
		if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
		{
			Error_Handler();
		}
		Set_Signals(1, &hcan, &TxHeader, &TxData, &TxMailbox);
		if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
		{
			Error_Handler();
		}
}

void Turnsignal_Right()
{
		Set_Signals(4, &hcan, &TxHeader, &TxData, &TxMailbox);
		if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
		{
			Error_Handler();
		}
		Set_Signals(3, &hcan, &TxHeader, &TxData, &TxMailbox);
		if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
		{
			Error_Handler();
		}
}

void Send_Speed_Msg()
{
	uint16_t mph, mph_a, mph_2a;
	mph = 20;

	mph_a = (((HAL_GetTick()-mph_timer)/50)*mph/2);
	mph_2a = mph_a + mph_last;
	mph_last = mph_2a;
	mph_timer = HAL_GetTick();

	Set_MPH(&mph_2a, &mph_counter,&hcan, &TxHeader, &TxData, &TxMailbox);
	if (HAL_CAN_AddTxMessage(&hcan, &TxHeader, &TxData, &TxMailbox) != HAL_OK)
	{
		Error_Handler();
	}

	mph_counter += 200;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	printf("ERROR!");

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
