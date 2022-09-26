
#include "bsp_pwmservo.h"
#include "bsp.h"
#include "tim.h"

#define SERVO_NUM (8)

typedef struct {
    TIM_HandleTypeDef *htim;
    uint32_t channel;
} PWMServo;

PWMServo pwmservo[SERVO_NUM] = {0};

void BSP_PWMServo_Init(void)
{
    // pwmservo1 -> TIM1_CH1 -> PA8
    // pwmservo2 -> TIM1_CH2 -> PB3
    // pwmservo3 -> TIM1_CH3 -> PB6
    // pwmservo4 -> TIM1_CH4 -> PA11
    // pwmservo5 -> TIM3_CH1 -> PA6
    // pwmservo6 -> TIM3_CH2 -> PA7
    // pwmservo7 -> TIM3_CH3 -> PB0
    // pwmservo8 -> TIM3_CH4 -> PB1

    pwmservo[0].htim = &htim1;
    pwmservo[0].channel = TIM_CHANNEL_1;

    pwmservo[1].htim = &htim1;
    pwmservo[1].channel = TIM_CHANNEL_2;

    pwmservo[2].htim = &htim1;
    pwmservo[2].channel = TIM_CHANNEL_3;

    pwmservo[3].htim = &htim1;
    pwmservo[3].channel = TIM_CHANNEL_4;

    pwmservo[4].htim = &htim3;
    pwmservo[4].channel = TIM_CHANNEL_1;

    pwmservo[5].htim = &htim3;
    pwmservo[5].channel = TIM_CHANNEL_2;

    pwmservo[6].htim = &htim3;
    pwmservo[6].channel = TIM_CHANNEL_3;

    pwmservo[7].htim = &htim3;
    pwmservo[7].channel = TIM_CHANNEL_4;

    for(int i=0;i<SERVO_NUM;i++)
    {
        HAL_TIM_PWM_Start(pwmservo[i].htim, pwmservo[i].channel);
    }
}

void BSP_PWMServo_SetAngle(int id, float angle)
{

// uint32_t tim_freq = 1000000; // 1MHz
// uint32_t pwm_freq = 50; // 50Hz -> 20ms
// uint32_t counter_period = (tim_freq/pwm_freq)-1; // 20000-1

// float min_duty = 0.025; // 0.5/20 = 0.025
// float max_duty = 0.125; // 2.5/20 = 0.125
// uint32_t min_compare = min_duty*counter_period;
// uint32_t max_compare = max_duty*counter_period;

    uint32_t min_compare = 500;
    uint32_t max_compare = 2500;
    uint32_t compare = (uint32_t)(angle*100/9) + 500; // [0,180] -> [500,2500]

    if(compare > max_compare)
    {
        compare = max_compare;
    }
    if(compare < min_compare)
    {
        compare = min_compare;
    }
    __HAL_TIM_SET_COMPARE(pwmservo[id-1].htim, pwmservo[id-1].channel, compare);
}


void BSP_PWMServo_Test(void)
{
    // 0 -> 60 -> 0
    static RangeCycle angle = {0,1};
    BSP_GenerateRangeCycle(&angle,0,60,60);

    for(int i=1;i<=SERVO_NUM;i++)
    {
        BSP_PWMServo_SetAngle(i, angle.val);
    }
}





