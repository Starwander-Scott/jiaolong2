//
// Created by chenyincheng on 2025/10/12.
//
#include "main.h"
#include "bmi088.h"

#ifndef C1_IMU_H
#define C1_IMU_H

#ifdef __cplusplus

#include <iostream>
class IMU {
public:

  IMU();
  ~IMU();
  float* acc_calculate();
  float* gyro_calculate();
//  float get_acc_x() const { return acceleration[0]; }
//  float get_acc_y() const { return acceleration[1]; }
//  float get_acc_z() const { return acceleration[2]; }
//
//  float get_gyro_x() const { return gyro[0]; }
//  float get_gyro_y() const { return gyro[1]; }
//  float get_gyro_z() const { return gyro[2]; }t
  int got_data();
private:
uint8_t rx_acc_data[6];
uint8_t rx_gyro_data[6];
float acceleration[3]; // 转换后的加速度值，单位为g
float gyro[3];         // 转换后的角速度值，单位为dps
};

#endif


// 在imu.h文件末尾添加以下C语言接口函数
#ifdef __cplusplus
extern "C" {
#endif

// C语言兼容的接口函数声明
void* imu_create(void);
void imu_destroy(void* imu_ptr);
float* imu_acc_calculate(void* imu_ptr);
float* imu_gyro_calculate(void* imu_ptr);
int imu_got_data(void* imu_ptr);




void* imu_get_handle(void);

#ifdef __cplusplus
}

#endif


#endif //C1_IMU_H