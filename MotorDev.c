#include "MotorDev.h"
extern u8 MODE;
//初始化定时器输出PWM
void MotorInit(u16 arr,u16 psc){
		GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_OCInitTypeDef TIM_OCInitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //①使能定时器 4 时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE); //①使能 GPIO B 和 AFIO 复用功能时钟
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //分别对应TIM4_CH3
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure); //①初始化 GPIO B
		GPIO_SetBits(GPIOB,GPIO_Pin_8);
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //分别对应TIM4_CH4
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure); //①初始化 GPIO B
		GPIO_SetBits(GPIOB,GPIO_Pin_9);
		//初始化 TIM4
		TIM_TimeBaseStructure.TIM_Period = arr; //设置在自动重装载周期值
		TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置预分频值
		TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM 向上计数模式
		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //③初始化 TIMx
		//初始化 TIM4 Channe3|4 PWM 模式
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择 PWM 模式 2
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性高
		TIM_OC3Init(TIM4, &TIM_OCInitStructure); //④初始化外设 TIM4 OC3
		TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); //使能预装载寄存器
		TIM_OC4Init(TIM4, &TIM_OCInitStructure); //④初始化外设 TIM4 OC4
		TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); //使能预装载寄存器
		TIM_Cmd(TIM4, ENABLE); //⑤使能 TIM4
		
		TIM_SetCompare3(TIM4,arr/4);//大概对应2.4V  对比值越小，输出电压越大，对应左轮
		TIM_SetCompare4(TIM4,arr/4);//大概对应2.4V，PB9  对应右轮
		
}

void DirInit(void){
	 GPIO_InitTypeDef  GPIO_InitStructure;
 	
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PB端口时钟
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
		
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //PB.12端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.12
	 GPIO_SetBits(GPIOB,GPIO_Pin_12);						 //PB.12 输出高
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //PB.13端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.12
	 GPIO_ResetBits(GPIOB,GPIO_Pin_13);						 //PB.13 输出低
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				 //PA.11端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.11
	 GPIO_SetBits(GPIOA,GPIO_Pin_11);						 //PA.11 输出高
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //PA.12端口配置
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA.12
	 GPIO_ResetBits(GPIOA,GPIO_Pin_12);						 //PA.12 输出低
}

//PB.12 PB.13控制左轮电机旋转方向
//PB.12 ->1    PB.13->0   正向旋转
//PB.12 ->0    PB.13->1   反向旋转
//PB.12 ->0    PB.13->0   停止
//PB.12 ->1    PB.13->1   停止
//PA11,PA12控制右轮电机旋转方向
//PA.11 ->1    PA.12->0   正向旋转
//PA.11 ->0    PA.12->1   反向旋转
//PA.11 ->0    PA.12->0   停止
//PA.11 ->1    PA.12->1   停止
void GoForward(u16 Leftspeed,u16 Rightspeed){
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);						 //PB.13 输出低
	GPIO_SetBits(GPIOB,GPIO_Pin_12);						 //PB.12 输出高
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);						 //PA.12 输出低
	GPIO_SetBits(GPIOA,GPIO_Pin_11);						 //PA.11 输出高
	TIM_SetCompare3(TIM4,Leftspeed);//大概对应2.4V  对比值越小，输出电压越大
	TIM_SetCompare4(TIM4,Rightspeed);//大概对应2.4V
}

