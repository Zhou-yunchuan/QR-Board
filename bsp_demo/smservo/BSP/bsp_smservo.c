
#include "bsp_smservo.h"
#include "SCServo.h"
#include "usart.h"
#include "bsp.h"

SMServo_Driver smsd;

void BSP_SMServo_Init(void)
{
    // SMServo TX -> USART2_TX -> PA2
    // SMServo RX -> USART2_RX -> PA3
    HAL_UART_Receive_IT(&huart2, (uint8_t*)&smsd.temp, 1);
}

void BSP_SMServo_Test(void)
{
    // 0 -> 60 -> 0
    static RangeCycle angle = {0,1};
    BSP_GenerateRangeCycle(&angle,0,60,60);
    BSP_SMServo_SetAngle(1, angle.val, 1500);

}

void BSP_SMServo_SetAngle(int id, float angle, int speed)
{
    uint32_t pos = angle*A2D;
    WritePosEx(id, pos, speed, 0);
}

void Uart_Send(uint8_t *buf , uint8_t len)
{
    HAL_UART_Transmit(&huart2, buf, len, 50);
}

void Uart_Flush(void)
{
    smsd.head = smsd.tail = 0;
}

int16_t Uart_Read(void)
{
    uint8_t ret = 0;
    if(smsd.head != smsd.tail) {
        ret = smsd.buf[smsd.head];
        smsd.head =  (smsd.head+1)%128;
        return ret;
    }else {
        return -1;
    }
}

