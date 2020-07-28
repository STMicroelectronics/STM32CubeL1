/**
  ******************************************************************************
  * @file    RTC/RTC_Tamper/Src/main.c
  * @author  MCD Application Team
  * @brief   This sample code shows how to use STM32L1xx RTC HAL API to write/read
  *          data to/from RTC Backup data registers and demonstrates the Tamper
  *          detection feature.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32L1xx_HAL_Examples
  * @{
  */

/** @addtogroup RTC_Tamper
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* RTC handler declaration */
RTC_HandleTypeDef RtcHandle;

__IO FlagStatus TamperStatus = RESET;

/* Backup registers table */
uint32_t aBKPDataReg[BACKUP_COUNT] =
{
  RTC_BKP_DR0,  RTC_BKP_DR1,  RTC_BKP_DR2,
  RTC_BKP_DR3,  RTC_BKP_DR4,  RTC_BKP_DR5,
  RTC_BKP_DR6,  RTC_BKP_DR7,  RTC_BKP_DR8,
  RTC_BKP_DR9,  RTC_BKP_DR10, RTC_BKP_DR11,
  RTC_BKP_DR12, RTC_BKP_DR13, RTC_BKP_DR14,
  RTC_BKP_DR15, RTC_BKP_DR16, RTC_BKP_DR17,
  RTC_BKP_DR18, RTC_BKP_DR19, RTC_BKP_DR20,
  RTC_BKP_DR21, RTC_BKP_DR22, RTC_BKP_DR23,
  RTC_BKP_DR24, RTC_BKP_DR25, RTC_BKP_DR26,
  RTC_BKP_DR27, RTC_BKP_DR28, RTC_BKP_DR29,
  RTC_BKP_DR30, RTC_BKP_DR31
};


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  uint32_t index = 0;
  RTC_TamperTypeDef  stamperstructure;
  
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

  /* Configure LED3 and LED4 */
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);

  /* Configure the system clock to 32 MHz */
  SystemClock_Config();

  /* Configure User push-button button */
  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);
  
  /*##-1- Configure the RTC peripheral #######################################*/
  /* Configure RTC prescaler and RTC data registers */
  /* RTC configured as follows:
      - Hour Format    = Format 24
      - Asynch Prediv  = Value according to source clock
      - Synch Prediv   = Value according to source clock
      - OutPut         = Output Disable
      - OutPutPolarity = High Polarity
      - OutPutType     = Open Drain */
  RtcHandle.Init.HourFormat     = RTC_HOURFORMAT_24;
  RtcHandle.Init.AsynchPrediv   = RTC_ASYNCH_PREDIV;
  RtcHandle.Init.SynchPrediv    = RTC_SYNCH_PREDIV;
  RtcHandle.Init.OutPut         = RTC_OUTPUT_DISABLE;
  RtcHandle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  RtcHandle.Init.OutPutType     = RTC_OUTPUT_TYPE_OPENDRAIN;
  RtcHandle.Instance            = RTC;
  
  if (HAL_RTC_Init(&RtcHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /*##-2- Configure RTC Tamper ###############################################*/
  stamperstructure.Tamper                       = RTC_TAMPER_2;
  stamperstructure.Trigger                      = RTC_TAMPERTRIGGER_FALLINGEDGE;
  stamperstructure.Filter                       = RTC_TAMPERFILTER_DISABLE;
  stamperstructure.SamplingFrequency            = RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV32768;
  stamperstructure.PrechargeDuration            = RTC_TAMPERPRECHARGEDURATION_1RTCCLK;
  stamperstructure.TamperPullUp                 = RTC_TAMPER_PULLUP_ENABLE;
  stamperstructure.TimeStampOnTamperDetection   = RTC_TIMESTAMPONTAMPERDETECTION_DISABLE;
  
  if (HAL_RTCEx_SetTamper_IT(&RtcHandle, &stamperstructure) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* Clear the Tamper interrupt pending bit */
  __HAL_RTC_TAMPER_CLEAR_FLAG(&RtcHandle,RTC_FLAG_TAMP2F);

  /*##-3- Write Data on the Back Up registers ################################*/
  for (index = 0; index < BACKUP_COUNT; index++)
  {
    HAL_RTCEx_BKUPWrite(&RtcHandle, aBKPDataReg[index], 0xDF59 + (index * 0x5A));
  }

  /*##-4- Check Data is stored on the Back Up registers ######################*/
  for (index = 0; index < BACKUP_COUNT; index++)
  {
    if (HAL_RTCEx_BKUPRead(&RtcHandle, aBKPDataReg[index]) != (0xDF59 + (index * 0x5A)))
    {
      Error_Handler();
    }
  }

  /* Reset flag after wrting of backup register in order to wait for new button press */
  TamperStatus = RESET;

  /*##-5- Wait for the tamper button is pressed ##############################*/
  while (TamperStatus != SET)
  {
    /* Toggle LED3 with a period of 1s */
    BSP_LED_Toggle(LED3);

    /* Delay */
    HAL_Delay(1000);
  }

  /*##-6- Deactivate the tamper                 ##############################*/
  HAL_RTCEx_DeactivateTamper(&RtcHandle, RTC_TAMPER_2);
    
  /*##-7- Check Data is cleared on the Back Up registers #####################*/
  for (index = 0; index < BACKUP_COUNT; index++)
  {
    if (HAL_RTCEx_BKUPRead(&RtcHandle, aBKPDataReg[index]) != 0x00)
    {
      Error_Handler();
    }
  }

  /* Infinite loop */
  while (1)
  {
    /* Turn LED3 on */
    BSP_LED_Toggle(LED3);

    /* Delay */
    HAL_Delay(100);
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
void Error_Handler(void)
{
  /* Turn LED4 on */
  BSP_LED_On(LED4);
  while (1)
  {
  }
}

/**
  * @brief  Tamper event callback function
  * @param  RTC handle
  * @retval None
  */
void HAL_RTCEx_Tamper2EventCallback(RTC_HandleTypeDef *hrtc)
{
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
