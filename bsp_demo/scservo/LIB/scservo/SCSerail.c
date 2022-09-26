/*
 * SCServo.c
 * 飞特舵机硬件接口层程序
 * 日期: 2019.9.7
 * 作者: 
 */
#include "bsp_scservo.h"
#include "wiring.h"

static uint8_t wBuf[128];
static uint8_t wLen = 0;

//UART 接收数据接口
int readSCS(unsigned char *nDat, int nLen)
{
	int Size = 0;
	int ComData;
	uint32_t IOTimeOut = 2;//输入输出超时

	uint32_t t_begin = millis();
	while(1){
		ComData = Uart_Read();
		if(ComData!=-1){
			if(nDat){
				nDat[Size] = ComData;
			}
			Size++;
			t_begin = millis();
			t_begin = HAL_GetTick();

		}
		if(Size>=nLen){
			break;
		}
		uint32_t t_user = millis() - t_begin;
		if(t_user>IOTimeOut){
			break;
		}
	}
	return Size;
}

//UART 发送数据接口
int writeSCS(unsigned char *nDat, int nLen)
{
	while(nLen--){
		if(wLen<sizeof(wBuf)){
			wBuf[wLen] = *nDat;
			wLen++;
			nDat++;
		}
	}
	return wLen;
}

//接收缓冲区刷新
void rFlushSCS()
{
	Uart_Flush();
}

//发送缓冲区刷新
void wFlushSCS()
{
	if(wLen){
		Uart_Send(wBuf, wLen);
		wLen = 0;
	}
}

