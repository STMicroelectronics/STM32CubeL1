/**
  ******************************************************************************
  * @file    COMP/COMP_AnalogWatchdog/Src/main.c
  * @author  MCD Application Team
  * @brief   This example provides a short description of how to use the COMP 
  *          peripheral in window mode to make an analog watchdog.
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

/** @addtogroup COMP_AnalogWatchdog
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define STATE_OVER_THRESHOLD    0x00000001
#define STATE_WITHIN_THRESHOLD  0x00000002
#define STATE_UNDER_THRESHOLD   0x00000003

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
COMP_HandleTypeDef   Comp1Handle;
COMP_HandleTypeDef   Comp2Handle;
__IO uint32_t State = 0;
/* Variable to indicate that MCU entered in Stop mode */
__IO uint32_t EnterInStopMode = 0;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void Error_Handler(void);
static void COMP_Config(void);
static void InputVoltageLevel_Check(void);
static void StopSequence_Config(void);

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
  
  /*******************************************************************************
  *                          Common Configuration Routines                       *
  *******************************************************************************/  
 
  /******* Initialize LEDs available on STM32L152D-EVAL board ******************/
  
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);
  BSP_LED_Init(LED4);

  /* Configure the system clock to 32 MHz */
  SystemClock_Config();
  
  /*## Configure peripherals #################################################*/
  /* Configure the COMP peripherals */
  COMP_Config();
  
  /*## Enable peripherals ####################################################*/
  /* Start COMP1 */
  if(HAL_COMP_Start_IT(&Comp1Handle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  
  /* Start COMP2 */
  if(HAL_COMP_Start_IT(&Comp2Handle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }

  /* Check input voltage level: within the thresholds, above the upper threshold
     or under the lower threshold */
  InputVoltageLevel_Check();
  
  /* Infinite loop */
  while (1)
  {
    if (State == STATE_OVER_THRESHOLD)
    {
      /* Restoration done only in case of MCU was in stop mode */
      if (EnterInStopMode == 1)
      {
        /* Restore config: clock, GPIO... */
        SystemClock_Config();
        
        /* Restore GPIO configuration */
          BSP_LED_Init(LED1);
          BSP_LED_Init(LED2);
          BSP_LED_Init(LED3);
          BSP_LED_Init(LED4);
        
        EnterInStopMode = 0;
      }

      /* Turn on LED1 and LED3 and turn off LED2 and LED4 */
      BSP_LED_On(LED1);
      BSP_LED_Off(LED2);
      BSP_LED_On(LED3);
      BSP_LED_Off(LED4);
     
      while(State == STATE_OVER_THRESHOLD)
      {
        /* add your code here */
        
      }
    }
    else if (State == STATE_WITHIN_THRESHOLD)
    {
      
      
      /* Input voltage is within the thresholds: higher and lower thresholds */
      /* Enter STOP mode with regulator in low power */
      StopSequence_Config();
    }
    else /* (State == STATE_UNDER_THRESHOLD) */
    {
      /* Restoration done only in case of MCU was in stop mode */
      if (EnterInStopMode == 1)
      {
        /* Restore config: clock, GPIO... */
        SystemClock_Config();
        
        /* Restore GPIO configuration */
        BSP_LED_Init(LED1);
        BSP_LED_Init(LED2);
        BSP_LED_Init(LED3);
        BSP_LED_Init(LED4);
        EnterInStopMode = 0;
      }
      
      /* Turn on LED2 and LED4 and turn off LED1 and LED3 */
      BSP_LED_Off(LED1);
      BSP_LED_On(LED2);
      BSP_LED_Off(LED3);
      BSP_LED_On(LED4);
      
      while(State == STATE_UNDER_THRESHOLD)
      {
        /* add your code here */
        
      }
    }
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
  /* COMP1 Init: the higher threshold is fixed by hardware to VREFINT         */
  /* (~ 1.22V).                                                               */
  Comp1Handle.Instance                   = COMP1;

  Comp1Handle.Init.NonInvertingInput     = COMP_NONINVERTINGINPUT_NONE;   /* In window mode, COMP1 non-inverting input is connected internally to COMP2 non-inverting input */
  Comp1Handle.Init.NonInvertingInputPull = COMP_NONINVERTINGINPUT_NOPULL;
  Comp1Handle.Init.TriggerMode           = COMP_TRIGGERMODE_IT_RISING_FALLING;
  if(HAL_COMP_Init(&Comp1Handle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  
  
  /* COMP2 Init: the lower threshold is set to VREFINT/4 (1.22V /4 ~ 0.305 V) */
  /* but can be changed to other available possibilities.                     */
  Comp2Handle.Instance                   = COMP2;
  
  Comp2Handle.Init.InvertingInput        = COMP_INVERTINGINPUT_1_4VREFINT;
  Comp2Handle.Init.NonInvertingInput     = COMP_NONINVERTINGINPUT_PB5;
  Comp2Handle.Init.Output                = COMP_OUTPUT_NONE;
  Comp2Handle.Init.Mode                  = COMP_MODE_LOWSPEED;
  Comp2Handle.Init.WindowMode            = COMP_WINDOWMODE_ENABLE;
  Comp2Handle.Init.TriggerMode           = COMP_TRIGGERMODE_IT_RISING_FALLING;
  if(HAL_COMP_Init(&Comp2Handle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  

}

/**
  * @brief  Prepare the system to enter STOP mode.
  * @param  None
  * @retval None
  */
static void StopSequence_Config(void)
{
  GPIO_InitTypeDef      GPIO_InitStruct;
  
  /* PWR Peripheral clock enable */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* Enable GPIOs clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /* Configure all GPIO port pins in Analog mode */
  GPIO_InitStruct.Pin = GPIO_PIN_All;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /* Request to enter STOP mode with regulator in low power */
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
  EnterInStopMode = 1;
}

/**
  * @brief  check input voltage level: within the thresholds, above the upper 
  *         threshold or under the lower threshold
  * @param  None
  * @retval None
  */
static void InputVoltageLevel_Check(void)
{
  /*  Check if COMP1 and COMP2 output level is high */
  if (((HAL_COMP_GetOutputLevel(&Comp1Handle)) == COMP_OUTPUTLEVEL_HIGH) 
   && ((HAL_COMP_GetOutputLevel(&Comp2Handle)) == COMP_OUTPUTLEVEL_HIGH))
  {
    /* A rising edge is detected so the input voltage is higher than VREFINT */
    State = STATE_OVER_THRESHOLD;
  }
  else if (((HAL_COMP_GetOutputLevel(&Comp1Handle)) == COMP_OUTPUTLEVEL_LOW)
       && ((HAL_COMP_GetOutputLevel(&Comp2Handle)) == COMP_OUTPUTLEVEL_HIGH))
  {
    /* A falling edge is detected so the input voltage is lower than VREFINT */
    State = STATE_WITHIN_THRESHOLD;
  }
  else if (((HAL_COMP_GetOutputLevel(&Comp1Handle)) == COMP_OUTPUTLEVEL_LOW)
       && ((HAL_COMP_GetOutputLevel(&Comp2Handle)) == COMP_OUTPUTLEVEL_LOW))
  {
    State = STATE_UNDER_THRESHOLD;
  }
}

/**
  * @brief  Comparator interrupt callback.
  * @param  hcomp: COMP handle
  * @retval None
  */
void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp)
{
  /* Check input voltage level: within the thresholds, */
  /* above the upper threshold or under the lower threshold */
  InputVoltageLevel_Check();
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
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */
