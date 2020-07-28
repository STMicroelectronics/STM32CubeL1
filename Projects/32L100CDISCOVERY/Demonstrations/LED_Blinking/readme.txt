/**
  @page LED_Blinking Demonstration of STM32L100C-Discovery board
  
  @verbatim
  ******************************************************************************
  * @file    Demonstrations/LED_Blinking/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the STM32L100C-Discovery Demonstration firmware.
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

This demonstration will use USER button, LED3 & LED4 available on the board.

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 32 MHz.

Each time user will press USER push-button, LEDs programming will be done.
1) LED3 blinking every 200ms
2) press button, LED4 ON during 1s and then off
3) LED3 blinking every 100ms
4) press button, LED4 ON during 1s and then off
5) LED3 OFF
6) press button, LED4 ON during 1s and then off => go to step 1)

@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - Demonstrations/LED_Blinking/Inc/stm32l1xx_hal_conf.h    HAL configuration file
  - Demonstrations/LED_Blinking/Inc/stm32l1xx_it.h          Interrupt handlers header file
  - Demonstrations/LED_Blinking/Inc/main.h                  Header for main.c module  
  - Demonstrations/LED_Blinking/Src/stm32l1xx_it.c          Interrupt handlers
  - Demonstrations/LED_Blinking/Src/main.c                  Main program
  - Demonstrations/LED_Blinking/Src/system_stm32l1xx.c      STM32L1xx system source file
  - Demonstrations/LED_Blinking/Binary/readme.txt           STM32L100C-Discovery binary readme.txt
firmware


@par Hardware and Software environment

  - This example runs on STM32L100xC devices.
    
  - Connect the STM32L100C-Discovery board to a PC with a 'USB type A to Mini-B'
    cable through USB connector CN1 to power the board.
    
  - Make sure that the embedded ST-LINK/V2 is configured for in-system programming
    (both CN2 jumpers ON)


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

Note: You can load the binary file: "STM32L100C_Discovery_Demo_V1.0.0.hex" available under "Binary"
using your preferred in-system programming (ex. STM32 ST-LINK Utility, available for download from www.st.com).
 

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
