
#include "bsp_scservo.h"
#include "bsp.h"
#include "SCSCL.h"
#include "usart.h"

SCServo_Driver scsd;

void BSP_SCServo_Init(void)
{
    // SCServo TX -> USART2_TX -> PA2
    // SCServo RX -> USART2_RX -> PA3
    HAL_UART_Receive_IT(&huart2, (uint8_t*)&scsd.temp, 1);
}

void BSP_SCServo_Test(void)
{
    // 0 -> 60 -> 0
    static RangeCycle angle = {0,1};
    BSP_GenerateRangeCycle(&angle,0,60,60);

    BSP_SCServo_SetAngle(1, angle.val, 1500);
}

void BSP_SCServo_SetAngle(int id, float angle, int speed)
{
    uint32_t pos = angle*A2D;
    WritePos(id, pos, 0, speed);
}

void Uart_Send(uint8_t *buf , uint8_t len)
{
    HAL_UART_Transmit(&huart2, buf, len, 50);
}

void Uart_Flush(void)
{
    scsd.head = scsd.tail = 0;
}

int16_t Uart_Read(void)
{
    uint8_t ret = 0;
    if(scsd.head != scsd.tail) {
        ret = scsd.buf[scsd.head];
        scsd.head =  (scsd.head+1)%128;
        return ret;
    }else {
        return -1;
    }
}

