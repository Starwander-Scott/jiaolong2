//
// Created by chenyincheng on 2025/10/12.
//
#include "imu.h"
#include "main.h"

// 假设的常量定义，实际值需参考最新数据手册
#define g 9.80665f // 重力加速度
#define pi 3.14159265358979323846f // 圆周率
#define deg2rad(x) (x * pi / 180.0f) // 角度转弧度
#define BMI088_ACCEL_RANGE_3G 0x00
#define BMI088_ACCEL_RANGE_6G 0x01
#define BMI088_ACCEL_RANGE_12G 0x02
#define BMI088_ACCEL_RANGE_24G 0x03

#define BMI088_GYRO_RANGE_2000DPS 0x00
#define BMI088_GYRO_RANGE_1000DPS 0x01
#define BMI088_GYRO_RANGE_500DPS 0x02
#define BMI088_GYRO_RANGE_250DPS 0x03
#define BMI088_GYRO_RANGE_125DPS 0x04

#define BMI088_GYRO_BW_532HZ 0x00
#define BMI088_GYRO_BW_230HZ 0x01
#define BMI088_GYRO_BW_116HZ 0x02
#define BMI088_GYRO_BW_47HZ  0x03
#define BMI088_GYRO_BW_23HZ  0x04
#define BMI088_GYRO_BW_12HZ  0x05
#define BMI088_GYRO_BW_64HZ  0x06
#define BMI088_GYRO_BW_32HZ  0x07

extern void bmi088_accel_read_reg(uint8_t reg_addr, uint8_t *data, uint8_t len);
extern void bmi088_gyro_read_reg(uint8_t reg_addr, uint8_t *data, uint8_t len);
extern void bmi088_accel_write_reg(uint8_t reg_addr, uint8_t data);
extern void bmi088_gyro_write_reg(uint8_t reg_addr, uint8_t data);

//float acceleration[] = {0, 0, 0};
//float gyro[] = {0, 0, 0};

IMU::IMU() {
  std::cout << "IMU init" << std::endl;
}

IMU::~IMU() {
  std::cout << "IMU deinit" << std::endl;
}

int IMU::got_data() {
  return 1;
}

float* IMU::acc_calculate() {
  uint8_t raw_range;

  float acc_range_factor; // 量程系数
  int16_t raw_acc[3];     // 三轴加速度原始值


  // 1. 读取0x41寄存器中的量程参数，并换算为量程系数
  bmi088_accel_read_reg(0x41, &raw_range, 1);

  // 提取量程配置位（寄存器低2位）
  uint8_t range_config = raw_range & 0x03;

  // 根据量程配置设置量程系数
  switch (range_config) {
  case BMI088_ACCEL_RANGE_3G:
    acc_range_factor = 3.0f / 32768.0f; // 16位有符号数 -> ±32768
    break;
  case BMI088_ACCEL_RANGE_6G:
    acc_range_factor = 6.0f / 32768.0f;
    break;
  case BMI088_ACCEL_RANGE_12G:
    acc_range_factor = 12.0f / 32768.0f;
    break;
  case BMI088_ACCEL_RANGE_24G:
    acc_range_factor = 24.0f / 32768.0f;
    break;
  default:
    // 默认使用3G量程
    acc_range_factor = 3.0f / 32768.0f;
    break;
  }

  // 2. 读取0x12寄存器开始的6字节加速度数据
  bmi088_accel_read_reg(0x12, rx_acc_data, 6);

  // 3. 将两个8位数据组合成16位有符号整数（注意字节顺序）
  for (int i = 0; i < 3; i++) {
    // BMI088通常采用高字节在前的方式[10](@ref)
    raw_acc[i] = (int16_t)((rx_acc_data[2*i+1] << 8) | rx_acc_data[2*i]);
  }

  // 4. 用量程系数将原始数据转换为加速度值(g)
  for (int i = 0; i < 3; i++) {
    acceleration[i] = raw_acc[i] * acc_range_factor * g;
  }
  return acceleration;
      //可添加进一步处理，如传感器校准、滤波等
}




//void IMU::gyro_calculate(){
  // 1. 设置/读取gyro0x0F寄存器中的量程range参数，并换算为量程系数

  // 2. 读取gyro0x02寄存器中的6位gyro数据
  // 3. 用量程系数将原始数据转换为常用单位
//}


float* IMU::gyro_calculate() {
  uint8_t raw_range;

  float gyro_range_factor; // 量程系数
  int16_t raw_gyro[3];     // 三轴陀螺仪原始值
  float gyro[3];           // 转换后的角速度值，单位为dps

  // 1. 读取0x0F寄存器中的量程参数
  bmi088_gyro_read_reg(0x0F, &raw_range, 1);

  // 提取量程配置位（寄存器低3位）
  uint8_t range_config = raw_range & 0x07;

  // 根据量程配置设置量程系数
  switch (range_config) {
  case BMI088_GYRO_RANGE_2000DPS:
    gyro_range_factor = 2000.0f / 32768.0f;
    break;
  case BMI088_GYRO_RANGE_1000DPS:
    gyro_range_factor = 1000.0f / 32768.0f;
    break;
  case BMI088_GYRO_RANGE_500DPS:
    gyro_range_factor = 500.0f / 32768.0f;
    break;
  case BMI088_GYRO_RANGE_250DPS:
    gyro_range_factor = 250.0f / 32768.0f;
    break;
  case BMI088_GYRO_RANGE_125DPS:
    gyro_range_factor = 125.0f / 32768.0f;
    break;
  default:
    // 默认使用2000DPS量程
    gyro_range_factor = 2000.0f / 32768.0f;
    break;
  }

  // 2. 读取0x02寄存器开始的6字节陀螺仪数据
  bmi088_gyro_read_reg(0x02, rx_gyro_data, 6);

  // 3. 将两个8位数据组合成16位有符号整数
  for (int i = 0; i < 3; i++) {
    raw_gyro[i] = (int16_t)((rx_gyro_data[2*i+1] << 8) | rx_gyro_data[2*i]);
  }

  // 4. 用量程系数将原始数据转换为角速度值(dps)
  for (int i = 0; i < 3; i++) {
    gyro[i] = raw_gyro[i] * gyro_range_factor;
  }
  return gyro;
  // 此处可添加进一步处理，如传感器校准、滤波等
}


// 在imu.cpp文件末尾添加以下实现
extern "C" {

void* imu_get_handle(void) {
  static IMU imu;
  return &imu;
}

void* imu_create(void) {
  return new IMU();
}

// 销毁IMU对象
void imu_destroy(void* imu_ptr) {
  IMU* imu = static_cast<IMU*>(imu_ptr);
  delete imu;
}

// 调用加速度计算函数
float* imu_acc_calculate(void* imu_ptr) {
  IMU* imu = static_cast<IMU*>(imu_ptr);
  return imu->acc_calculate();
}

// 调用陀螺仪计算函数
float* imu_gyro_calculate(void* imu_ptr) {
  IMU* imu = static_cast<IMU*>(imu_ptr);
  return imu->gyro_calculate();
}

// 调用数据获取状态函数
int imu_got_data(void* imu_ptr) {
  IMU* imu = static_cast<IMU*>(imu_ptr);
  return imu->got_data();
}

} // extern "C"




