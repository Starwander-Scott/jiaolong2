//
// Created by chenyincheng on 2025/10/25.
//

#ifndef C3_RC_H
#define C3_RC_H

#include <stdint.h>

class rc {
private:
  uint16_t channel0;
  uint16_t channel1;
  uint16_t channel2;
  uint16_t channel3;
  uint8_t s1;
  uint8_t s2;
  uint8_t rx_data[18];
  enum left{UP_LEFT,MID_LEFT,DOWN_LEFT};
  enum right{UP_RIGHT,MID_RIGHT,DOWN_RIGHT};


public:
  rc();
  void parse_control_frame(uint8_t* rx_buffer);
  //void calc();
  void init();
};


#endif // C3_RC_H
