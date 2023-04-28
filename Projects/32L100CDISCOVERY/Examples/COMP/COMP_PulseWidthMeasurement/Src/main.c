/**
  ******************************************************************************
  * @file    COMP/COMP_PulseWidthMeasurement/Src/main.c
  * @author  MCD Application Team
  * @brief   This example provides a short description of how to use the COMP 
  *          peripheral to measure Pulse Width.
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

/** @addtogroup COMP_PulseWidthMeasurement
  * @{
  */

/* Private typedef -----------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/**
  * @brief  Computation of digital value on range 8 bits from voltage value
  *         (unit: mV).
  *         Calculation depends on settings: digital resolution and power
  *         supply of analog voltage Vdda.
  * @param DATA: Voltage value (unit: mV)
  * @retval None
  */
#define COMPUTATION_VOLTAGE_TO_DIGITAL_8BITS(DATA)                             \
  ((DATA) * RANGE_8BITS / VDD_APPLI)

/* Private define ------------------------------------------------------------*/
#define VDD_APPLI                      ((uint32_t)3300)    /* Value of analog voltage supply Vdda (unit: mV) */
#define RANGE_8BITS                    ((uint32_t) 255)    /* Max value with a full range of 8 bits */
#define COMP_THRESHOLD_MV              ((uint32_t)1000)    /* Threshold of the comparator on the inverting input, provided by DAC. Can be customized for this example (unit: mV) */

#define TIMER_FREQUENCY_HZ             ((uint32_t)100000)  /* Timer frequency for pulse width measurement (unit: Hz). Frequency the highest (maximum TIM2CLK PCLK1 = 32MHz in this example), accuracy pitch the lowest. Maximum pulse length measurable is 65535*pitch (if timer set to 100kHz, pulse length measurable is min=10us, max=650ms) */

#define EXPECTED_PULSE_WIDTH_US           ((uint32_t)2000) /* Expected result of pulse width measurement (unit: us) */
#define EXPECTED_PULSE_WIDTH_TOLERANCE_US ((uint32_t) 500) /* Tolerance of expected result of pulse width measurement (unit: us) */

#if defined DAC_SPARE_CHANNEL_FOR_SIGNAL_TEST
#define TIMER_FOR_SIGNAL_TEST_FREQUENCY_HZ   ((uint32_t)1000)   /* Timer frequency to send each sample of the waveform (unit: Hz) */
#define WAVEFORM_SAMPLES_NUMBER              ((uint32_t)  10)
#define WAVEFORM_PERIOD_US                   ((WAVEFORM_SAMPLES_NUMBER * 1000000) / TIMER_FOR_SIGNAL_TEST_FREQUENCY_HZ)

/* Waveform sent by DAC channel. With timer frequency 1kHz and size of 10 samples: signal 100Hz with pulses of 2 ms */
const uint8_t Waveform_8bits[WAVEFORM_SAMPLES_NUMBER] = 
  {COMPUTATION_VOLTAGE_TO_DIGITAL_8BITS(   0),
   COMPUTATION_VOLTAGE_TO_DIGITAL_8BITS(   0),
   COMPUTATION_VOLTAGE_TO_DIGITAL_8BITS(   0),
   COMPUTATION_VOLTAGE_TO_DIGITAL_8BITS(   0),
   COMPUTATION_VOLTAGE_TO_DIGITAL_8BITS(   0),
   COMPUTATION_VOLTAGE_TO_DIGITAL_8BITS(3300),
   COMPUTATION_VOLTAGE_TO_DIGITAL_8BITS(3300),
   COMPUTATION_VOLTAGE_TO_DIGITAL_8BITS(   0),
   COMPUTATION_VOLTAGE_TO_DIGITAL_8BITS(   0),
   COMPUTATION_VOLTAGE_TO_DIGITAL_8BITS(   0)};
#endif /* DAC_SPARE_CHANNEL_FOR_SIGNAL_TEST */

/* Private macro -------------------------------------------------------------*/

/**
  * @brief  Computation of digital value on range 8 bits from voltage value
  *         (unit: mV).
  *         Calculation depends on settings: digital resolution and power
  *         supply of analog voltage Vdda.
  * @param DATA: Voltage value (unit: mV)
  * @retval None
  */
#define COMPUTATION_VOLTAGE_TO_DIGITAL_8BITS(DATA)                             \
  ((DATA) * RANGE_8BITS / VDD_APPLI)

