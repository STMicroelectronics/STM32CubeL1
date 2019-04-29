/**
  ******************************************************************************
  * @file    LCD/LCD_Contrast_Control/Src/stm32l1xx_hal_msp.c
  * @author  MCD Application Team
  * @brief   HAL MSP module.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32L1xx_HAL_Examples
  * @{
  */

/** @defgroup HAL_MSP
  * @brief HAL MSP module.
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/** @defgroup HAL_MSP_Private_Functions
  * @{
  */

/**
  * @brief  Initializes the ADC MSP.
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
  static DMA_HandleTypeDef  hdma_Adc = {0};
  GPIO_InitTypeDef          GPIO_InitStruct = {0};
  RCC_OscInitTypeDef        RCC_OscInitStructure = {0};
  
  /*** Configure the GPIOs ***/  
  /* Configure pin corresponding to the selected ADC Channel as analog input */
  /* Enable GPIO clock */
  ADC_PORT_CLK_ENABLE();
  
  GPIO_InitStruct.Pin = ADC_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(ADC_PORT, &GPIO_InitStruct);
  
  /*** Configure the ADC peripheral ***/
  
  /* Enable asynchronous clock source of ADC */
  HAL_RCC_GetOscConfig(&RCC_OscInitStructure);
  RCC_OscInitStructure.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStructure.HSIState = RCC_HSI_ON;
  RCC_OscInitStructure.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  HAL_RCC_OscConfig(&RCC_OscInitStructure);
  
  /* Enable ADC clock */
  ADC_CLK_ENABLE(); 
  
  /* DMA clock enable */
  DMA_CLK_ENABLE();
  
  /* Configure DMA handle init parameters */
  hdma_Adc.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  hdma_Adc.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_Adc.Init.MemInc              = DMA_MINC_DISABLE;
  hdma_Adc.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
  hdma_Adc.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;
  hdma_Adc.Init.Mode                = DMA_CIRCULAR;
  hdma_Adc.Init.Priority            = DMA_PRIORITY_HIGH;
  hdma_Adc.Instance                 = DMA_INSTANCE;
  
  /* Associate the DMA handle */
  __HAL_LINKDMA(hadc, DMA_Handle, hdma_Adc);
  
  /* Deinitialize the Channel for new transfer */
  HAL_DMA_DeInit(&hdma_Adc);
  
  /* Configure the DMA Channel */
  HAL_DMA_Init(&hdma_Adc);

  /* ADC DMA IRQ Channel configuration */
  HAL_NVIC_SetPriority(DMA_IRQ, 5, 0);
  HAL_NVIC_EnableIRQ(DMA_IRQ); 
}


/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
