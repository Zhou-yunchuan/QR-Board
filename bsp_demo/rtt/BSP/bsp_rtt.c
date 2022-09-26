
#include "bsp_rtt.h"
#include "bsp_led.h"
#include <rtthread.h>
#include "main.h"

static char led1_stack[256];
static struct rt_thread led1_thread;
void LED1Entry(void *parameter);

static rt_thread_t led2_thread = RT_NULL;
void LED2Entry(void *parameter);

void BSP_RTT_Init(void)
{
    // led1 static thread
    rt_thread_init(&led1_thread, "led1_thread",
                   LED1Entry, RT_NULL,
                   &led1_stack, sizeof(led1_stack), 0, 20);
    rt_thread_startup(&led1_thread);

    // led2 dynamic thread
    led2_thread = rt_thread_create("led2_thread",
                                    LED2Entry, RT_NULL,
                                    256, 1, 20);
    if(led2_thread != RT_NULL)
    {
        rt_thread_startup(led2_thread);
    }
}

void LED1Entry(void *parameter)
{
    while(1)
    {
        BSP_LED_Toggle(GREEN);
        rt_thread_delay(500);
    }
}

void LED2Entry(void *parameter)
{
    for(int i=0;i<4;i++)
    {
        BSP_LED_Toggle(BLUE);
        rt_thread_delay(1000);
    }
}
