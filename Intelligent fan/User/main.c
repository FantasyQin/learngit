#include "stm32f10x.h" 

#include "delay.h"
#include "bsp_systick.h"
#include "bsp_usart.h"
#include "bsp_fan.h"
#include "bsp_key.h"
#include "bsp_oled.h"
#include "bmp.h"
#include "bsp_ds18b20.h"


int Flag=0,Mode=1,Toggle=0;//��λ��Flag(1,2,3) �� ģʽ��Auto(�Զ�)��Humen(�ֶ�����Toggle(����)

float temperature;//�����¶�ֵ
uint8_t uc, ucDs18b20Id [ 8 ];//����DS18B20���к�

//��ʼ��
void init()
{
	SysTick_Init();
	delay_init();
	USART_Config();
	FAN_Init();
	KEY_GPIO_Config();
	DS18B20_Init();
	
	OLED_Init();
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
  OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
	OLED_Refresh();
}

//OLED��ʾ�¶�
void OLED_Showtemp(void)
{
				temperature = DS18B20_GetTemp_MatchRom(ucDs18b20Id);
				OLED_ShowNum(84,0,temperature,2,12);
				delay_ms(300);
				OLED_Refresh();
}

//����3�����Զ�����
void Fan_con_Auto(void)
{
		OLED_Showtemp();
		switch((int)temperature)//�¿�
		{
			case 24:
			case 25:Flag=1;FAN_Run();TIM_SetCompare1(TIM3, Flag*70);break;
			case 26:Flag=2;FAN_Run();TIM_SetCompare1(TIM3, Flag*70);break;
			case 27:
			case 28:
			case 29:
			case 30:
			case 31:
			case 32:
			case 33:Flag=3;FAN_Run();TIM_SetCompare1(TIM3, Flag*70);break;
			default:Flag=0;FAN_Stop();break;
		}
		OLED_ShowString(84,32,"Auto ",12);
		OLED_ShowNum(84,16,Flag,1,12);
		OLED_Refresh();
}

