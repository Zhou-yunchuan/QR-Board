/*
 * SCServo.c
 * ���ض��Ӳ���ӿڲ����
 * ����: 2019.9.7
 * ����: 
 */
#include "bsp_scservo.h"
#include "wiring.h"

static uint8_t wBuf[128];
static uint8_t wLen = 0;

//UART �������ݽӿ�
int readSCS(unsigned char *nDat, int nLen)
{
	int Size = 0;
	int ComData;
	uint32_t IOTimeOut = 2;//���������ʱ

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

//UART �������ݽӿ�
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

//���ջ�����ˢ��
void rFlushSCS()
{
	Uart_Flush();
}

//���ͻ�����ˢ��
void wFlushSCS()
{
	if(wLen){
		Uart_Send(wBuf, wLen);
		wLen = 0;
	}
}

