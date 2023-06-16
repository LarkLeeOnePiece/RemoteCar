/*
#作者：LARK
#日期：2023/6/1
#描述：定义电机的驱动程序（包括定时器的初始化，PWM生成，速度控制等）
*/
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stdint.h"
#include "led.h"
#include "SteerDev.h"
void MotorInit(u16 arr,u16 psc);
void DirInit(void);//初始化控制方向的两个引脚
void GoBack(u16 Leftspeed,u16 Rightspeed);
void GoForward(u16 Leftspeed,u16 Rightspeed);
void GoLeft(u16 Leftspeed,u16 Rightspeed);
void GoRight(u16 Leftspeed,u16 Rightspeed);
void GoStop(void);
void FollowLine(void);



