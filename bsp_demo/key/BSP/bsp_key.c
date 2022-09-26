/**
  * @file  bsp_key.c
  * @breif
  * Copyright (c) 2022 Zhou Yunchuan
  */
#include "bsp_key.h"

#include "main.h"
#include "bsp_led.h"

struct Button key2;
uint8_t readKey2(void);
void key2Callback(void *btn);

struct Button key1;
uint8_t readKey1(void);
void key1Callback(void *btn);

void BSP_Key_Init()
{
    // KEY1  ---> PC14
    button_init(&key1, readKey1, 	0);

    button_attach(&key1, SINGLE_CLICK,     key1Callback);
    button_attach(&key1, DOUBLE_CLICK,     key1Callback);
    button_attach(&key1, LONG_PRESS_START, key1Callback);

    button_start(&key1);

    // KEY2  ---> PC13
    button_init(&key2, readKey2, 	0);

    button_attach(&key2, SINGLE_CLICK,     key2Callback);
    button_attach(&key2, DOUBLE_CLICK,     key2Callback);
    button_attach(&key2, LONG_PRESS_START, key2Callback);

    button_start(&key2);

}


uint8_t readKey1(void)
{
    uint8_t ret = HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin);
    return ret;
}


uint8_t readKey2(void)
{
    uint8_t ret = HAL_GPIO_ReadPin(KEY2_GPIO_Port, KEY2_Pin);
    return ret;
}

void key2Callback(void *btn)
{
    switch(get_button_event((struct Button*)btn))
    {
        case SINGLE_CLICK:
            BSP_LED_Toggle(RED);
            break;
        case DOUBLE_CLICK:
            BSP_LED_Toggle(RED);
            break;
        case LONG_PRESS_START:
            BSP_LED_Toggle(RED);
            break;
        default:
            break;
    }

}

void key1Callback(void *btn)
{
    switch(get_button_event((struct Button*)btn))
    {
        case SINGLE_CLICK:
            BSP_LED_Toggle(BLUE);
            break;
        case DOUBLE_CLICK:
            BSP_LED_Toggle(BLUE);
            break;
        case LONG_PRESS_START:
            BSP_LED_Toggle(BLUE);
            break;
        default:
            break;
    }
}