void GoBack(u16 Leftspeed,u16 Rightspeed){
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);						 //PB.12 输出低
	GPIO_SetBits(GPIOB,GPIO_Pin_13);						 //PB.13 输出高	
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);						 //PA.11 输出低
	GPIO_SetBits(GPIOA,GPIO_Pin_12);						 //PA.12 输出高
	TIM_SetCompare3(TIM4,Leftspeed);//大概对应2.4V  对比值越小，输出电压越大
	TIM_SetCompare4(TIM4,Rightspeed);//大概对应2.4V
}
void GoStop(void){
	GPIO_SetBits(GPIOB,GPIO_Pin_12);						 //PB.12 输出高
	GPIO_SetBits(GPIOB,GPIO_Pin_13);						 //PB.13 输出高
	GPIO_SetBits(GPIOA,GPIO_Pin_12);						 //PA.12 输出高
	GPIO_SetBits(GPIOA,GPIO_Pin_11);						 //PA.11 输出高

}
//差速转弯，左转，右轮速度大 右轮正向，左轮反向
void GoLeft(u16 Leftspeed,u16 Rightspeed){
	GPIO_SetBits(GPIOB,GPIO_Pin_13);						 //PB.13 输出高
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);						 //PB.12 输出低   左轮反向旋转
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);						 //PA.12 输出低
	GPIO_SetBits(GPIOA,GPIO_Pin_11);						 //PA.11 输出高   右轮正向旋转
	TIM_SetCompare3(TIM4,Leftspeed);//大概对应2.4V  对比值越小，输出电压越大
	TIM_SetCompare4(TIM4,Rightspeed);//大概对应2.4V
}
//右转，左轮速度大   左轮正向旋转，右轮反向旋转 
void GoRight(u16 Leftspeed,u16 Rightspeed){
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);						 //PB.13 输出低
	GPIO_SetBits(GPIOB,GPIO_Pin_12);						 //PB.12 输出高
	GPIO_SetBits(GPIOA,GPIO_Pin_12);						 //PA.12 输出高
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);						 //PA.11 输出低
	TIM_SetCompare3(TIM4,Leftspeed);//大概对应2.4V  对比值越小，输出电压越大
	TIM_SetCompare4(TIM4,Rightspeed);//大概对应2.4V
}
extern u16 SPEED;
extern u16 AutoSPEED;
extern u16 SuperSPEED;
extern u16 LeftPin1,RightPin1,LeftPin2,RightPin2;
//封装一个循迹函数
void FollowLine(void){
	if(MODE==0){
	GoStop();//先停一下
	LeftPin1=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4);
	RightPin1=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5);
	LeftPin2=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
	RightPin2=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7);
	//意为产生中断闪烁
	//要先判断是不是要停止
	if(((LeftPin1||LeftPin2)&&(RightPin1||RightPin2))){
		//有两个都检测到，遇到十字路口
		LeftPin1=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4);
		RightPin1=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5);
		LeftPin2=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
		RightPin2=GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7);
		//BlinkLED(10);
		GoStop();
	}
	if(LeftPin2&&(!LeftPin1)&&(!RightPin1)&&(!RightPin2)){//只有左2被触发
		//稍微偏左
		//BlinkLED(1);
		LeftPin1=0;
		RightPin1=0;
		LeftPin2=1;
		RightPin2=0;
		GoLeft(AutoSPEED,AutoSPEED);//半速转弯
	}
	if(RightPin2&&(!RightPin1)&&(!LeftPin1)&&(!LeftPin2)){//只有右2被触发
		//稍微偏右 
		//BlinkLED(2);
		LeftPin1=0;
		RightPin1=0;
		LeftPin2=0;
		RightPin2=1;
		GoRight(AutoSPEED,AutoSPEED);//半速转弯
	}
	if(LeftPin1&&(!LeftPin2)&&(!RightPin1)&&(!RightPin2)){//只有左1被触发
		//非常偏左
		//BlinkLED(5);
		LeftPin1=1;
		RightPin1=0;
		LeftPin2=0;
		RightPin2=0;
		GoLeft(SuperSPEED,SuperSPEED);//全速转弯
		//delay_ms(900);
	}
	if(LeftPin1&&LeftPin2&&(!RightPin1)&&(!RightPin2)){
		LeftPin1=1;
		RightPin1=0;
		LeftPin2=1;
		RightPin2=0;
		GoLeft(SuperSPEED,SuperSPEED);//全速转弯,而且需要延时一下，否则直接冲出去了
		//delay_ms(900);
	}
	if(RightPin1&&RightPin2&&(!LeftPin1)&&(!LeftPin2)){
		LeftPin1=0;
		RightPin1=1;
		LeftPin2=0;
		RightPin2=1;
		GoRight(SuperSPEED,SuperSPEED);//全速转弯
		//delay_ms(900);
	}
	if(RightPin1&&(!RightPin2)&&(!LeftPin1)&&(!LeftPin2)){//只有右1被触发
		//非常偏右
		//BlinkLED(8);
		LeftPin1=0;
		RightPin1=1;
		LeftPin2=0;
		RightPin2=0;
		GoRight(SuperSPEED,SuperSPEED);//全速转弯
		//delay_ms(900);
	}

	
	}
	
}
