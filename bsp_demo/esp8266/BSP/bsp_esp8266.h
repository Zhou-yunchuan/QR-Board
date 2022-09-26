#ifndef BSP_ESP8266_H_
#define BSP_ESP8266_H_

#include "stdint.h"

#define ESP8266_RX_LEN (10)

typedef struct {
    uint8_t buf[ESP8266_RX_LEN];
    int flag;
    int rx_len;
} ESP8266_Msg;

extern ESP8266_Msg esp8266_msg;

void BSP_ESP8266_Init(void);
void BSP_ESP8266_Test(void);

#endif
