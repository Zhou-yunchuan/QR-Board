

#include "bsp_mpu6050.h"
#include "inv_mpu.h"
#include "bsp_i2c.h"
#include "bsp.h"

uint8_t BSP_MPU6050_SetGyroFsr(uint8_t fsr);
uint8_t BSP_MPU6050_SetAccelFsr(uint8_t fsr);
uint8_t BSP_MPU6050_SetLPF(uint16_t lpf);
uint8_t BSP_MPU6050_SetRate(uint16_t rate);

int16_t BSP_MPU6050_GetTemp(void);
uint8_t BSP_MPU6050_GetGyroscope(int16_t *gx, int16_t *gy, int16_t *gz);
uint8_t BSP_MPU6050_GetAccelerometer(int16_t *ax, int16_t *ay, int16_t *az);

MPU6050 mpu6050 = {0};

void BSP_MPU6050_UpdateData(void)
{
    if(mpu_dmp_get_data(&mpu6050.pitch, &mpu6050.roll, &mpu6050.yaw) == 0)
    {
        mpu6050.temp = BSP_MPU6050_GetTemp();
        BSP_MPU6050_GetAccelerometer(&mpu6050.ax, &mpu6050.ay, &mpu6050.az);
        BSP_MPU6050_GetGyroscope(&mpu6050.gx, &mpu6050.gy, &mpu6050.gz);
    }
}

MPU6050 *BSP_MPU6050_GetData(void)
{
    return &mpu6050;
}

void BSP_MPU6050_Init(void)
{
    uint8_t res;
    BSP_I2C_Init();
    BSP_MPU6050_WriteByte(MPU_PWR_MGMT1_REG, 0X80);

    BSP_DelayMs(50);
    BSP_MPU6050_WriteByte(MPU_PWR_MGMT1_REG,0X00);
    BSP_MPU6050_SetGyroFsr(3);
    BSP_MPU6050_SetAccelFsr(0);
    BSP_MPU6050_SetRate(1000);
    BSP_MPU6050_WriteByte(MPU_INT_EN_REG,0X00);
    BSP_MPU6050_WriteByte(MPU_USER_CTRL_REG,0X00);
    BSP_MPU6050_WriteByte(MPU_FIFO_EN_REG,0X00);
    BSP_MPU6050_WriteByte(MPU_INTBP_CFG_REG,0X80);
    res = BSP_MPU6050_ReadByte(MPU_DEVICE_ID_REG);

    if(res == MPU_ADDR)
    {
        BSP_MPU6050_WriteByte(MPU_PWR_MGMT1_REG,0X01);
        BSP_MPU6050_WriteByte(MPU_PWR_MGMT2_REG,0X00);
        BSP_MPU6050_SetRate(1000);
     }

    int tick = HAL_GetTick();
    while(mpu_dmp_init())
    {
        if(HAL_GetTick()-tick >= 5000)
        {
            break;
        }
    }
}

uint8_t BSP_MPU6050_SetGyroFsr(uint8_t fsr)
{
    return BSP_MPU6050_WriteByte(MPU_GYRO_CFG_REG, fsr<<3);
}

uint8_t BSP_MPU6050_SetAccelFsr(uint8_t fsr)
{
    return BSP_MPU6050_WriteByte(MPU_ACCEL_CFG_REG, fsr<<3);
}

uint8_t BSP_MPU6050_SetLPF(uint16_t lpf)
{
    uint8_t data = 0;
    if(lpf >= 188) data = 1;
    else if(lpf >= 98) data = 2;
    else if(lpf >= 42) data = 3;
    else if(lpf >= 20) data = 4;
    else if(lpf >= 10) data = 5;
    else data = 6;
    return BSP_MPU6050_WriteByte(MPU_CFG_REG,data);
}

uint8_t BSP_MPU6050_SetRate(uint16_t rate)
{
    u8 data;
    if(rate>1000) rate=1000;
    if(rate<4) rate=4;
    data = 1000/rate-1;
    data = BSP_MPU6050_WriteByte(MPU_SAMPLE_RATE_REG,data);
    return BSP_MPU6050_SetLPF(rate/2);
}


