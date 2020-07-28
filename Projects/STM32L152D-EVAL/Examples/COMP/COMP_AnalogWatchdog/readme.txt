/**
  @page COMP_AnalogWatchdog COMP Analog Watchdog Example
  
  @verbatim
  ******************************************************************************
  * @file    COMP/COMP_AnalogWatchdog/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the COMP Analog Watchdog Example.
  ******************************************************************************
  *
  * Copyright (c) 2017 STMicroelectronics. All rights reserved.
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  @endverbatim

@par Example Description 

How to use a pair of comparator peripherals to compare a voltage level applied on
a GPIO pin to two thresholds: the internal voltage reference (VREFINT) and a fraction
of the internal voltage reference (VREFINT/4), in interrupt mode.

  - The upper threshold is set to VREFINT = 1.22V
  - The lower threshold is set to VREFINT / 4 = 1.22V / 4 = 0.305V
  - The input voltage is configured to be connected to pin PB.05
  
LEDs on STM32L152D-EVAL can be used to monitor the voltage level compared to comparators thresholds:

- LED3 and LED1 are turned On, MCU wakes-up from STOP mode, if the input voltage is above the higher threshold.
- LED2 and LED4 are turned On, MCU wakes-up from STOP mode, if the input voltage is under the lower threshold.
- If the input voltage is within the thresholds, the MCU is set in in STOP mode (LED2 and LED4 are turned Off).


@note Care must be taken when using HAL_Delay(), this function provides 
      accurate delay (in milliseconds) based on variable incremented in SysTick ISR. 
      This implies that if HAL_Delay() is called from a peripheral ISR process, then 
      the SysTick interrupt must have higher priority (numerically lower) than the 
      peripheral interrupt. Otherwise the caller ISR process will be blocked. 
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set 
      to 1 millisecond to have correct HAL operation.

@par Directory contents 

  - COMP/COMP_AnalogWatchdog/Inc/stm32l1xx_hal_conf.h    HAL configuration file
  - COMP/COMP_AnalogWatchdog/Inc/stm32l1xx_it.h          COMP interrupt handlers header file
  - COMP/COMP_AnalogWatchdog/Inc/main.h                  Header for main.c module
  - COMP/COMP_AnalogWatchdog/Src/stm32l1xx_it.c          COMP interrupt handlers
  - COMP/COMP_AnalogWatchdog/Src/main.c                  Main program
  - COMP/COMP_AnalogWatchdog/Src/stm32l1xx_hal_msp.c     HAL MSP file 
  - COMP/COMP_AnalogWatchdog/Src/system_stm32l1xx.c      STM32L1xx system source file


@par Hardware and Software environment 

  - This example runs on STM32L1xx devices.

  - This example has been tested with STM32L152D-EVAL board and can be
    easily tailored to any other supported device and development board.

  - STM32L152D-EVAL Set-up
    - Use LED1, LED2, LED3 and LED4 connected respectively to PD.03, PD.07 ,PG.14
      and PG.15 pins
      @note This example run in stand alone mode.
    - Use a wire to connect Potentiometer RV3 (pin PF.10)
      to COMP2 non inverting input (pin PB.05).
      Note: On STM32L152D-EVAL: Pin PB.05 is accessible on JP13, connector marked "COM_IN+".
      Alternatively use an external power supply and adjust supply voltage (above, within and below thresholds).
@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */