/*
#���ߣ�LARK
#���ڣ�2023/6/1
#���������������������򣨰�����ʱ���ĳ�ʼ����PWM���ɣ��ٶȿ��Ƶȣ�
*/
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stdint.h"
#include "led.h"
#include "SteerDev.h"
void MotorInit(u16 arr,u16 psc);
void DirInit(void);//��ʼ�����Ʒ������������
void GoBack(u16 Leftspeed,u16 Rightspeed);
void GoForward(u16 Leftspeed,u16 Rightspeed);
void GoLeft(u16 Leftspeed,u16 Rightspeed);
void GoRight(u16 Leftspeed,u16 Rightspeed);
void GoStop(void);
void FollowLine(void);



