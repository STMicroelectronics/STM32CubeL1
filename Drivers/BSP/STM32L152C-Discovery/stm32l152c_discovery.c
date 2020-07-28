/**
  ******************************************************************************
  * @file    stm32l152c_discovery.c
  * @author  MCD Application Team
  * @brief   This file provides
  *            - set of firmware functions to manage Led and push-button
  *          available on STM32L152C-Discovery board from STMicroelectronics.  
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
#include "stm32l152c_discovery.h"

/** @addtogroup BSP
  * @{
  */ 

/** @defgroup STM32L152C_DISCOVERY STM32L152C-Discovery
  * @brief This file provides firmware functions to manage Leds and push-buttons
  *        available on STM32L152C discovery board from STMicroelectronics.
  * @{
  */ 

/** @defgroup STM32L152C_Discovery_Common Common
  * @{
  */ 
  
/** @defgroup STM32L152C_DISCOVERY_Private_Defines Private Defines
  * @{
  */ 
  
/**
* @brief STM32L152C-Discovery BSP Driver version number
*/
#define __STM32L152C_DISCO_BSP_VERSION_MAIN   (0x01) /*!< [31:24] main version */
#define __STM32L152C_DISCO_BSP_VERSION_SUB1   (0x00) /*!< [23:16] sub1 version */
#define __STM32L152C_DISCO_BSP_VERSION_SUB2   (0x05) /*!< [15:8]  sub2 version */
#define __STM32L152C_DISCO_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define __STM32L152C_DISCO_BSP_VERSION         ((__STM32L152C_DISCO_BSP_VERSION_MAIN << 24)\
                                             |(__STM32L152C_DISCO_BSP_VERSION_SUB1 << 16)\
                                             |(__STM32L152C_DISCO_BSP_VERSION_SUB2 << 8 )\
                                             |(__STM32L152C_DISCO_BSP_VERSION_RC))
/**
  * @}
  */ 


/** @defgroup STM32L152C_DISCOVERY_Private_Variables Private Variables
  * @{
  */ 
GPIO_TypeDef* GPIO_PORT[LEDn] = {LED3_GPIO_PORT,
                                 LED4_GPIO_PORT};

const uint16_t GPIO_PIN[LEDn] = {LED3_PIN,
                                 LED4_PIN};


GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {USER_BUTTON_GPIO_PORT}; 
const uint16_t BUTTON_PIN[BUTTONn] = {USER_BUTTON_PIN}; 
const uint8_t BUTTON_IRQn[BUTTONn] = {USER_BUTTON_EXTI_IRQn};

/**
  * @}
  */ 

/** @defgroup STM32L152C_DISCOVERY_Exported_Functions Exported Functions
  * @{
  */ 

/**
  * @brief  This method returns the STM32L152C-Discovery BSP Driver revision
  * @retval version : 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
  return __STM32L152C_DISCO_BSP_VERSION;
}

/** @defgroup STM32152C_DISCOVERY_LED_Functions LED Functions
  * @{
  */ 

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void BSP_LED_Init(Led_TypeDef Led)
{
  GPIO_InitTypeDef  gpioinitstruct = {0};
  
  /* Enable the GPIO_LED Clock */
  LEDx_GPIO_CLK_ENABLE(Led);

  /* Configure the GPIO_LED pin */
  gpioinitstruct.Pin   = GPIO_PIN[Led];
  gpioinitstruct.Mode  = GPIO_MODE_OUTPUT_PP;
  gpioinitstruct.Pull  = GPIO_NOPULL;
  gpioinitstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIO_PORT[Led], &gpioinitstruct);

  /* Reset PIN to switch off the LED */
  HAL_GPIO_WritePin(GPIO_PORT[Led],GPIO_PIN[Led], GPIO_PIN_RESET);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
void BSP_LED_On(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_SET); 
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4 
  * @retval None
  */
void BSP_LED_Off(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(GPIO_PORT[Led], GPIO_PIN[Led], GPIO_PIN_RESET); 
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *   This parameter can be one of following parameters:
  *     @arg LED3
  *     @arg LED4  
  * @retval None
  */
void BSP_LED_Toggle(Led_TypeDef Led)
{
  HAL_GPIO_TogglePin(GPIO_PORT[Led], GPIO_PIN[Led]);
}

/**
  * @}
  */ 

/** @defgroup STM32152C_DISCOVERY_BUTTON_Functions BUTTON Functions
  * @{
  */ 

/**
  * @brief  Configures Button GPIO and EXTI Line.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter should be: BUTTON_USER
  * @param  Mode: Specifies Button mode.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                     generation capability  
  * @retval None
  */
void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef Mode)
{
  GPIO_InitTypeDef gpioinitstruct = {0};

  /* Enable the BUTTON Clock */
  BUTTONx_GPIO_CLK_ENABLE(Button);

  if (Mode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    gpioinitstruct.Pin   = BUTTON_PIN[Button];
    gpioinitstruct.Mode  = GPIO_MODE_INPUT;
    gpioinitstruct.Pull  = GPIO_NOPULL;
    gpioinitstruct.Speed = GPIO_SPEED_FREQ_HIGH;
  
    HAL_GPIO_Init(BUTTON_PORT[Button], &gpioinitstruct);
  }
 
  if (Mode == BUTTON_MODE_EXTI)
  {
    /* Configure Button pin as input with External interrupt */
    gpioinitstruct.Pin   = BUTTON_PIN[Button];
    gpioinitstruct.Pull  = GPIO_NOPULL;
    gpioinitstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    gpioinitstruct.Mode  = GPIO_MODE_IT_RISING; 
    HAL_GPIO_Init(BUTTON_PORT[Button], &gpioinitstruct);

    /* Enable and set Button EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(BUTTON_IRQn[Button]), 0x0F, 0);
    HAL_NVIC_EnableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
  }
}

/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter should be: BUTTON_USER  
  * @retval Button state.
  */
uint32_t BSP_PB_GetState(Button_TypeDef Button)
{
  return HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]);
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

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
