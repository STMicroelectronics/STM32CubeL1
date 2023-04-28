/**
  ******************************************************************************
  * @file    LCD/LCD_Blink_Frequency/Src/main.c 
  * @author  MCD Application Team
  * @brief   This example describes how to configure and use GPIOs through 
  *          the STM32L1xx HAL API.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32L1xx_HAL_Examples
  * @{
  */

/** @addtogroup LCD_Blink_Frequency
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern LCD_HandleTypeDef LCDHandle;
uint32_t BlinkCounter = 1; 
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* This sample code shows how to use STM32L1xx LCD HAL API to configures the LCD Blink
     mode and Blink frequency.*/  

  /* STM32L1xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();

  /* Configure the User push-button */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

  /* Initialize LED4 */
  BSP_LED_Init(LED4);

  /* Configure the system clock to 32 MHz */
  SystemClock_Config();

  /* LCD GLASS Initialization */
  BSP_LCD_GLASS_Init();
  
  /* Configure all LCD segments and Coms to blink at frequency LCDCLK/16 */
  __HAL_LCD_BLINK_CONFIG(&LCDHandle, LCD_BLINKMODE_ALLSEG_ALLCOM, LCD_BLINKFREQUENCY_DIV16);
  
  /* Display the "BK0016" message on the LCD GLASS */
  BSP_LCD_GLASS_DisplayString((uint8_t*)"BK0016");

  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 32000000
  *            HCLK(Hz)                       = 32000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSI Frequency(Hz)              = 16000000
  *            PLLMUL                         = 6
  *            PLLDIV                         = 3
  *            Flash Latency(WS)              = 1
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* Enable HSE Oscillator and Activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState            = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL          = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PLLDIV          = RCC_PLL_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* Set Voltage scale1 as MCU will run at 32MHz */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Poll VOSF bit of in PWR_CSR. Wait until it is reset to 0 */
  while (__HAL_PWR_GET_FLAG(PWR_FLAG_VOS) != RESET) {};

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
  clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED4 on */
  BSP_LED_On(LED4);
  while (1)
  {
  }
}
/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == USER_BUTTON_PIN)
  {
    /* Clear The LCD GLASS */
    BSP_LCD_GLASS_Clear();
    
    switch(BlinkCounter)
    {
    case 0:
      /* Configure all LCD segments and Coms to blink at frequency LCDCLK/16 */      
      __HAL_LCD_BLINK_CONFIG(&LCDHandle, LCD_BLINKMODE_ALLSEG_ALLCOM, LCD_BLINKFREQUENCY_DIV16);
      
      /* Display the "BK0016" message on the LCD GLASS */
      BSP_LCD_GLASS_DisplayString((uint8_t*)"BK0016");
      
      /* Increment the Blink frequency */
      BlinkCounter++;
      break;
      
    case  1: 
      /* Configure all LCD segments and Coms to blink at frequency LCDCLK/32 */ 
      __HAL_LCD_BLINK_CONFIG(&LCDHandle, LCD_BLINKMODE_ALLSEG_ALLCOM, LCD_BLINKFREQUENCY_DIV32); 
      
      /* Display the "BK0032" message on the LCD GLASS */
      BSP_LCD_GLASS_DisplayString((uint8_t*)"BK0032");
      
      /* Increment the Blink frequency */
      BlinkCounter++;
      break ;
      
    case  2:
      /* Configure all LCD segments and Coms to blink at frequency LCDCLK/64 */ 
      __HAL_LCD_BLINK_CONFIG(&LCDHandle, LCD_BLINKMODE_ALLSEG_ALLCOM, LCD_BLINKFREQUENCY_DIV64);
      
      /* Display the "BK0064" message on the LCD GLASS */
      BSP_LCD_GLASS_DisplayString((uint8_t*)"BK0064");
      
      /* Increment the Blink frequency */
      BlinkCounter++;
      break ;
      
    case  3:
      /* Configure all LCD segments and Coms to blink at frequency LCDCLK/128 */ 
      __HAL_LCD_BLINK_CONFIG(&LCDHandle, LCD_BLINKMODE_ALLSEG_ALLCOM, LCD_BLINKFREQUENCY_DIV128);
      
      /* Display the "BK0128" message on the LCD GLASS */
      BSP_LCD_GLASS_DisplayString((uint8_t*)"BK0128");
      
      /* Increment the blink frequency */
      BlinkCounter++;
      break ;
      
    case  4:
      /* Configure all LCD segments and Coms to blink at frequency LCDCLK/256 */ 
      __HAL_LCD_BLINK_CONFIG(&LCDHandle, LCD_BLINKMODE_ALLSEG_ALLCOM, LCD_BLINKFREQUENCY_DIV256);
      
      /* Display the "BK0256" message on the LCD GLASS */
      BSP_LCD_GLASS_DisplayString((uint8_t*)"BK0256");
      
      /* Increment the Blink frequency */
      BlinkCounter++;
      break ;
      
    case 5:
      /* Configure all LCD segments and Coms to blink at frequency LCDCLK/512 */ 
      __HAL_LCD_BLINK_CONFIG(&LCDHandle, LCD_BLINKMODE_ALLSEG_ALLCOM, LCD_BLINKFREQUENCY_DIV512);
      
      /* Display the "BK0512" message on the LCD GLASS */
      BSP_LCD_GLASS_DisplayString((uint8_t*)"BK0512");
      
      /* Increment the Blink frequency */
      BlinkCounter++;
      break;
    default:
      /* Configure all LCD segments and Coms to blink at frequency LCDCLK/1024 */ 
      __HAL_LCD_BLINK_CONFIG(&LCDHandle, LCD_BLINKMODE_ALLSEG_ALLCOM, LCD_BLINKFREQUENCY_DIV1024);
      
      /* Display the "BK1024" message on the LCD GLASS */
      BSP_LCD_GLASS_DisplayString((uint8_t*)"BK1024");
      BlinkCounter = 0;
      break ;
    }
  }
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */
