#ifndef BSP_SMSERVO_H_
#define BSP_SMSERVO_H_

#include "main.h"

#define A2D (11.37f)
#define D2A (0.087f)

typedef struct {
    __IO uint8_t buf[128];
    __IO int head;
    __IO int tail;
    __IO uint8_t temp;
} SMServo_Driver;

extern SMServo_Driver smsd;

void BSP_SMServo_Init(void);
void BSP_SMServo_Test(void);
void BSP_SMServo_SetAngle(int id, float angle, int speed);

int16_t Uart_Read(void);
void Uart_Flush(void);
void Uart_Send(uint8_t *buf , uint8_t len);




#endif
