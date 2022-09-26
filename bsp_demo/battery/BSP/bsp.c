

#include "bsp.h"
#include "main.h"

const uint32_t CLOCK_FREQ = 64;

void BSP_GenerateRangeCycle(RangeCycle *obj, float start, float end, float step)
{
    if((obj->val)>=end)
    {
        obj->sign = -1;
    }
    if((obj->val)<=start)
    {
        obj->sign = 1;
    }
    obj->val += step*(obj->sign);
}


void BSP_DelayUs(int us)
{
    uint32_t ticks;
    uint32_t t_old,t_now,t_cnt = 0;
    uint32_t reload = SysTick->LOAD;
    ticks = us*CLOCK_FREQ;
    t_old = SysTick->VAL;
    while(1)
    {
        t_now = SysTick->VAL;
        if(t_now!=t_old)
        {
            if(t_now<t_old)
            {
                t_cnt += t_old-t_now;
            }
            else
            {
                t_cnt += reload+(t_old-t_now);
            }
            t_old = t_now;
            if(t_cnt>=ticks)
            {
                break;
            }
        }
    }
}


void BSP_DelayMs(int ms)
{
    uint32_t i;
    for(i=0;i<ms;i++)
    {
        BSP_DelayUs(1000);
    }
}
