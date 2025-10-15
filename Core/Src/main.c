/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "spi.h"
#include "tim.h"
#include "gpio.h"
#include "imu.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bmi088.h"
#include <stdio.h>

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

/* USER CODE BEGIN PV */
//
uint8_t acel[6];
uint8_t ac[6];
//// 尝试完成 ↓
//void bmi088_write_byte(uint8_t tx_data) {
//  HAL_SPI_Transmit(&hspi1, &tx_data, 1, 1000);
//  // while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX);
//}
//void bmi088_read_byte(uint8_t *rx_data, uint8_t length){
//  HAL_SPI_Receive(&hspi1, rx_data, length, 1000);
//  // while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_RX);
//};
//
//void bmi088_write_reg(uint8_t reg, uint8_t data){
//  bmi088_write_byte(reg & 0x7F);//注意后面的位运算符，将reg的最高位设置为0，以便写入寄存器
//  bmi088_write_byte(data);
//}; // 向寄存器中写入数据，可参考5.3，5.4寄存器写入方 法，先写首位判别符+地址，再写data
//
//
//
//void BMI088_ACCEL_NS_L(void) {
//  HAL_GPIO_WritePin(CS1_ACCEL_GPIO_Port, CS1_ACCEL_Pin, GPIO_PIN_RESET);
//}
//void BMI088_ACCEL_NS_H(void){
//  HAL_GPIO_WritePin(CS1_ACCEL_GPIO_Port, CS1_ACCEL_Pin, GPIO_PIN_SET);
//};
//void BMI088_GYRO_NS_L(void){
//  HAL_GPIO_WritePin(CS1_GYRO_GPIO_Port, CS1_GYRO_Pin, GPIO_PIN_RESET);
//};
//void BMI088_GYRO_NS_H(void){
//  HAL_GPIO_WritePin(CS1_GYRO_GPIO_Port, CS1_GYRO_Pin, GPIO_PIN_SET);
//};
//
//
//// 参考: acc写入，相当于加上片选的 bmi088_write_reg 函数
//void bmi088_accel_write_single_reg(uint8_t reg, uint8_t data) {
//  BMI088_GYRO_NS_H();
//  BMI088_ACCEL_NS_L();
//
//  bmi088_write_byte(reg & 0x7F);
//  bmi088_write_byte(data);
//
//  BMI088_ACCEL_NS_H();
//}
//
//// 尝试完成 ↓
//void bmi088_accel_read_reg(uint8_t reg, uint8_t *rx_data, uint8_t length){
//  BMI088_GYRO_NS_H();
//  BMI088_ACCEL_NS_L();
//
//  uint8_t dummy_byte ;
//  bmi088_write_byte(reg | 0x80);
//  bmi088_read_byte(&dummy_byte, 1);
//  bmi088_read_byte(rx_data, length);
//
//  BMI088_ACCEL_NS_H();
//
//}; // 加速度计读取，注意需要忽略第一位数据dummy byte
//
//
//void bmi088_gyro_read_reg(uint8_t reg, uint8_t *rx_data, uint8_t length){
//  BMI088_ACCEL_NS_H();
//  BMI088_GYRO_NS_L();
//  bmi088_write_byte(reg | 0x80);
//  bmi088_read_byte(rx_data, length);
//  BMI088_GYRO_NS_H();
//
//
//};// 陀螺仪读取
//
//void bmi088_gyro_write_single_reg(uint8_t reg, uint8_t tx_data){
//  BMI088_ACCEL_NS_H();
//  BMI088_GYRO_NS_L();
//  bmi088_write_byte(reg & 0x7F);
//  bmi088_write_byte(tx_data);
//  BMI088_GYRO_NS_H();
//
//} // gyro写入




/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//IMU imu2;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
  int gyro = 0;



//  int s = imu2.got_data();
//  int s = imu2.got_data();

//    bmi088_init();
//    bmi088_accel_write_single_reg(0x11, 0x01); // Enable Accel
//    bmi088_gyro_write_single_reg(0x11, 0x01); // Enable Gyro
//    bmi088_accel_write_single_reg(0x12, 0x00); // Set Accel Range to 2G
//    bmi088_gyro_write_single_reg(0x12, 0x00); // Set Gyro Range to 2000dps
//    while (1) {
//      // Read Accel
//      BMI088_ACCEL_NS_L();
//      bmi088_accel_read_reg(0x02, (uint8_t*)&acel, 6); // Read 6 bytes of Accel data
//      BMI088_ACCEL_NS_H();
//      acel = (int16_t)((acel[1] << 8) | acel[0]); // Combine two bytes to form 16-bit signed int
//      acel = acel >> 4; // Right-shift 4 bits to get 10-bit signed int
//
//      // Read Gyro
//      BMI088_GYRO_NS_L();
//      bmi088_gyro_read_reg(0x02, (uint8_t*)&gyro, 6); // Read 6 bytes of Gyro data
//      BMI088_GYRO_NS_H();
//      gyro = (int16_t)((gyro[1] << 8) | gyro[0]); // Combine two bytes to form 16-bit signed int
//      gyro = gyro >> 4; // Right-shift 4 bits to get 10-bit signed int



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
  MX_SPI1_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */
  bmi088_init();
//  HAL_TIM_Base_Start_IT(&htim6); // Start timer for 1ms interrupt

  // 在main.c中获取IMU对象句柄
  void* imu_handle = (void *)imu_get_handle();

  // 使用句柄调用加速度计算函数



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//    HAL_Delay(10);
    bmi088_accel_read_reg(0x12, acel, 6); // Read 6 bytes of Accel data
    bmi088_gyro_read_reg(0x02, ac, 6); // Read 6 bytes of Gyro data
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    float* acceleration = imu_acc_calculate(imu_handle);
    float acc_x = acceleration[0];  // X轴加速度
    float acc_y = acceleration[1];  // Y轴加速度
    float acc_z = acceleration[2];  // Z轴加速度
    float* gyroscope = imu_gyro_calculate(imu_handle);
    float gyro_x = gyroscope[0];  // X轴角速度
    float gyro_y = gyroscope[1];  // Y轴角速度
    float gyro_z = gyroscope[2];  // Z轴角速度
    // 打印角速度值（通过串口输出）

    // 打印加速度值（通过串口输出）
    printf("加速度值: X=%.3fg, Y=%.3fg, Z=%.3fg\n",
           acc_x, acc_y, acc_z);
    HAL_Delay(100);


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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
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
#ifdef USE_FULL_ASSERT
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
