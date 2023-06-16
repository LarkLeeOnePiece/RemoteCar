/*
#作者：LARK
#日期：2023/6/1
#描述：定义舵机的驱动程序（包括定时器的初始化，PWM生成）
*/
// t = 0.5ms——————-舵机会转动 0 °
//t = 1.0ms——————-舵机会转动 45°
//t = 1.5ms——————-舵机会转动 90°
//t = 2.0ms——————-舵机会转动 135°
//t = 2.5ms——————-舵机会转动180°

void SteerInit(u16 arr,u16 psc);

void SwipeCard(void);//刷卡

void ResetCard(void);//手臂复原
