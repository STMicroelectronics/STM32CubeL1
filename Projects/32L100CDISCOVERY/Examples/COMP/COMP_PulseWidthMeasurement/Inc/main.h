/**
  ******************************************************************************
  * @file    COMP/COMP_PulseWidthMeasurement/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
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
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"
#include "stm32l100c_discovery.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor COMPx instance under use and associated
   resources */

/* ## Definition of COMPx related resources ################################# */
/* Definition for COMPx clock resources */
#define COMPx_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOB_CLK_ENABLE()
#define COMPx_GPIO_CLK_DISABLE()       __HAL_RCC_GPIOB_CLK_DISABLE()

/* Definition for COMPx Channel Pin */
#define COMPx_PIN                      GPIO_PIN_5
#define COMPx_GPIO_PORT                GPIOB 

/* Definition for COMPx's NVIC */
#define COMPx_IRQn                     COMP_IRQn
#define COMPx_IRQHandler               COMP_IRQHandler

/* ## Definition of TIM related resources ################################### */
/* Definition of TIMx clock resources */
#define TIMx                            TIM2
#define TIMx_CLK_ENABLE()               __HAL_RCC_TIM2_CLK_ENABLE()

#define TIMx_FORCE_RESET()              __HAL_RCC_TIM2_FORCE_RESET()
#define TIMx_RELEASE_RESET()            __HAL_RCC_TIM2_RELEASE_RESET()

#define TIMx_IRQn                       TIM2_IRQn
#define TIMx_IRQHandler                 TIM2_IRQHandler

/* ## Definition of DAC related resources ################################### */
/* Definition of DACx clock resources */
#define DACx                            DAC
#define DACx_CLK_ENABLE()               __HAL_RCC_DAC_CLK_ENABLE()
#define DACx_CHANNEL_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()

#define DACx_FORCE_RESET()              __HAL_RCC_DAC_FORCE_RESET()
#define DACx_RELEASE_RESET()            __HAL_RCC_DAC_RELEASE_RESET()

/* Definition of DACx channels */
#define DACx_CHANNEL_SIGNAL_FOR_TEST            DAC_CHANNEL_1
#define DACx_CHANNEL_TO_COMP_INPUT_NEG          DAC_CHANNEL_2

/* Definition of DACx channels pins */
#define DACx_CHANNEL_SIGNAL_FOR_TEST_PIN        GPIO_PIN_4
#define DACx_CHANNEL_SIGNAL_FOR_TEST_GPIO_PORT  GPIOA

/* Definition of DACx DMA resources */
#define DACx_CHANNEL_SIGNAL_FOR_TEST_DMA_CLK_ENABLE()           __HAL_RCC_DMA1_CLK_ENABLE()
#define DACx_CHANNEL_SIGNAL_FOR_TEST_DMA                        DMA1_Channel2

#define DACx_CHANNEL_SIGNAL_FOR_TEST_DMA_IRQn                   DMA1_Channel2_IRQn
#define DACx_CHANNEL_SIGNAL_FOR_TEST_DMA_IRQHandler             DMA1_Channel2_IRQHandler

/* Definition of DACx NVIC resources */
#define DACx_IRQn                       DAC_IRQn
#define DACx_IRQHandler                 DAC_IRQHandler

/* For this example purpose, generate a periodic signal on a spare DAC        */
/* channel, so user has just to connect a wire between DAC channel and COMP   */
/* input to run this example.                                                 */
/* (this avoid to user the need of an external signal generator).             */
#define DAC_SPARE_CHANNEL_FOR_SIGNAL_TEST

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */
