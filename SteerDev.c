/*
#作者：LARK
#日期：2023/6/1
#描述：定义舵机的驱动程序（包括定时器的初始化，PWM生成）
*/
#include "stm32f10x_tim.h"
#include "stdint.h"
#include "SteerDev.h"

//初始化定时器输出PWM
void SteerInit(u16 arr,u16 psc){
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//使能定时器2时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	
	//GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5    这里不需要映射 
 
	//设置该引脚为复用输出功能,输出TIM2 CH1的PWM脉冲波形	GPIOA.0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
	GPIO_SetBits(GPIOA,GPIO_Pin_0);
	//初始化TIM2 周期3000/100000=30ms;
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM2 Channel-1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM2 OC1

	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //使能TIM2在CCR1上的预装载寄存器
 
	TIM_Cmd(TIM2, ENABLE);  //使能TIM2
		
	//TIM_SetCompare1(TIM2,arr/4);//大概对应2.4V	
}

void SwipeCard(void){
	TIM_SetCompare1(TIM2,195);//185对应竖直角度，195对应向右90° 180对应向左45° 175对应向左90° 左右以面向铜黄圈为标准
}

void ResetCard(void){
	TIM_SetCompare1(TIM2,185);
}	

