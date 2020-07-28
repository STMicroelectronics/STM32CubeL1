/**
  ******************************************************************************
  * @file    LCD/LCD_SegmentsDrive/Inc/main.h 
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"
#include "stm32l152d_eval.h"
#include "stm32l152d_eval_glass_lcd.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* ADC peripheral configuration defines */
#define ADC_INSTANCE            ADC1           
#define ADC_CLK_ENABLE()        __HAL_RCC_ADC1_CLK_ENABLE()
#define ADC_PIN                 GPIO_PIN_10           /* PF.10 */
#define ADC_PORT                GPIOF
#define ADC_PORT_CLK_ENABLE()   __HAL_RCC_GPIOF_CLK_ENABLE()
#define ADC_CHANNEL             ADC_CHANNEL_31

/* ADC DMA Channel definitions */
#define DMA_INSTANCE            DMA1_Channel1
#define DMA_CLK_ENABLE()        __HAL_RCC_DMA1_CLK_ENABLE()
#define DMA_IRQ                 DMA1_Channel1_IRQn
#define DMA_IRQ_HANDLER         DMA1_Channel1_IRQHandler

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
