/**
  @page DAC_SignalsGeneration DAC Signals generation example
  
  @verbatim
  ******************************************************************************
  * @file    DAC/DAC_SignalsGeneration/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the DAC Signals generation example.
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

How to use the DAC peripheral to generate several signals using the DMA
controller.
For each press on Key push-button, a signal has been selected and can be monitored on  
the DAC channel one:
    - Triangle waveform (Channel 1).
    - Escalator waveform (Channel 1) using DMA transfer.

STM32L152D-EVAL board's LEDs can be used to monitor the process status:
  - LED3 is ON and example is stopped (using infinite loop)
  when there is an error during process.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.
    
@par Directory contents 

  - DAC/DAC_SignalsGeneration/Inc/stm32l1xx_hal_conf.h    HAL configuration file
  - DAC/DAC_SignalsGeneration/Inc/stm32l1xx_it.h          DAC interrupt handlers header file
  - DAC/DAC_SignalsGeneration/Inc/main.h                  Header for main.c module  
  - DAC/DAC_SignalsGeneration/Src/stm32l1xx_it.c          DAC interrupt handlers
  - DAC/DAC_SignalsGeneration/Src/main.c                  Main program
  - DAC/DAC_SignalsGeneration/Src/stm32l1xx_hal_msp.c     HAL MSP file
  - DAC/DAC_SignalsGeneration/Src/system_stm32l1xx.c      STM32L1xx system source file

@par Hardware and Software environment  
  - This example runs on STM32L1xx devices.
    
  - This example has been tested with STM32L152D-EVAL board and can be
    easily tailored to any other supported device and development board.

  - STM32L152D-EVAL Set-up 	
  - Use Key push-button connected to PA.00.
  - Connect PA4 (DAC Channel1) pin to an oscilloscope.
  
@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example
  
 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */

