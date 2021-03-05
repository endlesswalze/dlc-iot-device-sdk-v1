#ifndef __ASCII_H
#define __ASCII_H

#include "KEY.h"
#include "Stdio.h"
#include "gpio.h"

uint8_t Key_Scan(GPIO_TypeDef *GPIOx,uint16_t GPIO_PIN)
{
    if (HAL_GPIO_ReadPin(GPIOx,GPIO_PIN) == 1)
    {
        /* code */
        while (HAL_GPIO_ReadPin(GPIOx,GPIO_PIN) == 1)
				//;
        return 1;
    }
    else
    {
        return 0;
    } 
}
#endif