/* Private variables ---------------------------------------------------------*/
COMP_HandleTypeDef   Comp2Handle;
DAC_HandleTypeDef    DacHandle;
TIM_HandleTypeDef    TimHandle;

#if defined DAC_SPARE_CHANNEL_FOR_SIGNAL_TEST
TIM_HandleTypeDef    TimForSignalTestHandle;
#endif /* DAC_SPARE_CHANNEL_FOR_SIGNAL_TEST */

/* Captured Values */
uint32_t               uwIC2Value1 = 0;
uint32_t               uwIC2Value2 = 0;
uint32_t               uwDiffCapture = 0;

/* Capture index */
uint16_t               uhCaptureIndex = 0;

__IO uint32_t uwMeasuredPulse = 0;    /* Result of the pulse width measurement (unit: us) */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void Error_Handler(void);
static void COMP_Config(void);
static void TIM_Config(void);
static void DAC_Config(void);
#if defined DAC_SPARE_CHANNEL_FOR_SIGNAL_TEST
static void DAC_generate_signal_for_test(void);
#endif /* DAC_SPARE_CHANNEL_FOR_SIGNAL_TEST */
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
  /* Initialize LEDs on board */
  BSP_LED_Init(LED4);
  BSP_LED_Init(LED3);
  
  /*## Configure peripherals #################################################*/
  /* Configure the COMPx peripheral */
  COMP_Config();
  
  /* Configure the DAC peripheral */
  DAC_Config();

  /* Configure the TIMx peripheral */
  TIM_Config();

  /*## Enable peripherals ####################################################*/
    
  /* Start COMP2 */
  if(HAL_COMP_Start(&Comp2Handle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler(); 
  }
  
  /* Set DAC Channel DHR register */ 
  if(HAL_DAC_SetValue(&DacHandle, DACx_CHANNEL_TO_COMP_INPUT_NEG, DAC_ALIGN_12B_R, COMPUTATION_VOLTAGE_TO_DIGITAL_8BITS(COMP_THRESHOLD_MV)) != HAL_OK)
  {
    /* Setting value Error */
    Error_Handler();
  }
  
  /* Enable DAC Channel */ 
  if(HAL_DAC_Start(&DacHandle, DACx_CHANNEL_TO_COMP_INPUT_NEG) != HAL_OK)
  {
    /* Start Error */
    Error_Handler();
  }


  /* Start the Input Capture in interrupt mode */
  if(HAL_TIM_IC_Start_IT(&TimHandle, TIM_CHANNEL_4) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }

#if defined DAC_SPARE_CHANNEL_FOR_SIGNAL_TEST
  /* Generate a periodic signal on a spare DAC channel */
  DAC_generate_signal_for_test();
#endif /* DAC_SPARE_CHANNEL_FOR_SIGNAL_TEST */
  
  /* Infinite loop */
  while (1)
  {
    /* Note: For debug, to watch value of pulse measurement, add a breakpoint */
    /*       into function "HAL_TIM_IC_CaptureCallback()" (see comment placed */
    /*       at the end of this function).                                    */ 
    
    /* Turn-on/off LED3 in function of pulse width measurement */
    /*  - Turn-off if pulse width is out of the expected range 2ms +- 1ms */
    /*  - Turn-on if pulse width is within expected range 2ms +- 1ms */ 
    /* Note: In case of usage of the test signal from DAC channel, since this */
    /*       signal is periodic and comparator can measure the length of the  */
    /*       complement of the pulse: comparison with the complement of the   */
    /*       pulse width (period - pulse width).                              */
    /* Note: Variable of pulse width measurement is set into timer            */
    /*       interrupt callback "HAL_TIM_IC_CaptureCallback()"                */
#if defined DAC_SPARE_CHANNEL_FOR_SIGNAL_TEST
    if (((uwMeasuredPulse > (EXPECTED_PULSE_WIDTH_US - EXPECTED_PULSE_WIDTH_TOLERANCE_US)) &&
         (uwMeasuredPulse < (EXPECTED_PULSE_WIDTH_US + EXPECTED_PULSE_WIDTH_TOLERANCE_US))   )                       ||
        ((uwMeasuredPulse > ((WAVEFORM_PERIOD_US - EXPECTED_PULSE_WIDTH_US) - EXPECTED_PULSE_WIDTH_TOLERANCE_US)) &&
         (uwMeasuredPulse < ((WAVEFORM_PERIOD_US - EXPECTED_PULSE_WIDTH_US) + EXPECTED_PULSE_WIDTH_TOLERANCE_US))   )   )
#else
    if ((uwMeasuredPulse > (EXPECTED_PULSE_WIDTH_US - EXPECTED_PULSE_WIDTH_TOLERANCE_US)) &&
        (uwMeasuredPulse < (EXPECTED_PULSE_WIDTH_US + EXPECTED_PULSE_WIDTH_TOLERANCE_US))   )
#endif /* DAC_SPARE_CHANNEL_FOR_SIGNAL_TEST */
    {
      BSP_LED_On(LED3);
    }
    else
    {
      BSP_LED_Off(LED3);
    }
  
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
  
  Comp2Handle.Init.InvertingInput        = COMP_INVERTINGINPUT_DAC2;
  Comp2Handle.Init.NonInvertingInput     = COMP_NONINVERTINGINPUT_PB5;
  Comp2Handle.Init.Output                = COMP_OUTPUT_TIM2IC4;
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
  /* Timer Input Capture Configuration Structure declaration */
  TIM_IC_InitTypeDef     sICConfig;

  /* Configure the TIM peripheral */
  /* Set TIMx instance */
  TimHandle.Instance = TIMx;
  
  /* Configure timer frequency */
  /* Set timer period to the maximum */
  /* Set timer prescaler to system core clock (unit: Hz) divided by the       */
  /* selected frequency (unit: Hz) to have timer incremented at the selected  */
  /* frequency.                                                               */
  /* Note: Timer clock source frequency is retrieved with function            */
  /*       HAL_RCC_GetPCLK1Freq().                                            */
  /*       Alternate possibility, depending on prescaler settings:            */
  /*       use variable "SystemCoreClock" holding HCLK frequency, updated by  */
  /*       function HAL_RCC_ClockConfig().                                    */
  TimHandle.Init.Period = 0xFFFF;
  TimHandle.Init.Prescaler = ((HAL_RCC_GetPCLK1Freq() / TIMER_FREQUENCY_HZ) -1);
  TimHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
  if(HAL_TIM_IC_Init(&TimHandle) != HAL_OK)
  {
    /* Error */
    Error_Handler();
  }
  

  /* Configure the Input Capture of channel 4 */
  sICConfig.ICPolarity  = TIM_ICPOLARITY_BOTHEDGE;  /* For pulse width measurement: capture from COMP rising to falling edge */
  sICConfig.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sICConfig.ICPrescaler = TIM_ICPSC_DIV1;
  sICConfig.ICFilter    = 0;   
  if(HAL_TIM_IC_ConfigChannel(&TimHandle, &sICConfig, TIM_CHANNEL_4) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler();
  }

}

/**
  * @brief  Configure the DAC peripheral
  * @param  None
  * @retval None
  */
static void DAC_Config(void)
{
  DAC_ChannelConfTypeDef sConfig;

  /* Configuration of DACx peripheral */
  DacHandle.Instance = DACx;

  if(HAL_DAC_Init(&DacHandle) != HAL_OK)
  {
    /* Error */
    Error_Handler();
  }
  
  /* Configuration of DACx selected channel */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;  
  
  if(HAL_DAC_ConfigChannel(&DacHandle, &sConfig, DACx_CHANNEL_SIGNAL_FOR_TEST) != HAL_OK)
  {
    /* Channel configuration Error */
    Error_Handler();
  }
  
}

#if defined DAC_SPARE_CHANNEL_FOR_SIGNAL_TEST
/**
  * @brief  For this example purpose, generate a periodic signal on a spare DAC
  *         channel, so user has just to connect a wire between DAC channel 
  *         (pin PA.04) and COMP2 non-inverting input (pin PB.05) to run this example.
  *         (this avoid to user the need of an external signal generator)
  * @param  None
  * @retval None
  */
static void DAC_generate_signal_for_test(void)
{
  DAC_ChannelConfTypeDef sConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  
  /*## Configure peripherals #################################################*/
    
  /* Time Base configuration */
  /* If main timer for this example purpose has been selected to TIM6, then   */
  /* select the timer of the test signal as timer 7. Otherwise, use timer 6.  */
  if (TimHandle.Instance == TIM6)
  {
    TimForSignalTestHandle.Instance = TIM7;
  }
  else
  {
    TimForSignalTestHandle.Instance = TIM6;
  }
  
  /* Configure timer frequency */
  /* Note: Setting of timer prescaler to 512 to increase the maximum range of */
  /*       the timer, to fit within timer range of 0xFFFF.                    */
  /*       Setting of reload period to SysClk/512 to maintain a base          */
  /*       frequency of 1us.                                                  */
  /*       With SysClk set to 32MHz, timer frequency (defined by label        */
  /*       TIMER_FOR_SIGNAL_TEST_FREQUENCY_HZ range) is min=1Hz, max=31.25kHz.*/
  /* Note: Timer clock source frequency is retrieved with function            */
  /*       HAL_RCC_GetPCLK1Freq().                                            */
  /*       Alternate possibility, depending on prescaler settings:            */
  /*       use variable "SystemCoreClock" holding HCLK frequency, updated by  */
  /*       function HAL_RCC_ClockConfig().                                    */
  TimForSignalTestHandle.Init.Period = ((HAL_RCC_GetPCLK1Freq() / (512 * TIMER_FOR_SIGNAL_TEST_FREQUENCY_HZ)) - 1);
  TimForSignalTestHandle.Init.Prescaler = (512-1);
  TimForSignalTestHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  TimForSignalTestHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
  
  if (HAL_TIM_Base_Init(&TimForSignalTestHandle) != HAL_OK)
  {
    /* Timer initialization Error */
    Error_Handler();
  }

  /* Timer TRGO selection */
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

  if (HAL_TIMEx_MasterConfigSynchronization(&TimForSignalTestHandle, &sMasterConfig) != HAL_OK)
  {
    /* Timer TRGO selection Error */
    Error_Handler();
  }

  
  
  /* Initialize the DAC peripheral */
  if (HAL_DAC_Init(&DacHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /* DAC channel Configuration */
  if (TimHandle.Instance == TIM6)
  {
  sConfig.DAC_Trigger = DAC_TRIGGER_T7_TRGO;
  }
  else
  {
  sConfig.DAC_Trigger = DAC_TRIGGER_T6_TRGO;
  }
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;

  if (HAL_DAC_ConfigChannel(&DacHandle, &sConfig, DACx_CHANNEL_SIGNAL_FOR_TEST) != HAL_OK)
  {
    /* Channel configuration Error */
    Error_Handler();
  }
  
  
  /*## Enable peripherals ####################################################*/
  
  /* Timer counter enable */
  if (HAL_TIM_Base_Start(&TimForSignalTestHandle) != HAL_OK)
  {
    /* Counter Enable Error */
    Error_Handler();
  }
  
  /* Enable DAC Channel1 and associated DMA */
  if (HAL_DAC_Start_DMA(&DacHandle, DACx_CHANNEL_SIGNAL_FOR_TEST, (uint32_t *)Waveform_8bits, WAVEFORM_SAMPLES_NUMBER, DAC_ALIGN_8B_R) != HAL_OK)
  {
    /* Start DMA Error */
    Error_Handler();
  }
  
}
#endif /* DAC_SPARE_CHANNEL_FOR_SIGNAL_TEST */

/**
  * @brief  Input Capture callback in non blocking mode
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
  {
    if(uhCaptureIndex == 0)
    {
      /* Get the 1st Input Capture value */
      uwIC2Value1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
      uhCaptureIndex = 1;
    }
    else if(uhCaptureIndex == 1)
    {
      /* Get the 2nd Input Capture value */
      uwIC2Value2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4); 
      
      /* Capture computation */
      if (uwIC2Value2 > uwIC2Value1)
      {
        uwDiffCapture = (uwIC2Value2 - uwIC2Value1); 
      }
      else if (uwIC2Value2 < uwIC2Value1)
      {
        uwDiffCapture = ((0xFFFF - uwIC2Value1) + uwIC2Value2); 
      }
      else
      {
        uwDiffCapture = 0;
      }
      /* Compute the pulse width in us */
      uwMeasuredPulse = (uint32_t)(((uint64_t) uwDiffCapture * (htim->Init.Prescaler +1) * 1000000) / HAL_RCC_GetPCLK1Freq());
      uhCaptureIndex = 0;
      
      /* For debug: To watch value of pulse measurement:                      */
      /*  - Set breakpoint here                                               */
      /*  - Add variable "uwMeasuredPulse" into the debugger watch window     */
      __NOP();  /* Set breakpoint here */
      
    }

  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with a potential error */
  
  /* In case of error, LED4 is toggling at a frequency of 1Hz */
  while(1)
  {
    /* Toggle LED4 */
    BSP_LED_Toggle(LED4);
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
