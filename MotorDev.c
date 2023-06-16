#include "MotorDev.h"
extern u8 MODE;
//��ʼ����ʱ�����PWM
void MotorInit(u16 arr,u16 psc){
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_OCInitTypeDef TIM_OCInitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //��ʹ�ܶ�ʱ�� 4 ʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE); //��ʹ�� GPIO B �� AFIO ���ù���ʱ��
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //�ֱ��ӦTIM4_CH3
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure); //�ٳ�ʼ�� GPIO B
		GPIO_SetBits(GPIOB,GPIO_Pin_8);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //�ֱ��ӦTIM4_CH4
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure); //�ٳ�ʼ�� GPIO B
		GPIO_SetBits(GPIOB,GPIO_Pin_9);
		//��ʼ�� TIM4
		TIM_TimeBaseStructure.TIM_Period = arr; //�������Զ���װ������ֵ
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //����Ԥ��Ƶֵ
		TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM ���ϼ���ģʽ
		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //�۳�ʼ�� TIMx
		//��ʼ�� TIM4 Channe3|4 PWM ģʽ
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ�� PWM ģʽ 2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //������Ը�
		TIM_OC3Init(TIM4, &TIM_OCInitStructure); //�ܳ�ʼ������ TIM4 OC3
		TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); //ʹ��Ԥװ�ؼĴ���
		TIM_OC4Init(TIM4, &TIM_OCInitStructure); //�ܳ�ʼ������ TIM4 OC4
		TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); //ʹ��Ԥװ�ؼĴ���
		TIM_Cmd(TIM4, ENABLE); //��ʹ�� TIM4
		
		TIM_SetCompare3(TIM4,arr/4);//��Ŷ�Ӧ2.4V  �Ա�ֵԽС�������ѹԽ�󣬶�Ӧ����
		TIM_SetCompare4(TIM4,arr/4);//��Ŷ�Ӧ2.4V��PB9  ��Ӧ����
		
}

void DirInit(void){
	 GPIO_InitTypeDef  GPIO_InitStructure;
 	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //PB.12�˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.12
	 GPIO_SetBits(GPIOB,GPIO_Pin_12);						 //PB.12 �����
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //PB.13�˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.12
	 GPIO_ResetBits(GPIOB,GPIO_Pin_13);						 //PB.13 �����
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 //PA.11�˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.11
	 GPIO_SetBits(GPIOA,GPIO_Pin_11);						 //PA.11 �����
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //PA.12�˿�����
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOA.12
	 GPIO_ResetBits(GPIOA,GPIO_Pin_12);						 //PA.12 �����
}

//PB.12 PB.13�������ֵ����ת����
//PB.12 ->1    PB.13->0   ������ת
//PB.12 ->0    PB.13->1   ������ת
//PB.12 ->0    PB.13->0   ֹͣ
//PB.12 ->1    PB.13->1   ֹͣ
//PA11,PA12�������ֵ����ת����
//PA.11 ->1    PA.12->0   ������ת
//PA.11 ->0    PA.12->1   ������ת
//PA.11 ->0    PA.12->0   ֹͣ
//PA.11 ->1    PA.12->1   ֹͣ
void GoForward(u16 Leftspeed,u16 Rightspeed){
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);						 //PB.13 �����
	GPIO_SetBits(GPIOB,GPIO_Pin_12);						 //PB.12 �����
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);						 //PA.12 �����
	GPIO_SetBits(GPIOA,GPIO_Pin_11);						 //PA.11 �����
	TIM_SetCompare3(TIM4,Leftspeed);//��Ŷ�Ӧ2.4V  �Ա�ֵԽС�������ѹԽ��
	TIM_SetCompare4(TIM4,Rightspeed);//��Ŷ�Ӧ2.4V
}

