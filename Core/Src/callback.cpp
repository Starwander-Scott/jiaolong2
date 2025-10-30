//
// Created by chenyincheng on 2025/10/25.
//
#include <stdint.h>
#include "usart.h"
#include "main.h"
#include "rc.h"

rc rc1;




extern uint8_t rx_buffer[18];

//
// extern rc rc1;


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart,uint16_t Size) {
  if (huart == &huart3) {
    // 处理接收到的数据
    // 例如，可以将数据存储到缓冲区，或者设置一个标志位表示数据已接收
    HAL_UARTEx_ReceiveToIdle_DMA( &huart3,rx_buffer,18);
    rc1.handle(rx_buffer);


  }
}



