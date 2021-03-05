#include "WS2812.h"
#include "Stdio.h"


//void RGB_LED_Init(void)
//{
//	GPIO_InitTypeDef  GPIO_InitStructure;
// 	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
//	GPIO_Init(GPIOB, &GPIO_InitStructure);					
//	GPIO_SetBits(GPIOB,GPIO_Pin_9);						 
//}

/********************************************************/
//
/********************************************************/
void RGB_LED_Write0(void)
{
	RGB_LED_HIGH;
	__nop();__nop();__nop();//__nop();__nop();__nop(); 
	RGB_LED_LOW;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();//__nop();__nop();__nop();
	//__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	//__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	//__nop();__nop();
}

/********************************************************/
//写0高电平375ns；写0低电平875ns
/********************************************************/

void RGB_LED_Write1(void)
{
	RGB_LED_HIGH;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();//__nop();__nop();__nop();
	//__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	//__nop();__nop();
	RGB_LED_LOW;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();//__nop();__nop();__nop();
	//__nop();__nop();
}

/********************************************************/
//写1高电平875ns；写1低电平875ns
/********************************************************/
void RGB_LED_Reset(void)
{
	RGB_LED_LOW;
	HAL_Delay(1);
}

void RGB_LED_Write_Byte(uint8_t byte)
{
	uint8_t i;

	for(i=0;i<8;i++)
		{
			if(byte&0x80)
				{
					RGB_LED_Write1();
			}
			else
				{
					RGB_LED_Write0();
			}
		byte <<= 1;
	}
}

void RGB_LED_Write_24Bits(uint8_t green,uint8_t red,uint8_t blue)
{
	RGB_LED_Write_Byte(green);
	RGB_LED_Write_Byte(red);
	RGB_LED_Write_Byte(blue);
}

void RGB_LED_Red(void)
{
	 uint8_t i;
	//4个LED全彩灯
	for(i=0;i<4;i++)
		{
			RGB_LED_Write_24Bits(0, 0xff, 0);
	}
}

void RGB_LED_Green(void)
{
	uint8_t i;

	for(i=0;i<4;i++)
		{
			RGB_LED_Write_24Bits(0xff, 0, 0);
	}
}

void RGB_LED_Blue(void)
{
	uint8_t i;

	for(i=0;i<4;i++)
		{
			RGB_LED_Write_24Bits(0, 0, 0xff);
	}
}
