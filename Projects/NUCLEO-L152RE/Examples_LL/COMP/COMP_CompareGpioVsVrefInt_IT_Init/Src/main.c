/**
  ******************************************************************************
  * @file    Examples_LL/COMP/COMP_CompareGpioVsVrefInt_IT_Init/Src/main.c
  * @author  MCD Application Team
  * @brief   This example shows how to use a comparator peripheral
  *          to compare a voltage level applied on a GPIO pin
  *          versus the internal voltage reference (VrefInt),
  *          in interrupt mode.
  *          This example is based on the STM32L1xx COMP LL API;
  *          Peripheral initialization done using LL initialization function.
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

/** @addtogroup STM32L1xx_LL_Examples
  * @{
  */

/** @addtogroup COMP_CompareGpioVsVrefInt_IT_Init
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void     SystemClock_Config(void);
void     Configure_COMP(void);
void     Activate_COMP(void);
void     LED_Init(void);
void     LED_On(void);
void     LED_Off(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* Configure the system clock to 32 MHz */
  SystemClock_Config();
  
  /* Initialize LED2 */
  LED_Init();
  
  /* Configure comparator */
  Configure_COMP();
  
  /* Activate comparator */
  Activate_COMP();
  
  /* Infinite loop */
  while (1)
  {
    /* Note: LED state depending on COMP status is set into COMP IRQ handler, */
    /*        refer to function "ComparatorTrigger_Callback()".               */
    
  }
}

/**
  * @brief  Configure comparator (COMP instance: COMP1), GPIO and EXTI line
  *         used by comparator.
  * @note   This function configures the comparator but does not enable it,
  *         in order to optimize power consumption (comparator enabled only
  *         when needed).
  * @param  None
  * @retval None
  */
void Configure_COMP(void)
{
  LL_COMP_InitTypeDef COMP_InitStruct;
  /*## Configuration of GPIO used by comparator ##############################*/
  
  /* Configure GPIO connected to the selected comparator input plus */
  /* Enable GPIO clock */
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  
  /* Configure GPIO in analog mode to be used as COMP input */
  LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_1, LL_GPIO_MODE_ANALOG);
  
  /*## Configuration of NVIC #################################################*/
  /* Configure NVIC to enable COMP1 interruptions */
  NVIC_SetPriority(COMP_IRQn, 0);
  NVIC_EnableIRQ(COMP_IRQn);
  
  /*## Configuration of comparator ###########################################*/
  
  /* Enable COMP clock */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_COMP);
  
  /* Enable SYSCFG clock to control the routing interface (RI) */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  
  /*## Configuration of comparator common instance ###########################*/
  
  /* Set comparator common instance window mode */
  /* Note: Window mode is common to 2 COMP instances, and therefore must      */
  /*       with a COMP common instance (COMP12_COMMON, ...)                   */
  //LL_COMP_SetCommonWindowMode(__LL_COMP_COMMON_INSTANCE(COMP1), LL_COMP_WINDOWMODE_DISABLE);
  
  /*## Configuration of comparator instance ##################################*/
  
  /* Update fields of initialization structure */
  COMP_InitStruct.PowerMode            = LL_COMP_POWERMODE_ULTRALOWPOWER;
  COMP_InitStruct.InputPlus            = LL_COMP_INPUT_PLUS_IO6;
  COMP_InitStruct.InputMinus           = LL_COMP_INPUT_MINUS_VREFINT;
  COMP_InitStruct.OutputSelection      = LL_COMP_OUTPUT_NONE;
  
  /* Initialize COMP instance according to parameters defined in              */
  /* initialization structure.                                                */
  LL_COMP_Init(COMP1, &COMP_InitStruct);
  
  /*## Configuration of EXTI line used by comparator #########################*/
  /* Set EXTI line trigger edge */
  LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_21);
  LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_21);
  
  /* Set EXTI line interruption */
  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_21);
  
}

/**
  * @brief  Perform comparator activation procedure
  *         (COMP instance: COMP1).
  * @note   Operations:
  *         - Enable comparator instance
  *         - Wait for comparator startup time
  *           (required to reach propagation delay specification)
  * @param  None
  * @retval None
  */
