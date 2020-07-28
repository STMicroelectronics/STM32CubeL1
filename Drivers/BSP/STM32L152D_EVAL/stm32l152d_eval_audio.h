/**
  ******************************************************************************
  * @file    stm32l152d_eval_audio.h
  * @author  MCD Application Team
  * @brief   This file contains the common defines and functions prototypes for
  *          stm32l152d_eval_audio.c driver.
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
#ifndef __STM32L152D_EVAL_AUDIO_H
#define __STM32L152D_EVAL_AUDIO_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
/* Include audio component Driver */
#include "../Components/cs43l22/cs43l22.h"
#include "stm32l152d_eval.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32L152D_EVAL
  * @{
  */
    
/** @addtogroup STM32L152D_EVAL_AUDIO
  * @{
  */    


/** @defgroup STM32L152D_EVAL_AUDIO_OUT_Exported_Constants Exported Constants 
  * @{
  */ 


/*------------------------------------------------------------------------------
             AUDIO OUT CONFIGURATION
------------------------------------------------------------------------------*/

/* I2S peripheral configuration defines */
#define I2SOUT                          SPI2
#define I2SOUT_CLK_ENABLE()             __HAL_RCC_SPI2_CLK_ENABLE()
#define I2SOUT_SCK_SD_WS_AF             GPIO_AF5_SPI2
#define I2SOUT_SCK_SD_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2SOUT_MCK_CLK_ENABLE()         __HAL_RCC_GPIOC_CLK_ENABLE()
#define I2SOUT_WS_CLK_ENABLE()          __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2SOUT_WS_PIN                   GPIO_PIN_12             /* PB.12*/
#define I2SOUT_SCK_PIN                  GPIO_PIN_13             /* PB.13*/
#define I2SOUT_SD_PIN                   GPIO_PIN_15             /* PB.15*/
#define I2SOUT_MCK_PIN                  GPIO_PIN_6              /* PC.06*/
#define I2SOUT_SCK_SD_GPIO_PORT         GPIOB
#define I2SOUT_WS_GPIO_PORT             GPIOB
#define I2SOUT_MCK_GPIO_PORT            GPIOC

/* I2S DMA Channel definitions */
#define I2SOUT_DMAx_CLK_ENABLE()        __HAL_RCC_DMA1_CLK_ENABLE()
#define I2SOUT_DMAx_CHANNEL             DMA1_Channel5
#define I2SOUT_DMAx_IRQ                 DMA1_Channel5_IRQn
#define I2SOUT_DMAx_PERIPH_DATA_SIZE    DMA_PDATAALIGN_HALFWORD
#define I2SOUT_DMAx_MEM_DATA_SIZE       DMA_MDATAALIGN_HALFWORD
#define DMA_MAX_SZE                     0xFFFF

#define I2SOUT_IRQHandler               DMA1_Channel5_IRQHandler

/* Select the interrupt preemption priority and subpriority for the DMA interrupt */
#define AUDIO_OUT_IRQ_PREPRIO         5   /* Select the preemption priority level(0 is the highest) */

/*------------------------------------------------------------------------------
             AUDIO IN CONFIGURATION
------------------------------------------------------------------------------*/

/* ADC peripheral configuration defines */
#define AUDIO_IN_ADC_PIN                GPIO_PIN_3             /* PA.03*/
#define AUDIO_IN_ADC_PORT               GPIOA
#define AUDIO_IN_ADC_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define AUDIO_IN_ADC_CHANNEL            ADC_CHANNEL_3
   
/* ADC DMA Channel definitions */
#define AUDIO_IN_DMAx_CLK_ENABLE()      __HAL_RCC_DMA1_CLK_ENABLE()
#define AUDIO_IN_DMAx_CHANNEL           DMA1_Channel1
#define AUDIO_IN_DMAx_IRQ               DMA1_Channel1_IRQn
#define AUDIO_IN_DMAx_PERIPH_DATA_SIZE  DMA_PDATAALIGN_HALFWORD
#define AUDIO_IN_DMAx_MEM_DATA_SIZE     DMA_MDATAALIGN_HALFWORD

#define AUDIO_IN_IRQHandler             DMA1_Channel1_IRQHandler

/* Select the interrupt preemption priority and subpriority for the IT/DMA interrupt */
#define AUDIO_IN_IRQ_PREPRIO          6   /* Select the preemption priority level(0 is the highest) */

/* OPAMP peripheral configuration defines */
#define AUDIO_IN_OPAMP_PIN                (GPIO_PIN_1 | GPIO_PIN_2) /* PA.01 & PA.02*/
#define AUDIO_IN_OPAMP_PORT               GPIOA
#define AUDIO_IN_OPAMP_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()


/*------------------------------------------------------------------------------
             CONFIGURATION: Audio Driver Configuration parameters
------------------------------------------------------------------------------*/

/* Audio status definition */     
#define AUDIO_OK                              0
#define AUDIO_ERROR                           1
#define AUDIO_TIMEOUT                         2

/* AudioFreq * DataSize (2 bytes) * NumChannels (Stereo: 2) */
#define DEFAULT_AUDIO_IN_FREQ                 32000
#define DEFAULT_AUDIO_IN_BIT_RESOLUTION       16
#define DEFAULT_AUDIO_IN_CHANNEL_NBR          1 /* Mono = 1, Stereo = 2 */
#define DEFAULT_AUDIO_IN_VOLUME               64

/* PDM buffer input size */
#define INTERNAL_BUFF_SIZE                    128*DEFAULT_AUDIO_IN_FREQ/16000*DEFAULT_AUDIO_IN_CHANNEL_NBR
   
/*------------------------------------------------------------------------------
                    OPTIONAL Configuration defines parameters
------------------------------------------------------------------------------*/


/**
  * @}
  */ 

/** @defgroup STM32L152D_EVAL_AUDIO_Exported_Variables Exported Variables 
  * @{
  */ 
extern __IO uint16_t AudioInVolume;
/**
  * @}
  */ 

/** @defgroup STM32L152D_EVAL_AUDIO_Exported_Macros Exported Macros
  * @{
  */
#define DMA_MAX(_X_)                (((_X_) <= DMA_MAX_SZE)? (_X_):DMA_MAX_SZE)

/**
  * @}
  */

/** @addtogroup STM32L152D_EVAL_AUDIO_Exported_Functions 
  * @{
  */ 
  
/** @addtogroup STM32L152D_EVAL_AUDIO_OUT_Exported_Functions 
  * @{
  */ 
uint8_t BSP_AUDIO_OUT_Init(uint16_t OutputDevice, uint8_t Volume, uint32_t AudioFreq);
uint8_t BSP_AUDIO_OUT_Play(uint16_t* pBuffer, uint32_t Size);
uint8_t BSP_AUDIO_OUT_ChangeBuffer(uint16_t *pData, uint16_t Size);
uint8_t BSP_AUDIO_OUT_Pause(void);
uint8_t BSP_AUDIO_OUT_Resume(void);
uint8_t BSP_AUDIO_OUT_Stop(uint32_t Option);
uint8_t BSP_AUDIO_OUT_SetVolume(uint8_t Volume);
void    BSP_AUDIO_OUT_SetFrequency(uint32_t AudioFreq);
uint8_t BSP_AUDIO_OUT_SetMute(uint32_t Command);
uint8_t BSP_AUDIO_OUT_SetOutputMode(uint8_t Output);

/* User Callbacks: user has to implement these functions in his code if they are needed. */
/* This function is called when the requested data has been completely transferred.*/
void    BSP_AUDIO_OUT_TransferComplete_CallBack(void);

/* This function is called when half of the requested buffer has been transferred. */
void    BSP_AUDIO_OUT_HalfTransfer_CallBack(void);

/* This function is called when an Interrupt due to transfer error on or peripheral
   error occurs. */
void    BSP_AUDIO_OUT_Error_CallBack(void);

/**
  * @}
  */

/** @addtogroup STM32L152D_EVAL_AUDIO_IN_Exported_Functions
  * @{
  */ 
uint8_t BSP_AUDIO_IN_Init(uint32_t AudioFreq, uint32_t BitRes, uint32_t ChnlNbr);
uint8_t BSP_AUDIO_IN_Record(uint16_t *pData, uint32_t Size);
uint8_t BSP_AUDIO_IN_Stop(void);
uint8_t BSP_AUDIO_IN_Pause(void);
uint8_t BSP_AUDIO_IN_Resume(void);
uint8_t BSP_AUDIO_IN_SetVolume(uint8_t Volume);
/* User Callbacks: user has to implement these functions in his code if they are needed. */
/* This function should be implemented by the user application.
   It is called into this driver when the current buffer is filled to prepare the next
   buffer pointer and its size. */
void    BSP_AUDIO_IN_TransferComplete_CallBack(void);
void    BSP_AUDIO_IN_HalfTransfer_CallBack(void);

/* This function is called when an Interrupt due to transfer error on or peripheral
   error occurs. */
void    BSP_AUDIO_IN_Error_Callback(void);

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

#ifdef __cplusplus
}
#endif
   
#endif /* __STM32L152D_EVAL_AUDIO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