int16_t BSP_MPU6050_GetTemp(void)
{
    uint8_t buf[2];
    int16_t raw;
    float temp;

    BSP_MPU6050_ReadLen(MPU_ADDR, MPU_TEMP_OUTH_REG, 2, buf);
    raw = ((u16)buf[0]<<8)|buf[1];
    temp = 36.53 + ((double)raw)/340;
    return temp*100;
}

uint8_t BSP_MPU6050_GetGyroscope(int16_t *gx, int16_t *gy, int16_t *gz)
{
    uint8_t buf[6],res;
    res = BSP_MPU6050_ReadLen(MPU_ADDR, MPU_GYRO_XOUTH_REG, 6, buf);
    if(res == 0)
    {
        *gx = ((uint16_t)buf[0]<<8)|buf[1];
        *gy = ((uint16_t)buf[2]<<8)|buf[3];
        *gz = ((uint16_t)buf[4]<<8)|buf[5];
    }
    return res;
}

uint8_t BSP_MPU6050_GetAccelerometer(int16_t *ax, int16_t *ay, int16_t *az)
{
    uint8_t buf[6], res;
    res = BSP_MPU6050_ReadLen(MPU_ADDR, MPU_ACCEL_XOUTH_REG, 6, buf);
    if(res == 0)
    {
        *ax = ((uint16_t)buf[0]<<8)|buf[1];
        *ay = ((uint16_t)buf[2]<<8)|buf[3];
        *az = ((uint16_t)buf[4]<<8)|buf[5];
    }
    return res;
}

uint8_t BSP_MPU6050_WriteLen(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf)
{
    BSP_I2C_Start();
    BSP_I2C_SendByte((addr<<1)|0);
    if(BSP_I2C_WaitAck())
    {
        BSP_I2C_Stop();
        return 1;
    }
    BSP_I2C_SendByte(reg);
    BSP_I2C_WaitAck();
    for(int i=0;i<len;i++)
    {
        BSP_I2C_SendByte(buf[i]);
        if(BSP_I2C_WaitAck())
        {
            BSP_I2C_Stop();
            return 1;
        }
    }
    BSP_I2C_Stop();
    return 0;
}

uint8_t BSP_MPU6050_ReadLen(uint8_t addr,uint8_t reg, uint8_t len,uint8_t *buf)
{
    BSP_I2C_Start();
    BSP_I2C_SendByte((addr<<1)|0);

    if(BSP_I2C_WaitAck())
    {
        BSP_I2C_Stop();
        return 1;
    }

    BSP_I2C_SendByte(reg);
    BSP_I2C_WaitAck();
    BSP_I2C_Start();
    BSP_I2C_SendByte((addr<<1)|1);
    BSP_I2C_WaitAck();

    while(len)
    {
        if(len == 1)
        {
            *buf=BSP_I2C_ReadByte(0);
        }
        else
        {
            *buf=BSP_I2C_ReadByte(1);
        }
        len--;
        buf++;
    }

    BSP_I2C_Stop();
    return 0;
}

uint8_t BSP_MPU6050_WriteByte(uint8_t reg, uint8_t data)
{
    BSP_I2C_Start();
    BSP_I2C_SendByte((MPU_ADDR<<1)|0);

    if(BSP_I2C_WaitAck())
    {
        BSP_I2C_Stop();
        return 1;
    }

    BSP_I2C_SendByte(reg);
    BSP_I2C_WaitAck();
    BSP_I2C_SendByte(data);

    if(BSP_I2C_WaitAck())
    {
        BSP_I2C_Stop();
        return 1;
    }

    BSP_I2C_Stop();
    return 0;
}

uint8_t BSP_MPU6050_ReadByte(uint8_t reg)
{
    uint8_t res;
    BSP_I2C_Start();
    BSP_I2C_SendByte((MPU_ADDR<<1)|0);
    BSP_I2C_WaitAck();
    BSP_I2C_SendByte(reg);
    BSP_I2C_WaitAck();
    BSP_I2C_Start();
    BSP_I2C_SendByte((MPU_ADDR<<1)|1);
    BSP_I2C_WaitAck();
    res = BSP_I2C_ReadByte(0);
    BSP_I2C_Stop();
    return res;
}


