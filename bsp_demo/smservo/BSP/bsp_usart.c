 
#include "bsp_usart.h"
#include "stdio.h" 
#include "main.h"      
#include "usart.h"
#include "bsp_smservo.h"

void BSP_UART_Init(void)
{

}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) 
{
    if(huart -> Instance == huart2.Instance ) 
    {
        smsd.buf[smsd.tail] = smsd.temp;
        smsd.tail = (smsd.tail+1)%128;
        HAL_UART_Receive_IT(&huart2, (uint8_t*)&smsd.temp, 1); 
    }
}

