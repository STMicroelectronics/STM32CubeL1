/**
  @page ADC_LowPower ADC conversion example using related peripherals (GPIO, Timer),
   user control by push button and LED.

  @verbatim
  ******************************************************************************
  * @file    ADC/ADC_LowPower/readme.txt 
  * @author  MCD Application Team
  * @brief   brief   Description of the ADC Low Power modes example.
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
  @endverbatim

@par Example Description 

How to use the ADC peripheral to perform conversions with ADC low-power modes: 
auto-wait and auto-power off.

Other peripherals related to ADC are used:
Mandatory:
 - GPIO peripheral is used in analog mode to drive signal from device pin to
   ADC input.
Optionally:
 - Timer peripheral is used to trig ADC conversions.

ADC settings:
  Trig of conversion start done by external event (timer at 1kHz).
  Continuous mode disabled to have only 1 conversion at each conversion trig.
ADC conversion results:
 - ADC conversions results are transferred manually (by software), into variable
   array "uhADCxConvertedValue".
 - This value will be displayed directly on LCD with a voltage conversion.
 @note Make sure that LCD Glass is in IO position
Board settings:
 - ADC is configured to convert ADC_CHANNEL_31 (pin PF.10).
 - The voltage input on ADC channel is provided from potentiometer RV3 (which is connected to
ADC_CHANNEL_31 (pin PF.10) on STM32L152D-EVAL).
   Turning this potentiometer will make the voltage vary into full range: from 0 to Vdda (3.3V).
   ==> Therefore, there is no external connection needed to run this example.

How to use this example:
ADC overrun feature is used to watch the ADC low power modes effectiveness:
 - If definition label "#define ADC_LOWPOWER" is commented, then ADC does not use
   low power features.
   Trigger events are occurring continuously (from timer trigger out), ADC performs
   a conversion at each trigger event.
   ADC conversion results are not fetch after each conversion, therefore some results
   are overwritten and ADC overrun triggers.
   => Press Key push-button (fetch an ADC conversion result and refresh LED state),
      then LED1 should turn on.
   
 - If definition label "#define ADC_LOWPOWER" is uncommented, then ADC does use
   low power features.
   Trigger events are occurring continuously (from timer trigger out), but ADC does not
   perform a conversion at each trigger event: after the first ADC conversion, ADC does
   not start a new conversion until the previous conversion result has been fetched
   (done by function "HAL_ADC_GetValue(&AdcHandle)" into the example: this is ADC feature
   "LowPowerAutoWait".
   Moreover, ADC is powered off during this idle phase: this is ADC feature
   "LowPowerAutoPowerOff".
   When user press Key push-button, ADC result is fetched and ADC is freed from idle phase:
   a new conversion starts at the next trigger event.
   ADC conversion results are never overwritten, ADC overrun does not trigger
   => Press Key push-button (fetch an ADC conversion result and refresh LED state),
      then LED1 should remain turned off.


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - ADC/ADC_LowPower/Inc/stm32l1xx_hal_conf.h    HAL configuration file
  - ADC/ADC_LowPower/Inc/stm32l1xx_it.h          HAL interrupt handlers header file
  - ADC/ADC_LowPower/Inc/main.h                  Header for main.c module  
  - ADC/ADC_LowPower/Src/stm32l1xx_it.c          HAL interrupt handlers
  - ADC/ADC_LowPower/Src/main.c                  Main program
  - ADC/ADC_LowPower/Src/stm32l1xx_hal_msp.c     HAL MSP file
  - ADC/ADC_LowPower/Src/system_stm32l1xx.c      STM32L1xx system source file


@par Hardware and Software environment 

  - This example runs on STM32L1xx devices.

  - This example has been tested with STM32L152D-EVAL board and can be
    easily tailored to any other supported device and development board.
    
  - JP7  jumper should be in position 1-2.
  - JP12 jumper should be closed.
  - JP13 jumper should be fitted in ADC position.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 */
