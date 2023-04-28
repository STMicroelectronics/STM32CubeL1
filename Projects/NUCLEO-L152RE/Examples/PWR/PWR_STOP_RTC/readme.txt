/**
  @page PWR_STOP_RTC Power Stop Mode Example 
  
  @verbatim
  ******************************************************************************
  * @file    PWR/PWR_STOP_RTC/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the Power Stop Mode using RTC example.
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

How to enter the Stop mode and wake up from this mode by using the RTC wakeup 
timer event connected to an interrupt.

This example shows also how to configure the STM32L1xx system to measure 
STOP mode with RTC current consumption.

In the associated software, the system clock is set to 32 MHz, the SysTick is 
programmed to generate an interrupt each 1 ms.
The Low Speed Internal (LSI) clock is used as RTC clock source by default.

In the associated software
  - the system clock is set to 32 MHz.
  - the EXTI_Line20 connected internally to the RTC Wakeup event is configured
    to generate an interrupt on rising edge each 4s.
  - the SysTick is programmed to generate an interrupt each 1 ms. 

The system enters STOP mode after 5s and will wait for the RTC Wakeup event to be
generated each 4s. Current consumption could be monitored through an amperemeter.
After the system woken up from STOP, the clock system should be reconfigured to HSI 
because the default clock after wake up is the MSI.

The above scenario is repeated in an infinite loop.
 - LED2 ON: HAL configuration failed (system will go to an infinite loop)
 
    - STOP Mode with RTC clocked by LSI
    ===================================  
            - RTC Clocked by LSI
            - Regulator in LP mode
            - VREFINT OFF with fast wakeup enabled
            - MSI as SysClk after Wake Up
            - No IWDG
            - Automatic Wakeup using RTC on LSI (after ~4s)


@note This example can not be used in DEBUG mode, this is due to the fact 
      that the Cortex-M3 core is no longer clocked during low power mode 
       so debugging features are disabled

@note Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to select 
      the RTC clock source; in this case the Backup domain will be reset in  
      order to modify the RTC Clock source, as consequence RTC registers (including 
      the backup registers) and RCC_CSR register are set to their reset values.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.
      
@par Directory contents 

  - PWR/PWR_STOP_RTC/Inc/stm32l1xx_conf.h         HAL Configuration file
  - PWR/PWR_STOP_RTC/Inc/stm32l1xx_it.h           Header for stm32l1xx_it.c
  - PWR/PWR_STOP_RTC/Inc/main.h                   Header file for main.c
  - PWR/PWR_STOP_RTC/Src/system_stm32l1xx.c       STM32L1xx system clock configuration file
  - PWR/PWR_STOP_RTC/Src/stm32l1xx_it.c           Interrupt handlers
  - PWR/PWR_STOP_RTC/Src/main.c                   Main program
  - PWR/PWR_STOP_RTC/Src/stm32l1xx_hal_msp.c  HAL MSP module

@par Hardware and Software environment

  - This example runs on STM32L152xE devices
    
      
  - This example has been tested with STMicroelectronics STM32L152RE-Nucleo Rev C
    board and can be easily tailored to any other supported device 
    and development board.

  - STM32L152RE-Nucleo Rev C Set-up
    - Connect an amperemeter to JP6 to measure the IDD current

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example



 */
