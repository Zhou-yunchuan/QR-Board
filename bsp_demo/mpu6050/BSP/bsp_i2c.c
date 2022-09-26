
#include "bsp_i2c.h"
#include "bsp.h"

#include "main.h"

void BSP_I2C_Init(void)
{
    // MPU6050 SCL -> PC6
    // MPU6050 SDA -> PC7
    I2C_SDA_HIGH;
    I2C_SCL_HIGH;

}

void BSP_I2C_Start(void)
{
    I2C_SDA_OUT;
    I2C_SDA_HIGH;
    I2C_SCL_HIGH;
    I2C_DELAY;
    I2C_SDA_LOW;
    I2C_DELAY;
    I2C_SCL_LOW;
}


void BSP_I2C_Stop(void)
{
    I2C_SDA_OUT;
    I2C_SCL_LOW;
    I2C_SDA_LOW;
    I2C_DELAY;
    I2C_SCL_HIGH;
    I2C_SDA_HIGH;
    I2C_DELAY;
}


uint8_t BSP_I2C_WaitAck(void)
{
    int err_time = 0;

    I2C_SDA_IN;
    I2C_SDA_HIGH;
    I2C_DELAY;
    I2C_SCL_HIGH;
    I2C_DELAY;

    while(I2C_READ_SDA)
    {
        err_time++;
        if(err_time>250)
        {
            BSP_I2C_Stop();
            return 1;
        }
    }
    I2C_SCL_LOW;
    return 0;
}

void BSP_I2C_Ack(void)
{
    I2C_SCL_LOW;
    I2C_SDA_OUT;
    I2C_SDA_LOW;
    I2C_DELAY;
    I2C_SCL_HIGH;
    I2C_DELAY;
    I2C_SCL_LOW;
}

void BSP_I2C_Nack(void)
{
    I2C_SCL_LOW;
    I2C_SDA_OUT;
    I2C_SDA_HIGH;
    I2C_DELAY;
    I2C_SCL_HIGH;
    I2C_DELAY;
    I2C_SCL_LOW;
}

void BSP_I2C_SendByte(uint8_t txd)
{
  I2C_SDA_OUT;
  I2C_SCL_LOW;

    for(int i=0;i<8;i++)
    {
        if(txd&0x80)
        {
            I2C_SDA_HIGH;
        }
        else
        {
            I2C_SDA_LOW;
        }
        txd <<= 1;
        I2C_DELAY;
        I2C_SCL_HIGH;
        I2C_DELAY;
        I2C_SCL_LOW;
        I2C_DELAY;
    }
}


uint8_t BSP_I2C_ReadByte(uint8_t ack)
{
    uint8_t receive = 0;
    I2C_SDA_IN;
    for(int i=0; i<8; i++)
    {
        I2C_SCL_LOW;
        I2C_DELAY;
        I2C_SCL_HIGH;
        receive <<= 1;
        if(I2C_READ_SDA)
        {
            receive++;
        }
        I2C_DELAY;
    }
    if(!ack)
    {
        BSP_I2C_Nack();
    }
    else
    {
        BSP_I2C_Ack();
    }
    return receive;
}

