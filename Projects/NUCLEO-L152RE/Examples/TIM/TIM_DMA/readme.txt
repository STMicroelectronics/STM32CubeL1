/**
  @page TIM_DMA TIM DMA example
  
  @verbatim
  ******************************************************************************
  * @file    TIM/TIM_DMA/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the TIM DMA example.
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

Use of the DMA with TIMER Update request 
to transfer data from memory to TIMER Capture Compare Register 3 (TIMx_CCR3).

  The following configuration values are used in this example:

    - TIM2CLK = SystemCoreClock
    - Prescaler = 0 
    - TIM2 counter clock = SystemCoreClock
    - SystemCoreClock is set to 32 MHz for STM32L1xx

  The objective is to configure TIM2 channel 3 to generate a PWM (Pulse Width
  Modulation) signal with a frequency equal to 17.57 KHz, and a variable duty
  cycle that is changed by the DMA after each Update DMA request.
  
  The PWM waveform can be displayed using an oscilloscope.
 

@note Care must be taken when using HAL_Delay(), this function provides accurate
      delay (in milliseconds) based on variable incremented in SysTick ISR. This
      implies that if HAL_Delay() is called from a peripheral ISR process, then 
      the SysTick interrupt must have higher priority (numerically lower)
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - TIM/TIM_DMA/Inc/stm32l1xx_hal_conf.h    HAL configuration file
  - TIM/TIM_DMA/Inc/stm32l1xx_it.h          Interrupt handlers header file
  - TIM/TIM_DMA/Inc/main.h                  Header for main.c module  
  - TIM/TIM_DMA/Src/stm32l1xx_it.c          Interrupt handlers
  - TIM/TIM_DMA/Src/main.c                  Main program
  - TIM/TIM_DMA/Src/stm32l1xx_hal_msp.c     HAL MSP file
  - TIM/TIM_DMA/Src/system_stm32l1xx.c      STM32L1xx system source file

@par Hardware and Software environment

  - This example runs on STM32L152xE devices.
    
  - This example has been tested with STMicroelectronics STM32L152RE-Nucleo Rev C 
    board and can be easily tailored to any other supported device 
    and development board.

  - STM32L152RE-Nucleo Rev C Set-up
    - Connect the TIM2 pin to an oscilloscope to monitor the different waveforms: 
    - TIM2 CH3 (PB.10)

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 */
