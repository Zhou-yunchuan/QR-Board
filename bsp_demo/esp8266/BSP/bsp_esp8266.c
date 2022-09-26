

#include "bsp_esp8266.h"
#include "bsp_led.h"
#include "usart.h"
#include "main.h"

ESP8266_Msg esp8266_msg;

void BSP_ESP8266_Init(void)
{
    for(int i=0;i<ESP8266_RX_LEN;i++)
    {
        esp8266_msg.buf[i] = 0;
    }
    esp8266_msg.flag = 0;
    esp8266_msg.rx_len = 0;

    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
    HAL_UART_Receive_DMA(&huart1, esp8266_msg.buf, ESP8266_RX_LEN);
}


void BSP_ESP8266_Test(void)
{
    if(esp8266_msg.flag == 1)
    {
        esp8266_msg.flag = 0;
        if(esp8266_msg.buf[0]==0xaa && esp8266_msg.buf[1]==0x55)
        {
            if(esp8266_msg.buf[2]) {
                BSP_LED_On(RED);
            }else {
                BSP_LED_Off(RED);
            }
        }
    }
}

