#ifndef BSP_TIME_H_
#define BSP_TIME_H_

void BSP_Time_Init(void);
void BSP_Time_IncTick(void);
int BSP_Time_CheckTick(void);
int BSP_Time_CheckSlice(int slice);


#endif
