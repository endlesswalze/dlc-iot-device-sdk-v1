/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Stdio.h"
#include "oled.h"
#include "WS2812.h"
#include "String.h"
#include "sht30.h"
#include "KEY.h"
#include "protocol.h"
#include "system.h"
#include "mcu_api.h"
#include "wifi.h"
#include "LED.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
 
	return ch;
}
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
  uint8_t value;
 float CTtemperature = 0.0;
 float CThumidity = 0.0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
                                                                                      {
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C2_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART4_UART_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
	wifi_protocol_init();
	LED_BLUE();
	HAL_UART_Receive_IT(&huart1,&value,1);
  OLED_Init();
	OLED_DrawBMP(0,0,128,8,BMP0);
	HAL_Delay(800);
	OLED_CLS();
	//SHT30_Init();
	SHT30_Reset();
    if(SHT30_Init() == HAL_OK)
		{
			printf("sht30 init ok.\n");
		  OLED_ShowStr(0, 0,"sht30 init ok.", 2);//��ʾ�ַ���
		  HAL_Delay(3000);
		  OLED_CLS();
		}
    else
    {    
			printf("sht30 init fail.\n");
		  OLED_ShowStr(0, 0,"sht30 init fail.", 2);//��ʾ�ַ���
		  HAL_Delay(3000);
		  OLED_CLS();	
		}

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		wifi_uart_service();
		
		uint8_t recv_dat[6] = {0};
    float temperature = 0.0;
    float humidity = 0.0;
    uint8_t temp[16] = {0};
    uint8_t humi[16] = {0};
		if (Key_Scan(GPIOA, GPIO_PIN_8 )== 0)
        {
            /* code */
					HAL_Delay(20);
					OLED_DrawBMP(0,0,128,8,BMP1);
					HAL_Delay(3000);
	        OLED_CLS();
          //continue;					
        }
    if (Key_Scan(GPIOB, GPIO_PIN_15) == 0)
        {
				printf("It's show time!\n");
				printf("Have your fun!\n");	
				//OLED_ShowStr(0, 6,"It's show time!", 2);	
        OLED_ShowStr(0, 6,"Have your fun!", 2);					
         }
		if (Key_Scan(GPIOB, GPIO_PIN_14) == 0)
        {
            /* code */
					   HAL_Delay(20);
             mcu_reset_wifi();
					if(mcu_get_reset_wifi_flag() == 1)
					{
						LED_GREEN_BL();//WIFI��λ�ɹ�������
					}
          else
          {
					  LED_GREEN_BF();//WIFI��λ�̼���
					}					
					
        }
    if (Key_Scan(GPIOB, GPIO_PIN_13) == 0)
        {
          HAL_Delay(20);  
					mcu_set_wifi_mode(SMART_CONFIG);
          if(mcu_get_wifimode_flag() == 1)
					{
						LED_RED_BL();//����wifi״̬�ɹ�������
					}	else
          {
					  LED_RED_BF();//����wifi״̬ʧ�ܺ켱��
          }					
        }	
		if (Key_Scan(GPIOB, GPIO_PIN_12) == 0)
        {
          HAL_Delay(20);  
					mcu_start_wifitest();
					
        }	

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		switch(mcu_get_wifi_work_state())
         { 
					case SMART_CONFIG_STATE:
						OLED_ShowStr(0, 0,"SMART MODE!", 2);//��ʾ�ַ���//smart config ? ? ? ? LED ? ? ,led? ? ? ? ? ? ? ?
          break;
          case AP_STATE:
          OLED_ShowStr(0, 0,"AP MODE!", 2);//AP? ? ? ? LED? ?
          break;
          case WIFI_NOT_CONNECTED:
          OLED_ShowStr(0, 0,"WiFi CONNECT..", 2);//Wi-Fi ? ? ? ?, ? ? ? ? ? ? ?, LED? ?
					
          break;
          case WIFI_CONNECTED:
          OLED_ShowStr(0, 0,"WiFi CONNECTED!", 2);//? ? ? ? ? ? ? LED? ?
          break;
          default:
						break;
				}
		      HAL_Delay(3000);
		      if(SHT30_Read_Dat(recv_dat) == HAL_OK)
          {
						if(SHT30_Dat_To_Float(recv_dat, &temperature, &humidity)==0)
            { 
						printf("temperature = %f, humidity = %f\n", temperature, humidity);	
						sprintf((char *)temp, "temp:%0.2f", temperature);
						sprintf((char *)humi, "humi:%0.2f", humidity);
						OLED_ShowStr(0, 2,temp, 2);//��ʾ�ַ���
					  OLED_ShowStr(0, 4,humi, 2);//��ʾ�ַ���
				    CTtemperature = temperature*10;
						CThumidity = humidity ;
						all_data_update();
					
            }
            else
            {
                printf("crc check fail.\n");
            }
           }
         else
        {
            printf("read data from sht30 fail.\n");
        }
		
		
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_6;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_SYSCLK;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_SYSCLK;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_SYSCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);

  /* NOTE : This function should not be modified, when the callback is needed,
            the HAL_UART_RxCpltCallback can be implemented in the user file.
   */
	//uint8_t value;
	HAL_UART_Receive_IT(&huart1,&value,1);
	uart_receive_input(value); 
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
