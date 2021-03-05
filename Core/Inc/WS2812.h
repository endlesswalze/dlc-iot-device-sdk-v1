#include "gpio.h"

//#define 	RGB_LED 	GPIO_Pin_9
#define	  RGB_LED_HIGH	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_SET)
#define 	RGB_LED_LOW	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_RESET)

void RGB_LED_Red(void);
void RGB_LED_Green(void);
void RGB_LED_Blue(void);
