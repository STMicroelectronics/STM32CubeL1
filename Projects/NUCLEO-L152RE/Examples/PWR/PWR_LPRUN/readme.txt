/**
  @page PWR_LPRUN Low Power run Mode Example
  
  @verbatim
  ******************************************************************************
  * @file    PWR/PWR_LPRUN/readme.txt 
  * @author  MCD Application Team
  * @brief   This example shows how to use STM32L1xx PWR HAL API to enter the
  *          system to Low Power Run mode and exit from this mode using Key 
  *          push button.
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
 
How to enter and exit the Low-power run mode.
This example shows also how to configure the STM32L1xx system to measure 
LP Run mode current consumption.

In the associated software, the system clock is set to 32 KHz.

 @note This mode is achieved with the multispeed internal (MSI) RC oscillator set 
       to the lowspeed clock (max 131 kHz), execution from SRAM or Flash memory, 
       and internal regulator in low-power mode to minimize the regulator's 
       operating current.

In the associated software
  - the system clock is set to 32 KHz
  - the External line 15 to 10 (PC.13) is used to enter and exit the Low Power Run mode.

The system enters LP RUN mode by pressing User push-button (PC.13) and will wait 
for the same button to be pressed to exit LP RUN mode. Current consumption could 
be monitored through an amperemeter.

This behavior is repeated in an infinite loop.
 - LED2 ON: HAL configuration failed (system will go to an infinite loop)

    - Low Power Run Mode from FLASH
    ================================
          - Regulator in LP mode
          - System Running at MSI (~32KHz)
          - Flash 0 wait state  
          - MSI Range 0
          - Voltage Range 2
          - Code running from Internal FLASH
          - All peripherals OFF
          - Wakeup using Key Button PC.13

@note This example can not be used in DEBUG mode, this is due to the fact 
      that the Cortex-M3 core is no longer clocked during low power mode 
       so debugging features are disabled

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.
      
@par Directory contents 

  - PWR/PWR_LPRUN/Inc/stm32l1xx_conf.h         HAL Configuration file
  - PWR/PWR_LPRUN/Inc/stm32l1xx_it.h           Header for stm32l1xx_it.c
  - PWR/PWR_LPRUN/Inc/main.h                   Header file for main.c
  - PWR/PWR_LPRUN/Src/system_stm32l1xx.c       STM32L1xx system clock configuration file
  - PWR/PWR_LPRUN/Src/stm32l1xx_it.c           Interrupt handlers
  - PWR/PWR_LPRUN/Src/main.c                   Main program

@par Hardware and Software environment

  - This example runs on STM32L152xE devices
    
      
  - This example has been tested with STMicroelectronics STM32L152RE-Nucleo Rev C
    board and can be easily tailored to any other supported device 
    and development board.

  - STM32L152RE-Nucleo Rev C Set-up
    - Use the User push-button connected to pin PC.13 (External line 15 to 10)
    - Connect an amperemeter to JP6 to measure the IDD current

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example



 */
