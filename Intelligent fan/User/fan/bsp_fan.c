#include "bsp_fan.h"

//����GPIO��ʼ��
static void FAN_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;//�ṹ���ʼ��
	RCC_APB2PeriphClockCmd(FAN_GPIO_CLK,ENABLE);//��GPIOʱ��
	GPIO_InitStructure.GPIO_Pin = FAN_GPIO_PIN;//������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//���ģʽ���������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�����ٶ�
	GPIO_Init(FAN_GPIO_PORT,&GPIO_InitStructure);//����CRL���˿����õͼĴ�����
	
	RCC_APB2PeriphClockCmd(TIM_CH1_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin = TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(TIM_CH1_PORT, &GPIO_InitStructure);
}

//��ʱ����ʼ��
static void TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(TIM_CLK, ENABLE);
	
	TIM_TimeBaseStructure.TIM_Period=TIM_PERIOD; //����Ϊ100
	TIM_TimeBaseStructure.TIM_Prescaler=TIM_PSC;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1; //pwmģʽ1��С�ڱȽϲ���Ĵ�����ֵΪ��Ч��ƽ
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High; //��Ч��ƽΪ�ߵ�ƽ
//	TIM_OCInitStructure.TIM_Pulse=TIM_PULSE;//ռ�ձ�
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_Cmd(TIM3, ENABLE); //��������
}

//������
void FAN_Run(void)
{
	IN1_FAN(ON);
	IN2_FAN(OFF);
}

//�ط���
void FAN_Stop(void)
{
	IN1_FAN(OFF);
	IN2_FAN(OFF);
}

//��ʼ��
void FAN_Init(void)
{
	FAN_GPIO_Config();
	TIM_Mode_Config();	
}

