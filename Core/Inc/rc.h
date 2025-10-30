//
// Created by chenyincheng on 2025/10/25.
//

#ifndef C3_RC_H
#define C3_RC_H

#include <stdint.h>
#include <stdbool.h>

enum joystick{UP,MID,DOWN};

class rc {
private:
  uint8_t *rx_data_;

public:
  float channel0;
  float channel1;
  float channel2;
  float channel3;
  joystick s1;
  joystick s2;

  rc();
  void handle(uint8_t* rx_buffer);
  uint8_t *rx_buffer_;
  float linear_mapping(float x, uint16_t in_min, uint16_t in_max, float out_min, float out_max);
  //void calc();
  void init();
};


#endif // C3_RC_H
