


#include "bsp_pwmbuzzer.h"
#include "bsp.h"
#include "tim.h"


void BSP_PWMBuzzer_Init(void)
{
    // Buzzer -> PF0
    BSP_PWMBuzzer_Off();
}


void BSP_PWMBuzzer_Test(void)
{
    static RangeCycle freq = {500,1};
    BSP_GenerateRangeCycle(&freq, 500, 2500, 500);
    BSP_PWMBuzzer_SetFreq(freq.val);
    BSP_PWMBuzzer_On();
}

void BSP_PWMBuzzer_On(void)
{
    HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
}


void BSP_PWMBuzzer_Off(void)
{
    // HAL_TIM_PWM_Stop(&htim14, TIM_CHANNEL_1);
    __HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, 0);
}


void BSP_PWMBuzzer_SetFreq(int pwm_freq)
{
    uint32_t tim_freq = 1000000; // 1MHz
    uint32_t reload = (tim_freq/pwm_freq)-1;
    uint32_t compare = reload/2; // 0.5 duty cycle

    __HAL_TIM_SET_AUTORELOAD(&htim14, reload);
    __HAL_TIM_SET_COMPARE(&htim14, TIM_CHANNEL_1, compare);
}