//���Ȱ�������
void Fan_con(void)
{
		if(Key_Scan(KEY_GPIO_PORT,GPIO_Pin_12)==KEY_ON)//����1������
		{
			if(Toggle==0)
			{
				FAN_Run();
				Flag=3;
				Toggle=1;
				OLED_Clear();
				OLED_ShowString(2,0,"Temperature:",12);
				OLED_ShowString(2,16,"Fan:",12);
				OLED_ShowString(2,32,"Mode:",12);
				OLED_ShowString(2,48,"DS18B20:",12);
				OLED_ShowString(100,0,"C",12);
				OLED_DrawCircle(108,1,1);
				OLED_ShowString(84,48,"Ok",12);
				OLED_ShowNum(84,16,Flag,1,12);
				OLED_ShowString(84,32,"Human",12);
				TIM_SetCompare1(TIM3, Flag*70);
			}
			else if(Toggle==1)
			{
				FAN_Stop();
				Toggle=0;
				OLED_Clear();
				OLED_ShowString(84,16,"OFF",12);
				OLED_ShowString(2,0,"Temperature:",12);
				OLED_ShowString(2,16,"Fan:",12);
				OLED_ShowString(2,32,"Mode:",12);
				OLED_ShowString(2,48,"DS18B20:",12);
				OLED_ShowString(100,0,"C",12);
				OLED_DrawCircle(108,1,1);
				OLED_ShowString(84,48,"Ok",12);
			}
			OLED_Refresh();
		}
		if(Key_Scan(KEY_GPIO_PORT,GPIO_Pin_11)==KEY_ON)//����2���ֶ�������
		{	
			Toggle=1;
			FAN_Run();
			OLED_Clear();
			OLED_ShowString(2,0,"Temperature:",12);
			OLED_ShowString(2,16,"Fan:",12);
			OLED_ShowString(2,32,"Mode:",12);
			OLED_ShowString(2,48,"DS18B20:",12);
			OLED_ShowString(100,0,"C",12);
			OLED_DrawCircle(108,1,1);
			OLED_ShowString(84,48,"Ok",12);
			OLED_Refresh();
			Flag++;
			if(Flag>3)
				Flag=1;
			TIM_SetCompare1(TIM3, Flag*70);
			OLED_ShowString(84,32,"Human",12);
			OLED_ShowNum(84,16,Flag,1,12);
			OLED_Refresh();
		}
		if(Key_Scan(KEY_GPIO_PORT,GPIO_Pin_10)==KEY_ON)//����3���л��Զ������ֶ���
		{
				Toggle=1;
				OLED_Clear();
				OLED_ShowString(2,0,"Temperature:",12);
				OLED_ShowString(2,16,"Fan:",12);
				OLED_ShowString(2,32,"Mode:",12);
				OLED_ShowString(2,48,"DS18B20:",12);
				OLED_ShowString(100,0,"C",12);
				OLED_DrawCircle(108,1,1);
				OLED_ShowString(84,48,"Ok",12);
				OLED_Refresh();
			do
			{
				Fan_con_Auto();
			}while((Key_Scan(KEY_GPIO_PORT,GPIO_Pin_9)==KEY_OFF)&&(Key_Scan(KEY_GPIO_PORT,GPIO_Pin_10)==KEY_OFF)&&(Key_Scan(KEY_GPIO_PORT,GPIO_Pin_11)==KEY_OFF)&&(Key_Scan(KEY_GPIO_PORT,GPIO_Pin_12)==KEY_OFF));
			OLED_Clear();
			OLED_ShowString(2,0,"Temperature:",12);
			OLED_ShowString(2,16,"Fan:",12);
			OLED_ShowString(2,32,"Mode:",12);
			OLED_ShowString(2,48,"DS18B20:",12);
			OLED_ShowString(100,0,"C",12);
			OLED_DrawCircle(108,1,1);
			OLED_ShowString(84,48,"Ok",12);
			OLED_ShowString(84,32,"Human",12);
			Flag++;
			if(Flag>3)
				Flag=1;
			OLED_ShowNum(84,16,Flag,1,12);
			OLED_Refresh();
			FAN_Run();
			TIM_SetCompare1(TIM3, Flag*70);
		}
		if(Key_Scan(KEY_GPIO_PORT,GPIO_Pin_9)==KEY_ON)//����4�������ʾ
		{
			Toggle=1;
			OLED_Clear();
			do
			{
				OLED_ShowChinese(8,10,0,16);//��
				OLED_ShowChinese(26,10,1,16);//��
				OLED_ShowChinese(44,10,2,16);//��
				OLED_ShowChinese(62,10,3,16);//��
				OLED_ShowChinese(80,10,4,16);//��
				OLED_ShowChinese(98,10,5,16);//ѧ
				OLED_ShowChinese(38,40,6,16);//��
				OLED_ShowChinese(56,40,7,16);//��
				OLED_ShowChinese(74,40,8,16);//��
				OLED_Refresh();
			}while((Key_Scan(KEY_GPIO_PORT,GPIO_Pin_9)==KEY_OFF)&&(Key_Scan(KEY_GPIO_PORT,GPIO_Pin_10)==KEY_OFF)&&(Key_Scan(KEY_GPIO_PORT,GPIO_Pin_11)==KEY_OFF)&&(Key_Scan(KEY_GPIO_PORT,GPIO_Pin_12)==KEY_OFF));
			OLED_Clear();
			OLED_ShowString(2,0,"Temperature:",12);
			OLED_ShowString(2,16,"Fan:",12);
			OLED_ShowString(2,32,"Mode:",12);
			OLED_ShowString(2,48,"DS18B20:",12);
			OLED_ShowString(100,0,"C",12);
			OLED_DrawCircle(108,1,1);
			OLED_ShowString(84,48,"Ok",12);
			OLED_ShowString(84,32,"Human",12);
			Flag++;
			if(Flag>3)
				Flag=1;
			OLED_ShowNum(84,16,Flag,1,12);
			OLED_Refresh();
			FAN_Run();
			TIM_SetCompare1(TIM3, Flag*70);
		}
}

//������
int main(void)
{
	init();
	OLED_ShowString(2,0,"Temperature:",12);
	OLED_ShowString(2,16,"Fan:",12);
	OLED_ShowString(2,32,"Mode:",12);
	OLED_ShowString(2,48,"DS18B20:",12);
	OLED_ShowString(100,0,"C",12);
	OLED_DrawCircle(108,1,1);
	OLED_ShowString(84,48,"Ok",12);
	OLED_ShowString(84,16,"OFF",12);
	OLED_Refresh();
	DS18B20_ReadId ( ucDs18b20Id  );// ��ȡ DS18B20 �����к�
	FAN_Stop();
	while(1)
	{
		Fan_con();
		OLED_Showtemp();
	}
}