void Activate_COMP(void)
{
  __IO uint32_t wait_loop_index = 0;
  
  /* Enable comparator */
  LL_COMP_Enable(COMP1);
  
  /* Delay for comparator startup time.                                       */
  /* Compute number of CPU cycles to wait for, from delay in us.              */
  /* Note: Variable divided by 2 to compensate partially                      */
  /*       CPU processing cycles (depends on compilation optimization).       */
  /* Note: If system core clock frequency is below 200kHz, wait time          */
  /*       is only a few CPU processing cycles.                               */
  wait_loop_index = ((LL_COMP_DELAY_STARTUP_US * (SystemCoreClock / (100000 * 2))) / 10);
  while(wait_loop_index != 0)
  {
    wait_loop_index--;
  }
  
}

/**
  * @brief  Initialize LED2.
  * @param  None
  * @retval None
  */
void LED_Init(void)
{
  /* Enable the LED2 Clock */
  LED2_GPIO_CLK_ENABLE();

  /* Configure IO in output push-pull mode to drive external LED2 */
  LL_GPIO_SetPinMode(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_MODE_OUTPUT);
  /* Reset value is LL_GPIO_OUTPUT_PUSHPULL */
  //LL_GPIO_SetPinOutputType(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  /* Reset value is LL_GPIO_SPEED_FREQ_LOW */
  //LL_GPIO_SetPinSpeed(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_SPEED_FREQ_LOW);
  /* Reset value is LL_GPIO_PULL_NO */
  //LL_GPIO_SetPinPull(LED2_GPIO_PORT, LED2_PIN, LL_GPIO_PULL_NO);
}

/**
  * @brief  Turn-on LED2.
  * @param  None
  * @retval None
  */
void LED_On(void)
{
  /* Turn LED2 on */
  LL_GPIO_SetOutputPin(LED2_GPIO_PORT, LED2_PIN);
}

/**
  * @brief  Turn-off LED2.
  * @param  None
  * @retval None
  */
void LED_Off(void)
{
  /* Turn LED2 off */
  LL_GPIO_ResetOutputPin(LED2_GPIO_PORT, LED2_PIN);
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
  /* Enable ACC64 access and set FLASH latency */ 
  LL_FLASH_Enable64bitAccess();; 
  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);

  /* Set Voltage scale1 as MCU will run at 32MHz */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
  LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
  
  /* Poll VOSF bit of in PWR_CSR. Wait until it is reset to 0 */
  while (LL_PWR_IsActiveFlag_VOSF() != 0)
  {
  };
  
  /* Enable HSI if not already activated*/
  if (LL_RCC_HSI_IsReady() == 0)
  {
    /* HSI configuration and activation */
    LL_RCC_HSI_Enable();
    while(LL_RCC_HSI_IsReady() != 1)
    {
    };
  }
  
  /* Main PLL configuration and activation */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLL_MUL_6, LL_RCC_PLL_DIV_3);

  LL_RCC_PLL_Enable();
  while(LL_RCC_PLL_IsReady() != 1)
  {
  };
  
  /* Sysclk activation on the main PLL */
  LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
  {
  };
  
  /* Set APB1 & APB2 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

  /* Set systick to 1ms in using frequency set to 32MHz                             */
  /* This frequency can be calculated through LL RCC macro                          */
  /* ex: __LL_RCC_CALC_PLLCLK_FREQ (HSI_VALUE, LL_RCC_PLL_MUL_6, LL_RCC_PLL_DIV_3); */
  LL_Init1msTick(32000000);
  
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(32000000);
}

/******************************************************************************/
/*   USER IRQ HANDLER TREATMENT                                               */
/******************************************************************************/

/**
  * @brief  Comparator interruption callback
  *         This function is executed when the comparator threshold
  *         is triggered.
  * @retval None
  */
void ComparatorTrigger_Callback()
{
  /* Set LED state in function of comparator output level */
  if (LL_COMP_ReadOutputLevel(COMP1) == LL_COMP_OUTPUT_LEVEL_HIGH)
  {
    LED_On();
  }
  else
  {
    LED_Off();
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
     ex: printf("Wrong parameters value: file %s on line %d", file, line) */

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
