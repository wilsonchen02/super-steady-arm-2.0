/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* Given servo ID and an angle from range 0-1000 of the servo's software limits,
 * move the servo to the corresponding angle
 * @param servo_id: servo to move
 * @param angle: angle metric range 0-1000 that the servo is to go to
 */
void servo_write(uint16_t servo_id, int angle) {
	if (angle > 1000 || angle < 0) {
//		throw std::runtime_error("angle out of range");
	}
	float angle_ratio = angle / 1000.0;
	uint16_t angle_low = angle & 0xFF;
	uint16_t angle_high = (angle >> 8) & 0xFF;
	// This should constrain sum to 16 bits
	uint16_t sum = servo_id + angle_low + angle_high + 0x7 + 0x1;
	sum = ~sum & 0xFF;
	uint8_t tx_buf[10] = {0x55, 0x55, servo_id, 0x7, 0x1, angle_low, angle_high, 0x0, 0x0, sum};
	HAL_UART_Transmit(&huart1, tx_buf[0], 10, 50);
}

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
  MX_USART1_UART_Init();
//  HAL_Delay(10);
  /* USER CODE BEGIN 2 */

  // TESTING UART message

  HAL_Delay(1000);
//  uint8_t tx_buf[10] = {0x55, 0x55, 0x06, 0x07, 0x01, 0x1E, 0x88, 0x08, 0x00, 0x4B};
  uint8_t tx_buf[4][10] = {
  // 0 and 1000 for motor 6 joint A (like 70 degrees?)
  {0x55, 0x55, 0x06, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0xF1},
  {0x55, 0x55, 0x06, 0x07, 0x01, 0xe8, 0x03, 0x00, 0x00, 0x06},
  {0x55, 0x55, 0x03, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0xF4},
  {0x55, 0x55, 0x03, 0x07, 0x01, 0xe8, 0x03, 0x00, 0x00, 0x09}
  };

  servo_write(3, 1000);
  HAL_Delay(1000);
//  uint8_t tx_buf0[0] = {0x55, 0x55, 0x06, 0x07, 0x01, 0x1E, 0x00, 0x00, 0x00, 0xD3};	// id6
//  uint8_t tx_buf1[1] = {0x55, 0x55, 0x06, 0x07, 0x01, 0x, 0x00, 0x00, 0x00, 0xD3};
//  uint8_t tx_buf[10] = {0x00, 0x00, 0x00, 0x07, 0x01, 0x1E, 0x00, 0x00, 0x00, 0xD3};

//  HAL_UART_Transmit(&huart1, tx_buf[2], 10, 50);
//	HAL_Delay(1000);
//	HAL_UART_Transmit(&huart1, tx_buf[3], 10, 50);
//	HAL_Delay(1000);
//  HAL_UART_Transmit(&huart1, tx_buf[2], 10, 50);
//  HAL_Delay(1000);
//  HAL_UART_Transmit(&huart1, tx_buf[3], 10, 50);
//  HAL_Delay(1000);


//  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
//  if(HAL_UART_Transmit(&huart1, tx_buf0, 10, 50) == HAL_ERROR) {
//	  // Enable GPIO
//	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 1);
//  }
//  HAL_Delay(200);
//  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, 0);
//  tx_buf[0] = 0xFF;
//  HAL_UART_Transmit(&huart1, tx_buf, 10, 50);
//  tx_buf[0] = 0x00;
//  HAL_UART_Transmit(&huart1, tx_buf, 10, 50);


//  int counter = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
  }
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
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
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
