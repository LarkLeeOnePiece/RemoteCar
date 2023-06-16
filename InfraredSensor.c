/*
#作者：LARK
#日期：2023/6/1
#描述：定义循迹的传感器
*/
#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stdint.h"
#include "InfraredSensor.h"
#include "led.h"
extern u16 SPEED;
extern u16 AutoSPEED;
extern u16 SuperSPEED;
void InfraredSensorInit(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		     //下拉输入模式
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.4
 GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		     //下拉输入模式
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.5
 GPIO_ResetBits(GPIOA,GPIO_Pin_5);

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		     //下拉输入模式
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.6
 GPIO_ResetBits(GPIOA,GPIO_Pin_6);
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		     //下拉输入模式
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.7
 GPIO_ResetBits(GPIOA,GPIO_Pin_7);
}
//外部中断4配置与初始化
void EXTIX4_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	InfraredSensorInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能IO复用时钟
	//映射IO和中断线
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);//PA4->Line4
	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;//一般情况为低，遇到黑线为高   应该该为上升下降沿都需要中断
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
//外部中断5
void EXTIX5_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	InfraredSensorInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能IO复用时钟
	//映射IO和中断线
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource5);//PA4->Line4
	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;//一般情况为低，遇到黑线为高
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//外部中断6
void EXTIX6_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	InfraredSensorInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能IO复用时钟
	//映射IO和中断线
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6);//PA6->Line6
	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;//一般情况为低，遇到黑线为高
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//外部中断7
void EXTIX7_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	InfraredSensorInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能IO复用时钟
	//映射IO和中断线
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);//PA7->Line7
	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;//一般情况为低，遇到黑线为高
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

extern u16 LeftPin1,RightPin1,LeftPin2,RightPin2;
//书写中断服务函数
void EXTI4_IRQHandler()
{
	//对应左1	
	FollowLine();
	EXTI_ClearITPendingBit(EXTI_Line4);
}

void EXTI9_5_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)//对应右1
	{
		FollowLine();
		//执行中断服务函数 即具体要干什么
		EXTI_ClearITPendingBit(EXTI_Line5); 	//中断标志位清除	
	}
	
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)//对应左2
	{
		FollowLine();
		//执行中断服务函数 即具体要干什么
		EXTI_ClearITPendingBit(EXTI_Line6); 	//中断标志位清除	
	}
	
	if(EXTI_GetITStatus(EXTI_Line7) != RESET)//对应右2
	{
		FollowLine();
		//执行中断服务函数 即具体要干什么
		EXTI_ClearITPendingBit(EXTI_Line7); 	//中断标志位清除	
	}

	
}


