/*******************************************************************************
//坡道循迹小车
//作者：化作尘
//CSDN：化作尘
//哔哩哔哩：化作尘my
//修改日期:2021年4月2日16:33:58
//版本：V1.0								  
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
//主函数
//t = 0.5ms——————-舵机会转动 0 °
//t = 1.0ms——————-舵机会转动 45°
//t = 1.5ms——————-舵机会转动 90°
//t = 2.0ms——————-舵机会转动 135°
//t = 2.5ms——————-舵机会转动180°
extern u16 USART_RX_STA;
u16 LeftPin1=0,RightPin1=0,LeftPin2=0,RightPin2=0;
u16 SPEED=5300;//全局速度设置 速度应该从10设置到190   190为最慢
u8 MODE=1;//模式设置 默认遥控模式
u8 Dir;//小车方向情况
u16 AutoSPEED=5000;//0-7199 0非常快，5000可以正常运行
u16 SuperSPEED=4800;//较快的速度，用在极速的情况下3000较快
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	My_USART1_Init(9600);
	LED_Init();
	delay_init(); //延时初始化
	MotorInit(7199,99);//初始化电机PWM波  对PWM波的频率要求在1K以上20k以下，1k以下无法稳定驱动，20k以上转速过高只有尖刺声
	SteerInit(199,7200);//初始化舵机PWM波 初始化周期为20ms
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
				//有两个都检测到，遇到十字路口
				//BlinkLED(10);
				GoStop();
				BlinkLED(10);
				SwipeCard();//刷卡
				delay_ms(3000);//等待三秒
				BlinkLED(10);
				ResetCard();//恢复继续往前走
				delay_ms(5000);//等待两秒
				BlinkLED(10);
				GoForward(AutoSPEED,AutoSPEED);
				delay_ms(2000);//等待三秒
			}
			if(LeftPin2&&(!LeftPin1)&&(!RightPin1)&&(!RightPin2)){//只有左2被触发
				//稍微偏左
				//BlinkLED(1);
				GoLeft(AutoSPEED,AutoSPEED);//半速转弯
			}
			if(RightPin2&&(!RightPin1)&&(!LeftPin1)&&(!LeftPin2)){//只有右2被触发
				//稍微偏右 
				//BlinkLED(2);
				GoRight(AutoSPEED,AutoSPEED);//半速转弯
			}
			if(LeftPin1&&(!LeftPin2)&&(!RightPin1)&&(!RightPin2)){//只有左1被触发
				GoLeft(SuperSPEED,SuperSPEED);//全速转弯
				while(!RightPin2){
					GoLeft(SuperSPEED,SuperSPEED);//全速转弯 直到右边碰到黑线
				}
			}
			if(LeftPin1&&LeftPin2&&(!RightPin1)&&(!RightPin2)){
				GoLeft(SuperSPEED,SuperSPEED);//全速转弯
				while(!RightPin2){
					GoLeft(SuperSPEED,SuperSPEED);//全速转弯 直到右边碰到黑线
				}
			}
			if(RightPin1&&RightPin2&&(!LeftPin1)&&(!LeftPin2)){
				GoRight(SuperSPEED,SuperSPEED);//全速转弯
				while(!LeftPin2){
					GoRight(SuperSPEED,SuperSPEED);//全速转弯直到左边碰到黑线
				}
				//delay_ms(500);
			}
			if(RightPin1&&(!RightPin2)&&(!LeftPin1)&&(!LeftPin2)){//只有右1被触发
				//非常偏右
				//BlinkLED(8);
				GoRight(SuperSPEED,SuperSPEED);//全速转弯
				while(!LeftPin2){
					GoRight(SuperSPEED,SuperSPEED);//全速转弯直到左边碰到黑线
				}
			}
			if((!LeftPin1)&&(!LeftPin2)&&(!RightPin1)&&(!RightPin2)){
			//如果全都没有检测到黑线直走
				GoForward(AutoSPEED,AutoSPEED);
			}
		
		}
	}

}
