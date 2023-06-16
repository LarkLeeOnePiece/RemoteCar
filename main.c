/*******************************************************************************
//�µ�ѭ��С��
//���ߣ�������
//CSDN��������
//����������������my
//�޸�����:2021��4��2��16:33:58
//�汾��V1.0								  
********************************************************************************
//V1.0 2021/4/2
//
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "infrared_sensor.h"
#include "encode_motor.h"
#include "steering_motor.h"
#include "bluetooth.h"
#include "usart.h"
#include "PID.h"
#include "timer.h"
#include "delay.h"
#include "oled.h"
#include "led.h"
#include <string.h>
#include "encodeing.h"
#include "MotorDev.h"
#include "SteerDev.h"
#include "InfraredSensor.h"
//������
//t = 0.5ms������������-�����ת�� 0 ��
//t = 1.0ms������������-�����ת�� 45��
//t = 1.5ms������������-�����ת�� 90��
//t = 2.0ms������������-�����ת�� 135��
//t = 2.5ms������������-�����ת��180��
extern u16 USART_RX_STA;
u16 LeftPin1=0,RightPin1=0,LeftPin2=0,RightPin2=0;
u16 SPEED=5300;//ȫ���ٶ����� �ٶ�Ӧ�ô�10���õ�190   190Ϊ����
u8 MODE=1;//ģʽ���� Ĭ��ң��ģʽ
u8 Dir;//С���������
u16 AutoSPEED=5000;//0-7199 0�ǳ��죬5000������������
u16 SuperSPEED=4800;//�Ͽ���ٶȣ����ڼ��ٵ������3000�Ͽ�
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	My_USART1_Init(9600);
	LED_Init();
	delay_init(); //��ʱ��ʼ��
	MotorInit(7199,99);//��ʼ�����PWM��  ��PWM����Ƶ��Ҫ����1K����20k���£�1k�����޷��ȶ�������20k����ת�ٹ���ֻ�м����
	SteerInit(199,7200);//��ʼ�����PWM�� ��ʼ������Ϊ20ms
	InfraredSensorInit();
	EXTIX4_Init();
	EXTIX5_Init();
	EXTIX6_Init();
	EXTIX7_Init();
	DirInit();
	GoStop();
	while(1){
		if(MODE==0){
			LeftPin1=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4);
			RightPin1=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5);
			LeftPin2=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
			RightPin2=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7);
			if(((LeftPin1||LeftPin2)&&(RightPin1||RightPin2))){
				//����������⵽������ʮ��·��
				//BlinkLED(10);
				GoStop();
				BlinkLED(10);
				SwipeCard();//ˢ��
				delay_ms(3000);//�ȴ�����
				BlinkLED(10);
				ResetCard();//�ָ�������ǰ��
				delay_ms(5000);//�ȴ�����
				BlinkLED(10);
				GoForward(AutoSPEED,AutoSPEED);
				delay_ms(2000);//�ȴ�����
			}
			if(LeftPin2&&(!LeftPin1)&&(!RightPin1)&&(!RightPin2)){//ֻ����2������
				//��΢ƫ��
				//BlinkLED(1);
				GoLeft(AutoSPEED,AutoSPEED);//����ת��
			}
			if(RightPin2&&(!RightPin1)&&(!LeftPin1)&&(!LeftPin2)){//ֻ����2������
				//��΢ƫ�� 
				//BlinkLED(2);
				GoRight(AutoSPEED,AutoSPEED);//����ת��
			}
			if(LeftPin1&&(!LeftPin2)&&(!RightPin1)&&(!RightPin2)){//ֻ����1������
				GoLeft(SuperSPEED,SuperSPEED);//ȫ��ת��
				while(!RightPin2){
					GoLeft(SuperSPEED,SuperSPEED);//ȫ��ת�� ֱ���ұ���������
				}
			}
			if(LeftPin1&&LeftPin2&&(!RightPin1)&&(!RightPin2)){
				GoLeft(SuperSPEED,SuperSPEED);//ȫ��ת��
				while(!RightPin2){
					GoLeft(SuperSPEED,SuperSPEED);//ȫ��ת�� ֱ���ұ���������
				}
			}
			if(RightPin1&&RightPin2&&(!LeftPin1)&&(!LeftPin2)){
				GoRight(SuperSPEED,SuperSPEED);//ȫ��ת��
				while(!LeftPin2){
					GoRight(SuperSPEED,SuperSPEED);//ȫ��ת��ֱ�������������
				}
				//delay_ms(500);
			}
			if(RightPin1&&(!RightPin2)&&(!LeftPin1)&&(!LeftPin2)){//ֻ����1������
				//�ǳ�ƫ��
				//BlinkLED(8);
				GoRight(SuperSPEED,SuperSPEED);//ȫ��ת��
				while(!LeftPin2){
					GoRight(SuperSPEED,SuperSPEED);//ȫ��ת��ֱ�������������
				}
			}
			if((!LeftPin1)&&(!LeftPin2)&&(!RightPin1)&&(!RightPin2)){
			//���ȫ��û�м�⵽����ֱ��
				GoForward(AutoSPEED,AutoSPEED);
			}
		
		}
	}

}
