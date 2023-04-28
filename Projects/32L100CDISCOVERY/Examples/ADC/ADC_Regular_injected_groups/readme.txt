/**
  @page ADC_Regular_injected_groups ADC conversion example showing the usage of
   the 2 ADC groups: regular group for ADC conversions on main stream and 
   injected group for ADC conversions limited on specific events (conversions
   injected within main conversions stream),
   using related peripherals (GPIO, DMA, Timer), voltage input from DAC, user 
   control by push button and LED

  @verbatim
  ******************************************************************************
  * @file    ADC/ADC_Regular_injected_groups/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the ADC conversion example
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

How to use the ADC peripheral to perform conversions using the two ADC groups: 
regular group for ADC conversions on the main stream, and injected group for 
ADC conversions limited to specific events (conversions injected into the 
main conversion stream).

Other peripherals related to ADC are used:
Mandatory:
 - GPIO peripheral is used in analog mode to drive signal from device pin to
   ADC input.
Optionally:
 - Timer peripheral is used to trig ADC conversions.
 - DMA peripheral is used to transfer ADC conversions data.

ADC settings:
 - Regular group:
   Trig of conversions is done by external event (timer at 1kHz).
   Continuous mode disabled to have only 1 conversion at each conversion trig.
 - Injected group: 
   Trig of conversions is done manually, by software start, at each press on
   user button.

ADC conversion results:
 - ADC conversions results are transferred automatically by DMA, into variable
   array "aADCxConvertedValues".
 - When DMA transfer half-buffer and buffer length are reached, callbacks 
   HAL_ADC_ConvCpltCallback() and HAL_ADC_ConvCpltCallback() are called.

Board settings:
 - ADC is configured to convert ADC_CHANNEL_4 (pin PA.04).
 - Channel configured on regular group:
   The voltage input on ADC channel is provided from DAC channel.
   ADC and DAC channel have been chosen to have the same pad shared at device level: pin PA.04.
   ==> Therefore, there is no external connection needed to run this example.
 - Voltage is increasing at each click on push button, from 0 to maximum range in 4 steps.
   Clicks on push button follow circular cycles: At clicks counter maximum value reached, counter is set back to 0.
 - Channel configured on injected group:
   The voltage input is provided from internal reference voltage VrefInt.

STM32L100C-Discovery board's LEDs are be used to monitor the program execution status:
 - Normal operation: LED3 is turned-on/off in function of ADC conversion
   result.
    - Turned-off if voltage measured by injected group is below voltage measured by regular group (average of results table)
    - Turned-on if voltage measured by injected group is above voltage measured by regular group (average of results table)
 - Error: In case of error, LED4 is toggling at a frequency of 1Hz.


@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - ADC/ADC_Regular_injected_groups/Inc/stm32l1xx_hal_conf.h    HAL configuration file
  - ADC/ADC_Regular_injected_groups/Inc/stm32l1xx_it.h          HAL interrupt handlers header file
  - ADC/ADC_Regular_injected_groups/Inc/main.h                  Header for main.c module  
  - ADC/ADC_Regular_injected_groups/Src/stm32l1xx_it.c          HAL interrupt handlers
  - ADC/ADC_Regular_injected_groups/Src/main.c                  Main program
  - ADC/ADC_Regular_injected_groups/Src/stm32l1xx_hal_msp.c     HAL MSP file
  - ADC/ADC_Regular_injected_groups/Src/system_stm32l1xx.c      STM32L1xx system source file

@par Hardware and Software environment 

  - This example runs on STM32L1xx devices.

  - This example has been tested with STM32L100C-Discovery board and can be
    easily tailored to any other supported device and development board. 

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 */
