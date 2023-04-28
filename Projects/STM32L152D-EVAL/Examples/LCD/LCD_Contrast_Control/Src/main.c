/**
  ******************************************************************************
  * @file    LCD/LCD_Contrast_Control/Src/main.c 
  * @author  MCD Application Team
  * @brief   This example describes how to use the STM32L1xx embedded LCD GLASS
             controller and how to configure the LCD Contrast.
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

/** @addtogroup LCD_Contrast_Control
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ADC_STEP_VALUE       512  /* Eight intervals with ADC_StepValue range */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* ADC handle used for conversion */
ADC_HandleTypeDef hAdc;
/* ADC channel configuration structure declaration */
static ADC_ChannelConfTypeDef hConfigAdc;

__IO uint16_t ADC_ConvertedValue = 0;
__IO uint8_t  Contrast_Range = 0;
uint32_t      LCDContrastArray[8]= {LCD_CONTRASTLEVEL_0, LCD_CONTRASTLEVEL_1, 
                                    LCD_CONTRASTLEVEL_2, LCD_CONTRASTLEVEL_3, 
                                    LCD_CONTRASTLEVEL_4, LCD_CONTRASTLEVEL_5,
                                    LCD_CONTRASTLEVEL_6, LCD_CONTRASTLEVEL_7};

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static HAL_StatusTypeDef  ADC_Config(void);
static void               LCD_GLASS_DisplayContrast(__IO uint8_t value);
static void               Error_Handler(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
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

  /* Initialize LED3 */
  BSP_LED_Init(LED3);

  /* Configure the system clock to 32 MHz */
  SystemClock_Config();

  /* ADC configuration ------------------------------------------------------*/
  if (ADC_Config() != HAL_OK)
  {
    Error_Handler();
  }

  /* LCD GLASS Initialization */
  BSP_LCD_GLASS_Init();
  
  /* Note: LCD glass update and ADC strategy:                                 */
  /* LCD glass update is relatively slow (rough order of 400ms) compared to   */
  /* conversion rate (if reduced to minimum ADC clock speed and maximum       */
  /* sampling rate, one ADC conversion every 100us).                          */
  /* Therefore, ADC conversion are not performed continuously, but rather     */
  /* triggered by software after LCD has been updated.                        */ 
  
  /* Start ADC conversion */
  if (HAL_ADC_Start_DMA(&hAdc, (uint32_t*)&ADC_ConvertedValue, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* Infinite loop */
  while (1)
  {
    /* Configure the LCD Contrast and Display message on the LCD Glass */
    /* Note: Variable "Contrast_Range" is updated when each ADC conversion is */
    /*       completed in function "HAL_ADC_ConvCpltCallback".                */
    LCD_GLASS_DisplayContrast(Contrast_Range);

    /* Start next ADC conversions by software (transfer by DMA is still       */
    /* active), after LCD has been updated.                                   */
    if (HAL_ADC_Start(&hAdc) != HAL_OK)
    {
      Error_Handler();
    }
    
  }
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 32000000
  *            HCLK(Hz)                       = 32000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 8000000
  *            HSI Frequency(Hz)              = 16000000
  *            PLLMUL                         = 12
  *            PLLDIV                         = 3
  *            Flash Latency(WS)              = 1
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};

  /* Enable HSE Oscillator and Activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType      = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState            = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState        = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource       = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL          = RCC_PLL_MUL12;
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
  * @brief  Configures the different ADC resources (Clock, GPIO ports...).
  * @retval HAL_StatusTypeDef
  */
static HAL_StatusTypeDef ADC_Config(void)
{
  /*## Configure the ADC #####################################################*/
  
  /* Set ADC instance */
  hAdc.Instance = ADC_INSTANCE;
  
  /* Configuration of ADC init structure: ADC parameters and regular group */
  hAdc.Init.ClockPrescaler        = ADC_CLOCK_ASYNC_DIV4;          /* ADC clock equal to HSI frequency divided by 4: 4MHz */
  hAdc.Init.Resolution            = ADC_RESOLUTION_12B;
  hAdc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
  hAdc.Init.ScanConvMode          = DISABLE;                       /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
  hAdc.Init.EOCSelection          = ADC_EOC_SEQ_CONV;
  hAdc.Init.LowPowerAutoWait      = ADC_AUTOWAIT_DISABLE;
  hAdc.Init.LowPowerAutoPowerOff  = ADC_AUTOPOWEROFF_DISABLE;
  hAdc.Init.ChannelsBank          = ADC_CHANNELS_BANK_A;
  hAdc.Init.ContinuousConvMode    = DISABLE;                       /* Continuous mode disabled to trig each conversion by software after LCD has been updated */
  hAdc.Init.NbrOfConversion       = 1;                             /* Parameter discarded because sequencer is disabled */
  hAdc.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
  hAdc.Init.NbrOfDiscConversion   = 1;                             /* Parameter discarded because sequencer is disabled */
  hAdc.Init.ExternalTrigConv      = ADC_SOFTWARE_START;            /* Trig of conversion start done by software */
  hAdc.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hAdc.Init.DMAContinuousRequests = ENABLE;
  
  /* Init ADC */
  if (HAL_ADC_Init(&hAdc) != HAL_OK)
  {
    return HAL_ERROR;
  }

  /* Configuration of channel on ADC regular group on rank 1 */
  /* Note: Considering IT occurring after each ADC conversion (IT by DMA end  */
  /*       of transfer), select sampling time and ADC clock with sufficient   */
  /*       duration to not create an overhead situation in IRQHandler.        */
  hConfigAdc.Channel       = ADC_CHANNEL;
  hConfigAdc.SamplingTime  = ADC_SAMPLETIME_192CYCLES;
  hConfigAdc.Rank          = ADC_REGULAR_RANK_1;
  HAL_ADC_ConfigChannel(&hAdc, &hConfigAdc);
  
  return HAL_OK;
}

/**
  * @brief  Conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    /* Calculate the Contrast range value */  
    Contrast_Range = (uint8_t)(ADC_ConvertedValue / ADC_STEP_VALUE);

}

/**
  * @brief  Configures the LCD Contrast and Display Message on the LCD GLASS.
  * @param  value: LCD CONTRAST range. 
  * @retval None
  */
static void LCD_GLASS_DisplayContrast(__IO uint8_t value)
{
  /* Configures the LCD Contrast Maximum Voltage according to the value variable */
  BSP_LCD_GLASS_Contrast(LCDContrastArray[value]);
  
  switch (value)
  {
    case 0 :
      /* Display the "CONTR2V6" message on the LCD GLASS */
      BSP_LCD_GLASS_DisplayString((uint8_t*)"CNTR2V6");
      break;
    case 1 :
      /* Display the "CONTR2V7" message on the LCD GLASS */
      BSP_LCD_GLASS_DisplayString((uint8_t*)"CNTR2V7");
      break;
    case 2 :
      /* Display the "CONTR2V8" message on the LCD GLASS */
      BSP_LCD_GLASS_DisplayString((uint8_t*)"CNTR2V8");
      break;
    case 3 :
      /* Display the "CONTR3V0" message on the LCD GLASS */
      BSP_LCD_GLASS_DisplayString((uint8_t*)"CNTR3V0");
      break;
    case 4 :
      /* Display the "CONTR3V1" message on the LCD GLASS */
      BSP_LCD_GLASS_DisplayString((uint8_t*)"CNTR3V1");
      break;
    case 5 :
      /* Display the "CONTR3V2" message on the LCD GLASS */
      BSP_LCD_GLASS_DisplayString((uint8_t*)"CNTR3V2");
      break;
    case 6 :
      /* Display the "CONTR3V4" message on the LCD GLASS */
      BSP_LCD_GLASS_DisplayString((uint8_t*)"CNTR3V4");
      break;
    default :
      /* Display the "CONTR3V5" message on the LCD GLASS */
      BSP_LCD_GLASS_DisplayString((uint8_t*)"CNTR3V5");
      break;
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED3 on */
  BSP_LED_On(LED3);
  while (1)
  {
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
