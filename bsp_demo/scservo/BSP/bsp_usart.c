
#include "bsp_usart.h"
#include "main.h"
#include "usart.h"
#include "bsp_scservo.h"

void BSP_UART_Init(void)
{

}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart -> Instance == huart2.Instance )
    {
        scsd.buf[scsd.tail] = scsd.temp;
        scsd.tail = (scsd.tail+1)%128;
        HAL_UART_Receive_IT(&huart2, (uint8_t*)&scsd.temp, 1);
    }
}

