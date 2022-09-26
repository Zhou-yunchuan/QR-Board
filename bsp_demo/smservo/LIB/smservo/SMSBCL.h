/*
 * SMSBCL.h
 * 飞特SMS/STS系列串行舵机应用层程序
 * 日期: 2020.11.8
 * 作者: 
 */

#ifndef _SMSBCL_H
#define _SMSBCL_H

#include <stdint.h>

#define	SMSBCL_1M 0
#define	SMSBCL_0_5M 1
#define	SMSBCL_250K 2
#define	SMSBCL_128K 3
#define	SMSBCL_115200 4
#define	SMSBCL_76800	5
#define	SMSBCL_57600	6
#define	SMSBCL_38400	7

//内存表定义
//-------EPROM(只读)--------
#define SMSBCL_MODEL_L 3
#define SMSBCL_MODEL_H 4

//-------EPROM(读写)--------
#define SMSBCL_ID 5
#define SMSBCL_BAUD_RATE 6
#define SMSBCL_MIN_ANGLE_LIMIT_L 9
#define SMSBCL_MIN_ANGLE_LIMIT_H 10
#define SMSBCL_MAX_ANGLE_LIMIT_L 11
#define SMSBCL_MAX_ANGLE_LIMIT_H 12
#define SMSBCL_CW_DEAD 26
#define SMSBCL_CCW_DEAD 27
#define SMSBCL_OFS_L 31
#define SMSBCL_OFS_H 32
#define SMSBCL_MODE 33

//-------SRAM(读写)--------
#define SMSBCL_TORQUE_ENABLE 40
#define SMSBCL_ACC 41
#define SMSBCL_GOAL_POSITION_L 42
#define SMSBCL_GOAL_POSITION_H 43
#define SMSBCL_GOAL_TIME_L 44
#define SMSBCL_GOAL_TIME_H 45
#define SMSBCL_GOAL_SPEED_L 46
#define SMSBCL_GOAL_SPEED_H 47
#define SMSBCL_LOCK 55

//-------SRAM(只读)--------
#define SMSBCL_PRESENT_POSITION_L 56
#define SMSBCL_PRESENT_POSITION_H 57
#define SMSBCL_PRESENT_SPEED_L 58
#define SMSBCL_PRESENT_SPEED_H 59
#define SMSBCL_PRESENT_LOAD_L 60
#define SMSBCL_PRESENT_LOAD_H 61
#define SMSBCL_PRESENT_VOLTAGE 62
#define SMSBCL_PRESENT_TEMPERATURE 63
#define SMSBCL_MOVING 66
#define SMSBCL_PRESENT_CURRENT_L 69
#define SMSBCL_PRESENT_CURRENT_H 70


extern int WritePosEx(uint8_t ID, int16_t Position, uint16_t Speed, uint8_t ACC);//普通写位置指令
extern int RegWritePosEx(uint8_t ID, int16_t Position, uint16_t Speed, uint8_t ACC);//异步写位置指令
extern void RegWriteAction(void);//异步写位置执行
extern void SyncWritePosEx(uint8_t ID[], uint8_t IDN, int16_t Position[], uint16_t Speed[], uint8_t ACC[]);//同步写位置指令
extern int WheelMode(uint8_t ID);//恒速模式
extern int WriteSpe(uint8_t ID, int16_t Speed, uint8_t ACC);//恒速模式控制指令
extern int EnableTorque(uint8_t ID, uint8_t Enable);//扭矩控制指令
extern int unLockEprom(uint8_t ID);//eprom解锁
extern int LockEprom(uint8_t ID);//eprom加锁
extern int CalibrationOfs(uint8_t ID);//中位校准
extern int FeedBack(int ID);//反馈舵机信息
extern int ReadPos(int ID);//读位置
extern int ReadSpeed(int ID);//读速度
extern int ReadLoad(int ID);//读输出扭力
extern int ReadVoltage(int ID);//读电压
extern int ReadTemper(int ID);//读温度
extern int ReadMove(int ID);//读移动状态
extern int ReadCurrent(int ID);//读电流
extern int getErr(void);//返回通信状态,0无出错,1通信出错


#endif
