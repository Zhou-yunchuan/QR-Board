

#include "bsp_led.h"
#include "main.h"

#define LED_NUM (3)

typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
} LED;

static LED led[LED_NUM] = {0};

void BSP_LED_Init(void)
{
    // LED Red -> PD0
    // LED Blue -> PD1
    // LED Green -> PA15

    led[RED].pin = LED_RED_Pin;
    led[RED].port = LED_RED_GPIO_Port;

    led[BLUE].pin = LED_BLUE_Pin;
    led[BLUE].port = LED_BLUE_GPIO_Port;

    led[GREEN].pin = LED_GREEN_Pin;
    led[GREEN].port = LED_GREEN_GPIO_Port;

}

void BSP_LED_Toggle(LED_Type type)
{
    HAL_GPIO_TogglePin(led[type].port, led[type].pin);
}

void BSP_LED_On(LED_Type type)
{
    HAL_GPIO_WritePin(led[type].port, led[type].pin, GPIO_PIN_RESET);
}

void BSP_LED_Off(LED_Type type)
{
    HAL_GPIO_WritePin(led[type].port, led[type].pin, GPIO_PIN_SET);
}

void BSP_LED_Waterfall(void)
{
    static int cnt = 1;
    switch(cnt)
    {
        case 1:
            BSP_LED_On(RED);
            break;
        case 2:
            BSP_LED_Off(RED);
            BSP_LED_On(GREEN);
            break;
        case 3:
            BSP_LED_Off(GREEN);
            BSP_LED_On(BLUE);
          break;
        case 4:
            BSP_LED_Off(BLUE);
            BSP_LED_On(RED);
            BSP_LED_On(BLUE);
            BSP_LED_On(GREEN);
          break;
        case 5:
            BSP_LED_Off(RED);
            BSP_LED_Off(BLUE);
            BSP_LED_Off(GREEN);
            break;
    }
    cnt++;
    if(cnt>5)
    {
        cnt = 1;
    }
}


