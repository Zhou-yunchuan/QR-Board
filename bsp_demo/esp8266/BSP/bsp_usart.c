
#include "bsp_usart.h"
#include "main.h"
#include "usart.h"
#include "bsp_led.h"
#include "bsp_esp8266.h"

void BSP_UART_Init(void)
{

}

int fputc(int ch, FILE *f)
{
    uint8_t temp[1] = {ch};
    HAL_UART_Transmit(&huart1, temp, 1, 5);
    return ch;
}

void USART1_IRQHandler(void)
{
    if(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET)
    {
        __HAL_UART_CLEAR_IDLEFLAG(&huart1);
        HAL_UART_DMAStop(&huart1);
        esp8266_msg.rx_len = ESP8266_RX_LEN - __HAL_DMA_GET_COUNTER(huart1.hdmarx);
        esp8266_msg.buf[esp8266_msg.rx_len] = 0;
        esp8266_msg.flag = 1;
        HAL_UART_Receive_DMA(&huart1, esp8266_msg.buf, ESP8266_RX_LEN);
    }
}


