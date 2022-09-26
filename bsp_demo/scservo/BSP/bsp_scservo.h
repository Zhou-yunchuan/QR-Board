#ifndef BSP_SCSERVO_H_
#define BSP_SCSERVO_H_

#include "main.h"

#define A2D (3.41f)
#define D2A (0.293f)

typedef struct {
    __IO uint8_t buf[128];
    __IO int head;
    __IO int tail;
    __IO uint8_t temp;
} SCServo_Driver;

extern SCServo_Driver scsd;

void BSP_SCServo_Init(void);
void BSP_SCServo_Test(void);
void BSP_SCServo_SetAngle(int id, float angle, int speed);

int16_t Uart_Read(void);
void Uart_Flush(void);
void Uart_Send(uint8_t *buf , uint8_t len);




#endif
