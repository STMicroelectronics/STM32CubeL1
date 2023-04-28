    /**
  @page FSMC_NOR FSMC NOR memory basic functionalities use example

  @verbatim
  ******************* (C) COPYRIGHT 2017 STMicroelectronics ********************
  * @file    FSMC/FSMC_NOR/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the FSMC NOR example.
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

How to configure the FSMC controller to access the NOR memory.

The NOR is M29W128GL.

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 32 MHz.

The goal of this example is to explain the different steps to configure the FSMC 
and make the NOR device ready for access, without using the BSP layer.          

In this example, the NOR device is configured and initialized explicitly 
following all initialization sequence steps. After initializing the device, user 
can perform erase/read NOR ID/read data/write data operations on it. 
A data buffer is written to the NOR memory, then read back and checked to verify 
its correctness.

If the data is read correctly from NOR, the LED1 is ON, otherwise the LED2 is ON.
In case of HAL initialization issue, LED3 will be ON.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

 - FSMC/FSMC_NOR/Inc/stm32l1xx_hal_conf.h        HAL Configuration file
 - FSMC/FSMC_NOR/Inc/main.h                      Header for main.c module 
 - FSMC/FSMC_NOR/Inc/stm32l1xx_it.h              Header for stm32l1xx_it.c
 - FSMC/FSMC_NOR/Src/main.c                      Main program
 - FSMC/FSMC_NOR/Src/stm32l1xx_hal_msp.c         HAL MSP module  
 - FSMC/FSMC_NOR/Src/stm32l1xx_it.c              Interrupt handlers
 - FSMC/FSMC_NOR/Src/system_stm32l1xx.c          STM32L1xx system clock configuration file 
    

@par Hardware and Software environment 

  - This example runs on STM32L1xx devices.
    
  - This example has been tested with STM32L152D-EVAL board and can be
    easily tailored to any other supported device and development board. 
    @note Make sure that LCD Glass is in IO Position.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 */
