
#include "bsp_hcsr04.h"
#include "bsp.h"
#include "tim.h"

float dist = 0; // cm
static uint32_t time = 0;

static enum {
    START = 0,
    IS_RISING_EDGE,
    IS_FALLING_EDGE,
    UPDATE_DIST
} state = START;


void BSP_HCSR04_Init(void)
{
  // Ultrasonic Trig -> PB12
  // Ultrasonic Echo -> TIM15_CH2 -> PB15

    HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);
    HAL_TIM_Base_Start(&htim15);
    HAL_TIM_IC_Start_IT(&htim15, TIM_CHANNEL_2);
}

float BSP_HCSR04_GetDist(void)
{
    return dist;
}

void BSP_HCSR04_Trig(void)
{
    HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin, GPIO_PIN_SET);
    BSP_DelayUs(11);
    HAL_GPIO_WritePin(TRIG_GPIO_Port,TRIG_Pin, GPIO_PIN_RESET);
}


void BSP_HCSR04_UpdateDist(void)
{
    const float VS = 342.62; // 342.62m/s

    switch(state)
    {
        case START:
            __HAL_TIM_SET_CAPTUREPOLARITY(&htim15, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);
            BSP_HCSR04_Trig();
            state = IS_RISING_EDGE;
            break;
        case UPDATE_DIST:
            dist = 100*VS*time/1000000/2;
            state = START;
            break;
        default:
            break;
    }
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == htim15.Instance)
    {
        switch(state)
        {
            case IS_RISING_EDGE:
                __HAL_TIM_SET_COUNTER(&htim15, 0);
                __HAL_TIM_SET_CAPTUREPOLARITY(&htim15, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_FALLING);
                state = IS_FALLING_EDGE;
                break;
            case IS_FALLING_EDGE:
                time = __HAL_TIM_GET_COUNTER(&htim15);
                state = UPDATE_DIST;
                break;
            default:
                break;
        }
    }
}

