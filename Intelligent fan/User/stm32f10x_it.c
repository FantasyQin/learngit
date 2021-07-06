/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_oled.h"
#include "bsp_usart.h"
#include "bsp_fan.h"
#include "bsp_key.h"
void Fan_con_Auto(void);
/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

//void SR501_IRQHandler(void)
//{
//  //确保是否产生了EXTI Line中断
//	if(EXTI_GetITStatus(SR501_INT_EXTI_LINE) != RESET) 
//	{
//    //清除中断标志位
//		EXTI_ClearITPendingBit(SR501_INT_EXTI_LINE);   	
//	}  
//}

// 串口中断服务函数,蓝牙控制
void DEBUG_USART_IRQHandler(void)
{
  uint8_t ucTemp;
	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
	{		
		ucTemp = USART_ReceiveData(DEBUG_USARTx);
    USART_SendData(DEBUG_USARTx,ucTemp);   	
		switch(ucTemp)
				{
					case '0':
						FAN_Stop();
						OLED_Clear();
						OLED_ShowString(84,16,"OFF",12);
						OLED_ShowString(2,0,"Temperature:",12);
						OLED_ShowString(2,16,"Fan:",12);
						OLED_ShowString(2,32,"Mode:",12);
						OLED_ShowString(2,48,"DS18B20:",12);
						OLED_ShowString(100,0,"C",12);
						OLED_DrawCircle(108,1,1);
						OLED_ShowString(84,48,"Ok",12);
						OLED_ShowString(84,32,"Human",12);
						OLED_Refresh();
						break;
					case '1':
						FAN_Run();
						TIM_SetCompare1(TIM3, 3*70);
						OLED_Clear();
						OLED_ShowNum(84,16,3,1,12);
						OLED_ShowString(2,0,"Temperature:",12);
						OLED_ShowString(2,16,"Fan:",12);
						OLED_ShowString(2,32,"Mode:",12);
						OLED_ShowString(2,48,"DS18B20:",12);
						OLED_ShowString(100,0,"C",12);
						OLED_DrawCircle(108,1,1);
						OLED_ShowString(84,48,"Ok",12);
						OLED_Refresh();
						break;
					case '2':
						OLED_Clear();
						OLED_ShowString(2,0,"Temperature:",12);
						OLED_ShowString(2,16,"Fan:",12);
						OLED_ShowString(2,32,"Mode:",12);
						OLED_ShowString(2,48,"DS18B20:",12);
						OLED_ShowString(100,0,"C",12);
						OLED_DrawCircle(108,1,1);
						OLED_ShowString(84,48,"Ok",12);
						OLED_Refresh();
						do{
						ucTemp = USART_ReceiveData(DEBUG_USARTx);
						Fan_con_Auto();
						}while(ucTemp!='3'&&((Key_Scan(KEY_GPIO_PORT,GPIO_Pin_9)==KEY_OFF)&&(Key_Scan(KEY_GPIO_PORT,GPIO_Pin_10)==KEY_OFF)&&(Key_Scan(KEY_GPIO_PORT,GPIO_Pin_11)==KEY_OFF)&&(Key_Scan(KEY_GPIO_PORT,GPIO_Pin_12)==KEY_OFF)));
						break;
					case '4':FAN_Run();
									 TIM_SetCompare1(TIM3, 1*70);
									 OLED_Clear();
									 OLED_ShowString(2,0,"Temperature:",12);
									 OLED_ShowString(2,16,"Fan:",12);
									 OLED_ShowString(2,32,"Mode:",12);
									 OLED_ShowString(2,48,"DS18B20:",12);
									 OLED_ShowString(100,0,"C",12);
									 OLED_DrawCircle(108,1,1);
									 OLED_ShowString(84,48,"Ok",12);
									 OLED_ShowString(84,32,"Human",12);
									 OLED_ShowNum(84,16,1,1,12);
									 OLED_Refresh();
									 break;
					case '5':FAN_Run();
									 TIM_SetCompare1(TIM3, 2*70);
									 OLED_Clear();
									 OLED_ShowString(2,0,"Temperature:",12);
									 OLED_ShowString(2,16,"Fan:",12);
									 OLED_ShowString(2,32,"Mode:",12);
									 OLED_ShowString(2,48,"DS18B20:",12);
									 OLED_ShowString(100,0,"C",12);
									 OLED_DrawCircle(108,1,1);
									 OLED_ShowString(84,48,"Ok",12);
									 OLED_ShowString(84,32,"Human",12);
									 OLED_ShowNum(84,16,2,1,12);
									 OLED_Refresh();
									 break;
					case '6':FAN_Run();
									 TIM_SetCompare1(TIM3, 3*70);
									 OLED_Clear();
									 OLED_ShowString(2,0,"Temperature:",12);
									 OLED_ShowString(2,16,"Fan:",12);
									 OLED_ShowString(2,32,"Mode:",12);
									 OLED_ShowString(2,48,"DS18B20:",12);
									 OLED_ShowString(100,0,"C",12);
									 OLED_DrawCircle(108,1,1);
									 OLED_ShowString(84,48,"Ok",12);
									 OLED_ShowString(84,32,"Human",12);
									 OLED_ShowNum(84,16,3,1,12);
									 OLED_Refresh();
									 break;
					default:break;
				}
	}	 
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
