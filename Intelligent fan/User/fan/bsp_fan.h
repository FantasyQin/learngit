#ifndef __BSP_FAN_H
#define __BSP_FAN_H

#include "stm32f10x.h"

#define 						FAN_GPIO_CLK          RCC_APB2Periph_GPIOB
#define 						FAN_GPIO_PORT         GPIOB
#define 						FAN_GPIO_PIN          GPIO_Pin_7|GPIO_Pin_8 //��������

#define             TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define             TIM_CH1_PORT          GPIOA
#define             TIM_CH1_PIN           GPIO_Pin_6						//pwm����

// ARR ���Զ���װ�ؼĴ�����ֵ
// CLK_cnt����������ʱ�ӣ����� Fck_int / (psc+1) = 72M/(psc+1)
// PWM �źŵ����� T = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// ռ�ձ�P=CCR/(ARR+1)
#define             TIM_CLK               RCC_APB1Periph_TIM3
#define             TIM_PERIOD            199
#define             TIM_PSC               7199
#define             TIM_PULSE             8

#define ON  1	//��
#define OFF 0	//��

#define IN1_FAN(a) if (a) \
												GPIO_SetBits(GPIOB,GPIO_Pin_7);\
										else  GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define IN2_FAN(a) if (a) \
												GPIO_SetBits(GPIOB,GPIO_Pin_8);\
										else  GPIO_ResetBits(GPIOB,GPIO_Pin_8) 
											
//extern volatile int Fan,Mode;
											
void FAN_Run(void);
void FAN_Stop(void);
void Fan_Con(void);
void FAN_Init(void);

#endif  //__BSP_FAN_H
