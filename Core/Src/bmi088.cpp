//
// Created by chenyincheng on 2025/10/12.
//
#include "bmi088.h"
#include "main.h"
#include "spi.h"
#include "gpio.h"

//uint8_t acel[6];
//uint8_t ac[6];


void bmi088_write_byte(uint8_t tx_data) {
  HAL_SPI_Transmit(&hspi1, &tx_data, 1, 1000);
  // while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_TX);
}
void bmi088_read_byte(uint8_t *rx_data, uint8_t length){
  HAL_SPI_Receive(&hspi1, rx_data, length, 1000);
  // while (HAL_SPI_GetState(&hspi1) == HAL_SPI_STATE_BUSY_RX);
};

void bmi088_write_reg(uint8_t reg, uint8_t data){
  bmi088_write_byte(reg & 0x7F);//注意后面的位运算符，将reg的最高位设置为0，以便写入寄存器
  bmi088_write_byte(data);
}; // 向寄存器中写入数据，可参考5.3，5.4寄存器写入方 法，先写首位判别符+地址，再写data



void BMI088_ACCEL_NS_L(void) {
  HAL_GPIO_WritePin(CS1_ACCEL_GPIO_Port, CS1_ACCEL_Pin, GPIO_PIN_RESET);
}
void BMI088_ACCEL_NS_H(void){
  HAL_GPIO_WritePin(CS1_ACCEL_GPIO_Port, CS1_ACCEL_Pin, GPIO_PIN_SET);
};
void BMI088_GYRO_NS_L(void){
  HAL_GPIO_WritePin(CS1_GYRO_GPIO_Port, CS1_GYRO_Pin, GPIO_PIN_RESET);
};
void BMI088_GYRO_NS_H(void){
  HAL_GPIO_WritePin(CS1_GYRO_GPIO_Port, CS1_GYRO_Pin, GPIO_PIN_SET);
};


// 参考: acc写入，相当于加上片选的 bmi088_write_reg 函数
void bmi088_accel_write_single_reg(uint8_t reg, uint8_t data) {
  BMI088_GYRO_NS_H();
  BMI088_ACCEL_NS_L();

  bmi088_write_byte(reg & 0x7F);
  bmi088_write_byte(data);

  BMI088_ACCEL_NS_H();
}

// 尝试完成 ↓
void bmi088_accel_read_reg(uint8_t reg, uint8_t *rx_data, uint8_t length){
  BMI088_GYRO_NS_H();
  BMI088_ACCEL_NS_L();

  uint8_t dummy_byte ;
  bmi088_write_byte(reg | 0x80);
  bmi088_read_byte(&dummy_byte, 1);
  bmi088_read_byte(rx_data, length);

  BMI088_ACCEL_NS_H();

}; // 加速度计读取，注意需要忽略第一位数据dummy byte


void bmi088_gyro_read_reg(uint8_t reg, uint8_t *rx_data, uint8_t length){
  BMI088_ACCEL_NS_H();
  BMI088_GYRO_NS_L();
  bmi088_write_byte(reg | 0x80);
  bmi088_read_byte(rx_data, length);
  BMI088_GYRO_NS_H();


};// 陀螺仪读取

void bmi088_gyro_write_single_reg(uint8_t reg, uint8_t tx_data){
  BMI088_ACCEL_NS_H();
  BMI088_GYRO_NS_L();
  bmi088_write_byte(reg & 0x7F);
  bmi088_write_byte(tx_data);
  BMI088_GYRO_NS_H();

} // gyro写入

void bmi088_init(void) {
  // Soft Reset ACCEL
  BMI088_ACCEL_NS_L();
  bmi088_write_reg(0x7E, 0xB6); // Write 0xB6 to ACC_SOFTRESET(0x7E)
  HAL_Delay(1);
  BMI088_ACCEL_NS_H();

  // Soft Reset GYRO
  BMI088_GYRO_NS_L();
  bmi088_write_reg(0x14, 0xB6); // Write 0xB6 to GYRO_SOFTRESET(0x14)
  HAL_Delay(30);
  BMI088_GYRO_NS_H();

  // Switch ACCEL to Normal Mode
  BMI088_ACCEL_NS_L();
  HAL_Delay(1);
  bmi088_write_reg(0x7D, 0x04); // Write 0x04 to ACC_PWR_CTRL(0x7D)
  HAL_Delay(1);
  BMI088_ACCEL_NS_H();
}