#include "bsp_fan.h"

//风扇GPIO初始化
static void FAN_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//结构体初始化
	RCC_APB2PeriphClockCmd(FAN_GPIO_CLK,ENABLE);//打开GPIO时钟
	GPIO_InitStructure.GPIO_Pin = FAN_GPIO_PIN;//输出针脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//输出模式，推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//配置速度
	GPIO_Init(FAN_GPIO_PORT,&GPIO_InitStructure);//配置CRL（端口配置低寄存器）
	
	RCC_APB2PeriphClockCmd(TIM_CH1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin = TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(TIM_CH1_PORT, &GPIO_InitStructure);
}

//定时器初始化
static void TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(TIM_CLK, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period=TIM_PERIOD; //周期为100
	TIM_TimeBaseStructure.TIM_Prescaler=TIM_PSC;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1; //pwm模式1，小于比较捕获寄存器的值为有效电平
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High; //有效电平为高电平
//	TIM_OCInitStructure.TIM_Pulse=TIM_PULSE;//占空比
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_Cmd(TIM3, ENABLE); //开计数器
}

//开风扇
void FAN_Run(void)
{
	IN1_FAN(ON);
	IN2_FAN(OFF);
}

//关风扇
void FAN_Stop(void)
{
	IN1_FAN(OFF);
	IN2_FAN(OFF);
}

//初始化
void FAN_Init(void)
{
	FAN_GPIO_Config();
	TIM_Mode_Config();	
}