void GoBack(u16 Leftspeed,u16 Rightspeed){
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);						 //PB.12 �����
	GPIO_SetBits(GPIOB,GPIO_Pin_13);						 //PB.13 �����	
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);						 //PA.11 �����
	GPIO_SetBits(GPIOA,GPIO_Pin_12);						 //PA.12 �����
	TIM_SetCompare3(TIM4,Leftspeed);//��Ŷ�Ӧ2.4V  �Ա�ֵԽС�������ѹԽ��
	TIM_SetCompare4(TIM4,Rightspeed);//��Ŷ�Ӧ2.4V
}
void GoStop(void){
	GPIO_SetBits(GPIOB,GPIO_Pin_12);						 //PB.12 �����
	GPIO_SetBits(GPIOB,GPIO_Pin_13);						 //PB.13 �����
	GPIO_SetBits(GPIOA,GPIO_Pin_12);						 //PA.12 �����
	GPIO_SetBits(GPIOA,GPIO_Pin_11);						 //PA.11 �����

}
//����ת�䣬��ת�������ٶȴ� �����������ַ���
void GoLeft(u16 Leftspeed,u16 Rightspeed){
	GPIO_SetBits(GPIOB,GPIO_Pin_13);						 //PB.13 �����
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);						 //PB.12 �����   ���ַ�����ת
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);						 //PA.12 �����
	GPIO_SetBits(GPIOA,GPIO_Pin_11);						 //PA.11 �����   ����������ת
	TIM_SetCompare3(TIM4,Leftspeed);//��Ŷ�Ӧ2.4V  �Ա�ֵԽС�������ѹԽ��
	TIM_SetCompare4(TIM4,Rightspeed);//��Ŷ�Ӧ2.4V
}
//��ת�������ٶȴ�   ����������ת�����ַ�����ת 
void GoRight(u16 Leftspeed,u16 Rightspeed){
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);						 //PB.13 �����
	GPIO_SetBits(GPIOB,GPIO_Pin_12);						 //PB.12 �����
	GPIO_SetBits(GPIOA,GPIO_Pin_12);						 //PA.12 �����
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);						 //PA.11 �����
	TIM_SetCompare3(TIM4,Leftspeed);//��Ŷ�Ӧ2.4V  �Ա�ֵԽС�������ѹԽ��
	TIM_SetCompare4(TIM4,Rightspeed);//��Ŷ�Ӧ2.4V
}
extern u16 SPEED;
extern u16 AutoSPEED;
extern u16 SuperSPEED;
extern u16 LeftPin1,RightPin1,LeftPin2,RightPin2;
//��װһ��ѭ������
void FollowLine(void){
	if(MODE==0){
	GoStop();//��ͣһ��
	LeftPin1=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4);
	RightPin1=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5);
	LeftPin2=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
	RightPin2=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7);
	//��Ϊ�����ж���˸
	//Ҫ���ж��ǲ���Ҫֹͣ
	if(((LeftPin1||LeftPin2)&&(RightPin1||RightPin2))){
		//����������⵽������ʮ��·��
		LeftPin1=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4);
		RightPin1=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5);
		LeftPin2=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
		RightPin2=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7);
		//BlinkLED(10);
		GoStop();
	}
	if(LeftPin2&&(!LeftPin1)&&(!RightPin1)&&(!RightPin2)){//ֻ����2������
		//��΢ƫ��
		//BlinkLED(1);
		LeftPin1=0;
		RightPin1=0;
		LeftPin2=1;
		RightPin2=0;
		GoLeft(AutoSPEED,AutoSPEED);//����ת��
	}
	if(RightPin2&&(!RightPin1)&&(!LeftPin1)&&(!LeftPin2)){//ֻ����2������
		//��΢ƫ�� 
		//BlinkLED(2);
		LeftPin1=0;
		RightPin1=0;
		LeftPin2=0;
		RightPin2=1;
		GoRight(AutoSPEED,AutoSPEED);//����ת��
	}
	if(LeftPin1&&(!LeftPin2)&&(!RightPin1)&&(!RightPin2)){//ֻ����1������
		//�ǳ�ƫ��
		//BlinkLED(5);
		LeftPin1=1;
		RightPin1=0;
		LeftPin2=0;
		RightPin2=0;
		GoLeft(SuperSPEED,SuperSPEED);//ȫ��ת��
		//delay_ms(900);
	}
	if(LeftPin1&&LeftPin2&&(!RightPin1)&&(!RightPin2)){
		LeftPin1=1;
		RightPin1=0;
		LeftPin2=1;
		RightPin2=0;
		GoLeft(SuperSPEED,SuperSPEED);//ȫ��ת��,������Ҫ��ʱһ�£�����ֱ�ӳ��ȥ��
		//delay_ms(900);
	}
	if(RightPin1&&RightPin2&&(!LeftPin1)&&(!LeftPin2)){
		LeftPin1=0;
		RightPin1=1;
		LeftPin2=0;
		RightPin2=1;
		GoRight(SuperSPEED,SuperSPEED);//ȫ��ת��
		//delay_ms(900);
	}
	if(RightPin1&&(!RightPin2)&&(!LeftPin1)&&(!LeftPin2)){//ֻ����1������
		//�ǳ�ƫ��
		//BlinkLED(8);
		LeftPin1=0;
		RightPin1=1;
		LeftPin2=0;
		RightPin2=0;
		GoRight(SuperSPEED,SuperSPEED);//ȫ��ת��
		//delay_ms(900);
	}

	
	}
	
}
