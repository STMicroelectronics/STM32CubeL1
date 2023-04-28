    /**
  @page FSMC_SRAM_DataMemory FSMC SRAM data memory example

  @verbatim
  ******************* (C) COPYRIGHT 2017 STMicroelectronics ********************
  * @file    FSMC/FSMC_SRAM_DataMemory/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the FSMC SRAM_DataMemory example.
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

How to configure the FSMC controller to access the SRAM memory including the
heap and stack.

The SRAM is IS61WV51216BLL.

The example scenario does not reflect a real application case, its purpose is to
provide only the procedure to follow to use the external SRAM as data memory.

This example does not use the default library startup file. It uses a modified 
startup file provided with the example. The user has to add the new startup 
file in the project source list. While startup, the SRAM is configured 
and initialized to be ready to contain data.

The user has to configure his preferred toolchain using the provided linker file.
The RAM zone is modified in order to use the external SRAM as a RAM.
 
At this stage, all the used data can be located in the external SRAM.

Then the SystemClock_Config() function is used to configure the system clock (SYSCLK) 
to run at 32 MHz. 

The user can use the debugger's watch to evaluate "uwTabAddr" and "MSPValue" variables
values which should be equal to "0x680xxxxx". 
 
@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

 - FSMC/FSMC_SRAM_DataMemory/Inc/stm32l1xx_hal_conf.h        HAL Configuration file
 - FSMC/FSMC_SRAM_DataMemory/Inc/main.h                      Header for main.c module 
 - FSMC/FSMC_SRAM_DataMemory/Inc/stm32l1xx_it.h              Header for stm32l1xx_it.c
 - FSMC/FSMC_SRAM_DataMemory/Src/main.c                      Main program
 - FSMC/FSMC_SRAM_DataMemory/Src/stm32l1xx_it.c              Interrupt handlers
 - FSMC/FSMC_SRAM_DataMemory/Src/system_stm32l1xx.c          STM32L1xx system clock configuration file 
    

@par Hardware and Software environment 

  - This example runs on STM32L1xx devices.
    
  - This example has been tested with STM32L152D-EVAL board and can be
    easily tailored to any other supported device and development board. 


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 */
