/**
  ******************************************************************************
  * @file    main.h
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
#include "stdio.h"
#include "string.h"
#include "stm32l1xx_hal.h"
#include "stm32l152d_eval.h"
#include "stm32l152d_eval_lcd.h"
#include "stm32l152d_eval_eeprom.h"
#include "stm32l152d_eval_sd.h"
#include "stm32l152d_eval_tsensor.h"
#include "stm32l152d_eval_audio.h"
#include "stm32l152d_eval_nor.h"
#include "stm32l152d_eval_sram.h"
#include "stm32l152d_eval_glass_lcd.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  void   (*DemoFunc)(void);
  uint8_t DemoName[50]; 
  uint32_t DemoIndex;
}BSP_DemoTypedef;

/* Exported variables --------------------------------------------------------*/
extern const unsigned char stlogo[];

/* Exported constants --------------------------------------------------------*/

/* Defines for the Audio playing process */
#define PAUSE_STATUS     ((uint32_t)0x00) /* Audio Player in Pause Status */
#define RESUME_STATUS    ((uint32_t)0x01) /* Audio Player in Resume Status */
#define IDLE_STATUS      ((uint32_t)0x02) /* Audio Player in Idle Status */

/* Size of the recorder buffer */
#define WR_BUFFER_SIZE           512
#define AUDIO_PLAY_SAMPLE        0
#define AUDIO_PLAY_RECORDED      1

/* Exported macro ------------------------------------------------------------*/
#define COUNT_OF_EXAMPLE(x)    (sizeof(x)/sizeof(BSP_DemoTypedef))

/* Exported functions ------------------------------------------------------- */
void LCD_demo (void);
void Log_demo(void);
void Joystick_demo (void);
void SD_demo (void);
void EEPROM_demo (void);
void TSENSOR_demo (void);
void AudioPlay_demo(void);
void AudioRecord_demo(void);
void NOR_demo(void);
void SRAM_demo(void);
uint8_t CheckForUserInput(void);
void Toggle_Leds(void);
void Error_Handler(void);

#endif /* __MAIN_H */
