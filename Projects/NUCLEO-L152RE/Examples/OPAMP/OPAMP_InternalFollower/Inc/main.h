/**
  ******************************************************************************
  * @file    OPAMP/OPAMP_InternalFollower/Inc/main.h
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
#include "stm32l1xx_nucleo.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* User can use this section to tailor peripherals instances under use and
   associated resources */

/* ## Definition of ADC related resources ################################### */
/* Definition of ADCx clock resources */
#define ADCx                                ADC1
#define ADCx_CLK_ENABLE()                   __HAL_RCC_ADC1_CLK_ENABLE()

#define ADCx_FORCE_RESET()                  __HAL_RCC_ADC1_FORCE_RESET()
#define ADCx_RELEASE_RESET()                __HAL_RCC_ADC1_RELEASE_RESET()

/* Definition of ADCx channels */
#define ADCx_CHANNEL_TO_OPAMP1_OUTPOUT                       ADC_CHANNEL_8

/* Definition of ADCx channels pins */
#define ADCx_CHANNEL_TO_OPAMP1_OUTPOUT_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define ADCx_CHANNEL_TO_OPAMP1_OUTPOUT_GPIO_PORT             GPIOA
#define ADCx_CHANNEL_TO_OPAMP1_OUTPOUT_PIN                   GPIO_PIN_4

/* Definition of ADCx NVIC resources */
#define ADCx_IRQn                           ADC1_IRQn
#define ADCx_IRQHandler                     ADC1_IRQHandler

/* Definition of ADCx DMA resources */
#define ADCx_DMA_CLK_ENABLE()               __HAL_RCC_DMA1_CLK_ENABLE()
#define ADCx_DMA                            DMA1_Channel1

#define ADCx_DMA_IRQn                       DMA1_Channel1_IRQn
#define ADCx_DMA_IRQHandler                 DMA1_Channel1_IRQHandler

/* ## Definition of DAC related resources ################################### */
/* Definition of DACx clock resources */
#define DACx                                DAC
#define DACx_CLK_ENABLE()                   __HAL_RCC_DAC_CLK_ENABLE()
#define DACx_CHANNEL_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define DACx_FORCE_RESET()                  __HAL_RCC_DAC_FORCE_RESET()
#define DACx_RELEASE_RESET()                __HAL_RCC_DAC_RELEASE_RESET()

/* Definition of DACx channels */
#define DACx_CHANNEL_TO_OPAMP1_NONINV_INPUT                  DAC_CHANNEL_1

/* Definition of DACx channels pins */
#define DACx_CHANNEL_TO_OPAMP1_NONINV_INPUT_PIN              GPIO_PIN_4
#define DACx_CHANNEL_TO_OPAMP1_NONINV_INPUT_GPIO_PORT        GPIOA

/* Definition of DACx NVIC resources */
#define DAC_IRQn                           DAC_IRQn
#define DAC_IRQHandler                     DAC_IRQHandler

/* Definition of DACx DMA resources */
#define DACx_CHANNEL_TO_OPAMP1_NONINV_INPUT_DMA_CLK_ENABLE() __HAL_RCC_DMA1_CLK_ENABLE()
#define DACx_CHANNEL_TO_OPAMP1_NONINV_INPUT_DMA              DMA1_Channel2

#define DACx_CHANNEL_TO_OPAMP1_NONINV_INPUT_DMA_IRQn         DMA1_Channel2_IRQn
#define DACx_CHANNEL_TO_OPAMP1_NONINV_INPUT_DMA_IRQHandler   DMA1_Channel2_IRQHandler

/* ## Definition of TIM related resources ################################### */
/* Definition of TIMx clock resources */
#define TIMx                                TIM2
#define TIMx_CLK_ENABLE()                   __HAL_RCC_TIM2_CLK_ENABLE()

#define TIMx_FORCE_RESET()                  __HAL_RCC_TIM2_FORCE_RESET()
#define TIMx_RELEASE_RESET()                __HAL_RCC_TIM2_RELEASE_RESET()

#define ADC_EXTERNALTRIGCONV_Tx_TRGO        ADC_EXTERNALTRIGCONV_T2_TRGO
#define DAC_TRIGGER_Tx_TRGO                 DAC_TRIGGER_T2_TRGO

/* ## Definition of OPAMP related resources ################################### */
/* Definition of OPAMPx clock resources */
#define OPAMPx                                OPAMP2
#define OPAMPx_CLK_ENABLE()                   __HAL_RCC_OPAMP_CLK_ENABLE()
#define OPAMPx_NON_INVERTING_INPUT_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define OPAMPx_OUTPUT_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOB_CLK_ENABLE()

#define OPAMPx_FORCE_RESET()                  __HAL_RCC_DAC_FORCE_RESET()
#define OPAMPx_RELEASE_RESET()                __HAL_RCC_DAC_RELEASE_RESET()
   
/* Definition of OPAMPx channels pins */
#define OPAMP2_NON_INVERTING_INPUT_PIN        GPIO_PIN_6
#define OPAMP2_NON_INVERTING_INPUT_GPIO_PORT  GPIOA
#define OPAMP2_OUTPUT_PIN                     GPIO_PIN_0
#define OPAMP2_OUTPUT_GPIO_PORT               GPIOB

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */
