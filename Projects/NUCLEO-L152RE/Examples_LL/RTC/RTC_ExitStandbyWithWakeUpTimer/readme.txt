/**
  @page RTC_ExitStandbyWithWakeUpTimer RTC example
  
  @verbatim
  ******************************************************************************
  * @file    Examples_LL/RTC/RTC_ExitStandbyWithWakeUpTimer/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the RTC example.
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

Configuration of the RTC to wake up from Standby mode 
using the RTC Wakeup timer. The peripheral initialization uses LL unitary service 
functions for optimization purposes (performance and size).

In this example, after start-up, SYSCLK is configured to the max frequency using 
the PLL with HSI as clock source.

Example execution:
   - 1st execution of the system, LED2 is quickly blinking
   - Press the user button:
     * RTC wakeup timer is configured to 5 seconds
     * System enters in standby mode (LED2 is switch off)
   - After 5 seconds, system resumes from standby mode, then LED2 is slowly blinking.
 
   @note LSI oscillator clock is used as RTC clock source by default.
      The user can use also LSE as RTC clock source. The user uncomment the adequate 
      line on the main.h file.
      @code
        #define RTC_CLOCK_SOURCE_LSI  
        /* #define RTC_CLOCK_SOURCE_LSE */
      @endcode
      LSI oscillator clock is delivered by a 37 kHz RC.
      LSE (when available on board) is delivered by a 32.768 kHz crystal.

- LED2 is toggling every 1 second: This indicates that the system generates an error.

@par Directory contents 

  - RTC/RTC_ExitStandbyWithWakeUpTimer/Inc/stm32l1xx_it.h          Interrupt handlers header file
  - RTC/RTC_ExitStandbyWithWakeUpTimer/Inc/main.h                  Header for main.c module
  - RTC/RTC_ExitStandbyWithWakeUpTimer/Inc/stm32_assert.h          Template file to include assert_failed function
  - RTC/RTC_ExitStandbyWithWakeUpTimer/Src/stm32l1xx_it.c          Interrupt handlers
  - RTC/RTC_ExitStandbyWithWakeUpTimer/Src/main.c                  Main program
  - RTC/RTC_ExitStandbyWithWakeUpTimer/Src/system_stm32l1xx.c      STM32L1xx system source file


@par Hardware and Software environment

  - This example runs on STM32L152xE devices.
    
  - This example has been tested with STM32L152RE-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example


 */
