#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "stm32f10x.h"

#define KEY_ON  1
#define KEY_OFF  0

#define KEY_GPIO_PIN    GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12
#define KEY_GPIO_PORT   GPIOA
#define KEY_GPIO_CLK    RCC_APB2Periph_GPIOA

void KEY_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);

#endif /*__BSP_KEY_H*/
