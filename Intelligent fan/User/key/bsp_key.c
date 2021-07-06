#include "bsp_key.h"
#include "delay.h"
#include "bsp_oled.h"

//独立按键GPIO初始化
void KEY_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO ,ENABLE);//重映射需要先使能AFIO时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//只关闭JTAG而保留SWD
	
	RCC_APB2PeriphClockCmd(KEY_GPIO_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = KEY_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(KEY_GPIO_PORT,&GPIO_InitStruct);
}

//按键扫描
uint8_t Key_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin)
{
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_OFF)
	{
		delay_ms(10);
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_OFF);
		return KEY_ON;
	}
	else return KEY_OFF;
}



