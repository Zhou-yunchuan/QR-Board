

#include "bsp_battery.h"
#include "bsp.h"
#include "adc.h"

#define BAT_BUF_LEN (20)

uint32_t bat_buf[BAT_BUF_LEN] = {0};
float bat_voltage = 0;

uint32_t averageFilter(const uint32_t arr[], int len);

void BSP_Battery_Init(void)
{
    // ADC1_IN0 -> PA0
    HAL_ADCEx_Calibration_Start(&hadc1);
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&bat_buf, BAT_BUF_LEN);
}


float BSP_Battery_GetVoltage(void)
{
    return bat_voltage;
}



void BSP_Battery_UpdateVoltage(void)
{
    uint32_t adc_avg = 0;

    adc_avg = averageFilter(bat_buf, BAT_BUF_LEN);
    bat_voltage = adc_avg*3.3f*4/4096;
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&bat_buf, BAT_BUF_LEN);
}


uint32_t averageFilter(const uint32_t arr[], int len)
{
    uint32_t sum = 0;
    uint32_t avg = 0;
    uint32_t ret = 0;

    for(int i=0;i<len;i++)
    {
        sum += arr[i];
    }

    avg = sum/len;
    ret = avg;
    return ret;
}

