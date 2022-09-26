#ifndef BSP_I2C_H_
#define BSP_I2C_H_

#include "stdint.h"

#define I2C_SDA_IN    {IMU_SDA_GPIO_Port->MODER &= ~(3<<(7*2)); IMU_SDA_GPIO_Port->MODER |= 0<<7*2;}
#define I2C_SDA_OUT   {IMU_SDA_GPIO_Port->MODER &= ~(3<<(7*2)); IMU_SDA_GPIO_Port->MODER |= 1<<7*2;}

#define I2C_SCL_HIGH  IMU_SCL_GPIO_Port->BSRR |= 1 << 6
#define I2C_SCL_LOW   IMU_SCL_GPIO_Port->BRR  |= 1 << 6

#define I2C_SDA_HIGH  IMU_SDA_GPIO_Port->BSRR |= 1 << 7
#define I2C_SDA_LOW   IMU_SDA_GPIO_Port->BRR  |= 1 << 7

#define I2C_READ_SDA  HAL_GPIO_ReadPin(IMU_SDA_GPIO_Port, IMU_SDA_Pin)
#define I2C_DELAY     BSP_DelayUs(2)

void BSP_I2C_Init(void);
void BSP_I2C_Start(void);
void BSP_I2C_Stop(void);
void BSP_I2C_SendByte(uint8_t txd);
void BSP_I2C_Ack(void);
void BSP_I2C_Nack(void);
uint8_t BSP_I2C_ReadByte(uint8_t ack);
uint8_t BSP_I2C_WaitAck(void);

#endif
















