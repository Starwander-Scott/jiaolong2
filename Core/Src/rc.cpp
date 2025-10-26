//
// Created by chenyincheng on 2025/10/25.
//
#include "rc.h"
#include <stdint.h>
#include <cstring>

//从364-1684线性映射到-1-1

// 在 rc.h 或相应头文件中
extern uint8_t rx_buffer[18];



float linear_mapping(float x, uint16_t in_min, uint16_t in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


rc::rc() {
//  this->init();

}
void rc::init(){
  memcpy(this->rx_data,rx_buffer,18);
  this->parse_control_frame(this->rx_data);
}



// 高性能版本 - 直接位运算
void rc::parse_control_frame(uint8_t* rx_data) {
  // 将前6个字节视为48位数据（实际使用前48位）
  uint64_t data = 0;
  for (int i = 0; i < 6; i++) {
    data |= ((uint64_t)rx_data[i]) << (8 * i);
  }

  // 提取各个位段
  uint16_t raw_ch0 = (data >> 0) & 0x7FF;  // 位0-10: 通道0
  uint16_t raw_ch1 = (data >> 11) & 0x7FF; // 位11-21: 通道1
  uint16_t raw_ch2 = (data >> 22) & 0x7FF; // 位22-32: 通道2
  uint16_t raw_ch3 = (data >> 33) & 0x7FF; // 位33-43: 通道3
  uint8_t raw_s1 = (data >> 44) & 0x03;    // 位44-45: S1
  uint8_t raw_s2 = (data >> 46) & 0x03;    // 位46-47: S2

  // 转换为实际物理值
  uint16_t channel0 = linear_mapping(raw_ch0, 364, 1684, -1, 1);
  uint16_t channel1 = linear_mapping(raw_ch1, 364, 1684, -1, 1);
  uint16_t channel2 = linear_mapping(raw_ch2, 364, 1684, -1, 1);
  uint16_t channel3 = linear_mapping(raw_ch3, 364, 1684, -1, 1);
  switch (raw_s1) {
    case 1:
      s1 = UP_LEFT;
      break;
    case 2:
      s1 = MID_LEFT;
      break;
    case 3:
      s1 = DOWN_LEFT;
      break;

  }
  switch (raw_s2) {
    case 1:
      s2 = UP_RIGHT;
      break;
    case 2:
      s2 = MID_RIGHT;
      break;
    case 3:
      s2 = DOWN_RIGHT;
      break;
  }
}

rc rc1;

//extern uint8_t rx_buffer[18];










