/*
#作者：LARK
#日期：2023/6/1
#描述：定义循迹的传感器
*/
#include "misc.h"
#include "stm32f10x_exti.h"
#include "delay.h"
#include "MotorDev.h"
//检索GPIO引脚的信号即可 无需使用中断
void InfraredSensorInit(void);
//void EXTI4_IRQHandler(void);
void EXTIX4_Init(void);
void EXTIX5_Init(void);
void EXTIX6_Init(void);
void EXTIX7_Init(void);


