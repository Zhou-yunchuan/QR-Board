 
#include "bsp_usart.h"
#include "main.h"      
#include "usart.h"

void BSP_UART_Init(void)
{


}

int fputc(int ch, FILE *f)
{
	uint8_t temp[1] = {ch};
	HAL_UART_Transmit(&huart1, temp, 1, 5);
	return ch;
}

