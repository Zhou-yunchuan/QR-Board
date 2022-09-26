#include "main.h"
#include "wiring.h"


__IO uint32_t TimingMillis = 0;


uint32_t millis(void)
{
	return TimingMillis;
}

void incTimingMillis(void)
{
	TimingMillis++;
}


