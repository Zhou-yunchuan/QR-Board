#ifndef BSP_LED_H_
#define BSP_LED_H_

#include "stdint.h"

typedef enum {
    RED = 0,
    GREEN,
    BLUE
} LED_Type;

void BSP_LED_Init(void);
void BSP_LED_Toggle(LED_Type type);
void BSP_LED_On(LED_Type type);
void BSP_LED_Off(LED_Type type);
void BSP_LED_Waterfall(void);


#endif
