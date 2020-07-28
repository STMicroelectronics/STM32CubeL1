/**
  ******************************************************************************
  * @file    COMP/COMP_PWMSignalControl/Src/main.c
  * @author  MCD Application Team
  * @brief   This example provides a short description of how to use the COMP 
  *          peripheral to measure Pulse Width.
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

/** @addtogroup COMP_PWMSignalControl
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TIMER_FREQUENCY_HZ             ((uint32_t)1000)    /* Timer frequency (unit: Hz). With SysClk set to 32MHz, timer frequency range is min=1Hz, max=31.25kHz. */

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
COMP_HandleTypeDef   Comp2Handle;
TIM_HandleTypeDef    TimHandle;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void Error_Handler(void);
static void COMP_Config(void);
static void TIM_Config(void);
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
  
  /* Configure the system clock to 32 MHz */
  SystemClock_Config();
  
  /*## Configure peripherals #################################################*/
  /* Initialize LED on board */
  BSP_LED_Init(LED2);
  
  /*## Configure peripherals #################################################*/
  /* Configure the COMPx peripheral */
  COMP_Config();

  /* Configure the TIMx peripheral */
  TIM_Config();

  /*## Enable peripherals ####################################################*/
    
  /* Start COMP2 */
  if(HAL_COMP_Start(&Comp2Handle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  
  /* Start TIM2 */
  /* Start channel 2 */
  if (HAL_TIM_PWM_Start(&TimHandle, TIM_CHANNEL_2) != HAL_OK)
  {
    /* PWM Generation Error */
    Error_Handler();
  }

  
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
  * @brief  COMP configuration
  * @param  None
  * @retval None
  */
static void COMP_Config(void)
{
  
  /*##-1- Configure the COMPx peripheral ###################################*/ 
  
  /* COMP2 Init: the lower threshold is set to VREFINT/4 (1.22V /4 ~ 0.305 V) */
  /* but can be changed to other available possibilities.                     */
  Comp2Handle.Instance                   = COMP2;
  
  Comp2Handle.Init.InvertingInput        = COMP_INVERTINGINPUT_VREFINT;
  Comp2Handle.Init.NonInvertingInput     = COMP_NONINVERTINGINPUT_PB5;
  Comp2Handle.Init.Output                = COMP_OUTPUT_TIM2OCREFCLR; /* Comparator output connected to TIM2 output clear */
  Comp2Handle.Init.Mode                  = COMP_MODE_LOWSPEED;
  Comp2Handle.Init.WindowMode            = COMP_WINDOWMODE_DISABLE;
  Comp2Handle.Init.TriggerMode           = COMP_TRIGGERMODE_NONE;  /* In this example, COMP is used without interruption */
  if(HAL_COMP_Init(&Comp2Handle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  

}


/**
  * @brief Configure the TIMx peripheral
  *        channel 4 in input capture mode
  * @param  None
  * @retval None
  */
static void TIM_Config(void)
{ 
  /* Timer Output Compare Configuration Structure declaration */
  TIM_OC_InitTypeDef sConfig;
  
  /* Timer Clear Input Configuration Structure declaration */
  TIM_ClearInputConfigTypeDef sClearInputConfig;
  
  /* Configure the TIM peripheral */
  /* Set TIMx instance */
  TimHandle.Instance = TIMx;
  
  /* Configure timer frequency */
  /* Note: Setting of timer prescaler to 512 to increase the maximum range of */
  /*       the timer, to fit within timer range of 0xFFFF.                    */
  /*       Setting of reload period to SysClk/512 to maintain a base          */
  /*       frequency of 1us.                                                  */
  /*       With SysClk set to 32MHz, timer frequency (defined by label        */
  /*       TIMER_FREQUENCY_HZ range) is min=1Hz, max=31.25kHz.                */
  /* Note: Timer clock source frequency is retrieved with function            */
  /*       HAL_RCC_GetPCLK1Freq().                                            */
  /*       Alternate possibility, depending on prescaler settings:            */
  /*       use variable "SystemCoreClock" holding HCLK frequency, updated by  */
  /*       function HAL_RCC_ClockConfig().                                    */
  TimHandle.Init.Period = ((HAL_RCC_GetPCLK1Freq() / (512 * TIMER_FREQUENCY_HZ)) - 1);
  TimHandle.Init.Prescaler = (512-1);
  TimHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
  if(HAL_TIM_PWM_Init(&TimHandle) != HAL_OK)
  {
    /* Error */
    Error_Handler();
  }
  
  /*##-2- Configure the PWM channels #########################################*/
  /* Common configuration for all channels */
  sConfig.OCMode       = TIM_OCMODE_PWM1;
  sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;
  sConfig.OCFastMode   = TIM_OCFAST_DISABLE;
  sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;


  /* Set the pulse value for channel 2: duty cycle of 25% */
  sConfig.Pulse = TimHandle.Init.Period / 4;
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIM_CHANNEL_2) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler();
  }
  
  /* Clear Input Configuration for channel 2 */
  sClearInputConfig.ClearInputState = ENABLE;
  sClearInputConfig.ClearInputSource = TIM_CLEARINPUTSOURCE_OCREFCLR;
  sClearInputConfig.ClearInputPrescaler = TIM_CLEARINPUTPRESCALER_DIV1;
  sClearInputConfig.ClearInputPolarity = TIM_CLEARINPUTPOLARITY_NONINVERTED;
  sClearInputConfig.ClearInputFilter = 0x0;

  HAL_TIM_ConfigOCrefClear(&TimHandle, &sClearInputConfig, TIM_CHANNEL_2);
   
  
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with a potential error */
  
  /* In case of error, LED2 is toggling at a frequency of 1Hz */
  while(1)
  {
    /* Toggle LED2 */
    BSP_LED_Toggle(LED2);
    HAL_Delay(500);
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
