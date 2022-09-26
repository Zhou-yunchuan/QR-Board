

#include "bsp_time.h"
#include "main.h"

typedef struct {
    __IO uint32_t tick;
    uint32_t flag;
} Time;

static Time time = {0};

void BSP_Time_Init(void)
{
    time.flag = 0;
    time.tick = 0;
}

void BSP_Time_IncTick(void)
{
    time.tick++;
}

int BSP_Time_CheckTick(void)
{
    int ret;
    if(time.flag != time.tick)
    {
        time.flag = time.tick;
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    return ret;
}

int BSP_Time_CheckSlice(int slice)
{
    int ret;
    if(time.flag % slice == 0)
    {
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    return ret;
}



