/**
  @page TouchSensing_Linear_swacq  Touch Sensing Linear SW acquisition example
  
  @verbatim
  ******************************************************************************
  * @file    readme.txt
  * @author  MCD Application Team
  * @brief   Description of the Touch Sensing Linear example.
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

@par Application Description

Use of the STMTouch driver with 1 linear 
sensor in software acquisition mode.

Observed behaviour:

- The LED1, LED2, LED3 and LED4 follow the linear sensor position when touched.
- LED3 toggle each 100 ms  if any errors was occurred

@par Directory contents

    - TouchSensing_Linear_swacq\Inc\main.h                Header for main.c file
    - TouchSensing_Linear_swacq\Inc\stm32l1xx_hal_conf.h  HAL Library configuration file
    - TouchSensing_Linear_swacq\Inc\stm32l1xx_it.h        Header for stm32l1xx_it.c file
    - TouchSensing_Linear_swacq\Src\stmCriticalSection.h  Header for stmCriticalSection.c file
    - TouchSensing_Linear_swacq\Inc\tsl_conf.h            STMTouch driver configuration file
    - TouchSensing_Linear_swacq\Inc\tsl_user.h            Header for tsl_user.c file

    - TouchSensing_Linear_swacq\Src\main.c                Main program file
    - TouchSensing_Linear_swacq\Src\stm32l1xx_hal_msp.c   HAL MSP module file
    - TouchSensing_Linear_swacq\Src\stm32l1xx_it.c        Interrupt handlers file
    - TouchSensing_Linear_swacq\Src\stmCriticalSection.c  STMStudio lock/unlock mechanism file
    - TouchSensing_Linear_swacq\Src\system_stm32l1xx.c    System initialization file
    - TouchSensing_Linear_swacq\Src\tsl_user.c            Touchsensing channels/banks description file

@par Hardware and Software environment

  - This example runs on STM32L152xD devices.

  - This example has been tested with STM32L152D-EVAL
    boards and can be easily tailored to any other supported device
    and development board.
    
@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example


 */
