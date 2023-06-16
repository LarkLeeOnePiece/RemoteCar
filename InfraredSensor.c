/*
#���ߣ�LARK
#���ڣ�2023/6/1
#����������ѭ���Ĵ�����
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
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		     //��������ģʽ
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.4
 GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		     //��������ģʽ
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.5
 GPIO_ResetBits(GPIOA,GPIO_Pin_5);

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		     //��������ģʽ
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.6
 GPIO_ResetBits(GPIOA,GPIO_Pin_6);
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		     //��������ģʽ
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.7
 GPIO_ResetBits(GPIOA,GPIO_Pin_7);
}
//�ⲿ�ж�4�������ʼ��
void EXTIX4_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	InfraredSensorInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//ʹ��IO����ʱ��
	//ӳ��IO���ж���
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource4);//PA4->Line4
	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;//һ�����Ϊ�ͣ���������Ϊ��   Ӧ�ø�Ϊ�����½��ض���Ҫ�ж�
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}
//�ⲿ�ж�5
void EXTIX5_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	InfraredSensorInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//ʹ��IO����ʱ��
	//ӳ��IO���ж���
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource5);//PA4->Line4
	EXTI_InitStructure.EXTI_Line=EXTI_Line5;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;//һ�����Ϊ�ͣ���������Ϊ��
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//�ⲿ�ж�6
void EXTIX6_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	InfraredSensorInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//ʹ��IO����ʱ��
	//ӳ��IO���ж���
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6);//PA6->Line6
	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;//һ�����Ϊ�ͣ���������Ϊ��
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

//�ⲿ�ж�7
void EXTIX7_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	InfraredSensorInit();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//ʹ��IO����ʱ��
	//ӳ��IO���ж���
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);//PA7->Line7
	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;//һ�����Ϊ�ͣ���������Ϊ��
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

extern u16 LeftPin1,RightPin1,LeftPin2,RightPin2;
//��д�жϷ�����
void EXTI4_IRQHandler()
{
	//��Ӧ��1	
	FollowLine();
	EXTI_ClearITPendingBit(EXTI_Line4);
}

void EXTI9_5_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line5) != RESET)//��Ӧ��1
	{
		FollowLine();
		//ִ���жϷ����� ������Ҫ��ʲô
		EXTI_ClearITPendingBit(EXTI_Line5); 	//�жϱ�־λ���	
	}
	
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)//��Ӧ��2
	{
		FollowLine();
		//ִ���жϷ����� ������Ҫ��ʲô
		EXTI_ClearITPendingBit(EXTI_Line6); 	//�жϱ�־λ���	
	}
	
	if(EXTI_GetITStatus(EXTI_Line7) != RESET)//��Ӧ��2
	{
		FollowLine();
		//ִ���жϷ����� ������Ҫ��ʲô
		EXTI_ClearITPendingBit(EXTI_Line7); 	//�жϱ�־λ���	
	}

	
}


