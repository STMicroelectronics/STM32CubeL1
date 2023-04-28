/**
  @page TIM_DMA TIM example
  
  @verbatim
  ******************************************************************************
  * @file    Examples_LL/TIM/TIM_DMA/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the TIM_DMA example.
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

Use of the DMA with a timer update request 
to transfer data from memory to Timer Capture Compare Register 3 (TIMx_CCR3). This 
example is based on the STM32L1xx TIM LL API. The peripheral initialization 
uses LL unitary service functions for optimization purposes (performance and size).

The following configuration values are used in this example:
  - TIM3CLK = SystemClock
  - Prescaler = 0 
  - TIM3 counter clock = SystemClock
  - SystemCoreClock is set to 32 MHz for STM32L1xx Devices.

The objective is to configure TIM3 channel 3 to generate PWM edge aligned 
signal with a frequency equal to 17.57 KHz, and a variable duty cycle that
is changed by the DMA after each Update DMA request. The TIM3 Channel 3 Duty Cycle 
changes to the next new value defined by the aCCValue_Buffer.

The PWM waveform can be displayed using an oscilloscope.

Whenever a DMA transfer fails LED2 flashes with a frequency of 1 Hz.
 
@note PWM signal frequency value mentioned above is theoretical (obtained when
      the system clock frequency is exactly 80 MHz). Since the generated system
      clock frequency may vary from one board to another observed PWM signal
      frequency might be slightly different.

@par Directory contents 

  - TIM/TIM_DMA/Inc/stm32l1xx_it.h          Interrupt handlers header file
  - TIM/TIM_DMA/Inc/main.h                  Header for main.c module
  - TIM/TIM_DMA/Inc/stm32_assert.h          Template file to include assert_failed function
  - TIM/TIM_DMA/Src/stm32l1xx_it.c          Interrupt handlers
  - TIM/TIM_DMA/Src/main.c                  Main program
  - TIM/TIM_DMA/Src/system_stm32l1xx.c      STM32L1xx system source file


@par Hardware and Software environment

  - This example runs on STM32L152xE devices.
    
  - This example has been tested with STM32L152RE-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.

  - STM32L152RE-Nucleo Rev C Set-up
    - Connect the TIM3 pins to an oscilloscope to monitor the different waveforms:
      - TIM3_CH3  PB.00: connected to pin 34 of CN7 connector 

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example


 */
