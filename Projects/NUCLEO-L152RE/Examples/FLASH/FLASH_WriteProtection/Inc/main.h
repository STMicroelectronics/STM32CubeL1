/**
  ******************************************************************************
  * @file    FLASH/FLASH_WriteProtection/Inc/main.h
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
/* Base address of the Flash pages */
#define ADDR_FLASH_PAGE_0   ((uint32_t)0x08000000) /* Base @ of Page 0, 256 bytes */
#define ADDR_FLASH_PAGE_1   ((uint32_t)0x08000100) /* Base @ of Page 1, 256 bytes */
#define ADDR_FLASH_PAGE_2   ((uint32_t)0x08000200) /* Base @ of Page 2, 256 bytes */
#define ADDR_FLASH_PAGE_3   ((uint32_t)0x08000300) /* Base @ of Page 3, 256 bytes */
#define ADDR_FLASH_PAGE_4   ((uint32_t)0x08000400) /* Base @ of Page 4, 256 bytes */
#define ADDR_FLASH_PAGE_5   ((uint32_t)0x08000500) /* Base @ of Page 5, 256 bytes */
#define ADDR_FLASH_PAGE_6   ((uint32_t)0x08000600) /* Base @ of Page 6, 256 bytes */
#define ADDR_FLASH_PAGE_7   ((uint32_t)0x08000700) /* Base @ of Page 7, 256 bytes */
#define ADDR_FLASH_PAGE_8   ((uint32_t)0x08000800) /* Base @ of Page 8, 256 bytes */
#define ADDR_FLASH_PAGE_9   ((uint32_t)0x08000900) /* Base @ of Page 9, 256 bytes */
#define ADDR_FLASH_PAGE_10  ((uint32_t)0x08000A00) /* Base @ of Page 10, 256 bytes */
#define ADDR_FLASH_PAGE_11  ((uint32_t)0x08000B00) /* Base @ of Page 11, 256 bytes */
#define ADDR_FLASH_PAGE_12  ((uint32_t)0x08000C00) /* Base @ of Page 12, 256 bytes */
#define ADDR_FLASH_PAGE_13  ((uint32_t)0x08000D00) /* Base @ of Page 13, 256 bytes */
#define ADDR_FLASH_PAGE_14  ((uint32_t)0x08000E00) /* Base @ of Page 14, 256 bytes */
#define ADDR_FLASH_PAGE_15  ((uint32_t)0x08000F00) /* Base @ of Page 15, 256 bytes */
#define ADDR_FLASH_PAGE_16  ((uint32_t)0x08001000) /* Base @ of Page 16, 256 bytes */
#define ADDR_FLASH_PAGE_17  ((uint32_t)0x08001100) /* Base @ of Page 17, 256 bytes */
#define ADDR_FLASH_PAGE_18  ((uint32_t)0x08001200) /* Base @ of Page 18, 256 bytes */
#define ADDR_FLASH_PAGE_19  ((uint32_t)0x08001300) /* Base @ of Page 19, 256 bytes */
#define ADDR_FLASH_PAGE_20  ((uint32_t)0x08001400) /* Base @ of Page 20, 256 bytes */
#define ADDR_FLASH_PAGE_21  ((uint32_t)0x08001500) /* Base @ of Page 21, 256 bytes */
#define ADDR_FLASH_PAGE_22  ((uint32_t)0x08001600) /* Base @ of Page 22, 256 bytes */
#define ADDR_FLASH_PAGE_23  ((uint32_t)0x08001700) /* Base @ of Page 23, 256 bytes */
#define ADDR_FLASH_PAGE_24  ((uint32_t)0x08001800) /* Base @ of Page 24, 256 bytes */
#define ADDR_FLASH_PAGE_25  ((uint32_t)0x08001900) /* Base @ of Page 25, 256 bytes */
#define ADDR_FLASH_PAGE_26  ((uint32_t)0x08001A00) /* Base @ of Page 26, 256 bytes */
#define ADDR_FLASH_PAGE_27  ((uint32_t)0x08001B00) /* Base @ of Page 27, 256 bytes */
#define ADDR_FLASH_PAGE_28  ((uint32_t)0x08001C00) /* Base @ of Page 28, 256 bytes */
#define ADDR_FLASH_PAGE_29  ((uint32_t)0x08001D00) /* Base @ of Page 29, 256 bytes */
#define ADDR_FLASH_PAGE_30  ((uint32_t)0x08001E00) /* Base @ of Page 30, 256 bytes */
#define ADDR_FLASH_PAGE_31  ((uint32_t)0x08001F00) /* Base @ of Page 31, 256 bytes */
#define ADDR_FLASH_PAGE_32  ((uint32_t)0x08002000) /* Base @ of Page 32, 256 bytes */
#define ADDR_FLASH_PAGE_33  ((uint32_t)0x08002100) /* Base @ of Page 33, 256 bytes */
#define ADDR_FLASH_PAGE_34  ((uint32_t)0x08002200) /* Base @ of Page 34, 256 bytes */
#define ADDR_FLASH_PAGE_35  ((uint32_t)0x08002300) /* Base @ of Page 35, 256 bytes */
#define ADDR_FLASH_PAGE_36  ((uint32_t)0x08002400) /* Base @ of Page 36, 256 bytes */
#define ADDR_FLASH_PAGE_37  ((uint32_t)0x08002500) /* Base @ of Page 37, 256 bytes */
#define ADDR_FLASH_PAGE_38  ((uint32_t)0x08002600) /* Base @ of Page 38, 256 bytes */
#define ADDR_FLASH_PAGE_39  ((uint32_t)0x08002700) /* Base @ of Page 39, 256 bytes */
#define ADDR_FLASH_PAGE_40  ((uint32_t)0x08002800) /* Base @ of Page 40, 256 bytes */
#define ADDR_FLASH_PAGE_41  ((uint32_t)0x08002900) /* Base @ of Page 41, 256 bytes */
#define ADDR_FLASH_PAGE_42  ((uint32_t)0x08002A00) /* Base @ of Page 42, 256 bytes */
#define ADDR_FLASH_PAGE_43  ((uint32_t)0x08002B00) /* Base @ of Page 43, 256 bytes */
#define ADDR_FLASH_PAGE_44  ((uint32_t)0x08002C00) /* Base @ of Page 44, 256 bytes */
#define ADDR_FLASH_PAGE_45  ((uint32_t)0x08002D00) /* Base @ of Page 45, 256 bytes */
#define ADDR_FLASH_PAGE_46  ((uint32_t)0x08002E00) /* Base @ of Page 46, 256 bytes */
#define ADDR_FLASH_PAGE_47  ((uint32_t)0x08002F00) /* Base @ of Page 47, 256 bytes */
#define ADDR_FLASH_PAGE_48  ((uint32_t)0x08003000) /* Base @ of Page 48, 256 bytes */
#define ADDR_FLASH_PAGE_49  ((uint32_t)0x08003100) /* Base @ of Page 49, 256 bytes */
#define ADDR_FLASH_PAGE_50  ((uint32_t)0x08003200) /* Base @ of Page 50, 256 bytes */
#define ADDR_FLASH_PAGE_51  ((uint32_t)0x08003300) /* Base @ of Page 51, 256 bytes */
#define ADDR_FLASH_PAGE_52  ((uint32_t)0x08003400) /* Base @ of Page 52, 256 bytes */
#define ADDR_FLASH_PAGE_53  ((uint32_t)0x08003500) /* Base @ of Page 53, 256 bytes */
#define ADDR_FLASH_PAGE_54  ((uint32_t)0x08003600) /* Base @ of Page 54, 256 bytes */
#define ADDR_FLASH_PAGE_55  ((uint32_t)0x08003700) /* Base @ of Page 55, 256 bytes */
#define ADDR_FLASH_PAGE_56  ((uint32_t)0x08003800) /* Base @ of Page 56, 256 bytes */
#define ADDR_FLASH_PAGE_57  ((uint32_t)0x08003900) /* Base @ of Page 57, 256 bytes */
#define ADDR_FLASH_PAGE_58  ((uint32_t)0x08003A00) /* Base @ of Page 58, 256 bytes */
#define ADDR_FLASH_PAGE_59  ((uint32_t)0x08003B00) /* Base @ of Page 59, 256 bytes */
#define ADDR_FLASH_PAGE_60  ((uint32_t)0x08003C00) /* Base @ of Page 60, 256 bytes */
#define ADDR_FLASH_PAGE_61  ((uint32_t)0x08003D00) /* Base @ of Page 61, 256 bytes */
#define ADDR_FLASH_PAGE_62  ((uint32_t)0x08003E00) /* Base @ of Page 62, 256 bytes */
#define ADDR_FLASH_PAGE_63  ((uint32_t)0x08003F00) /* Base @ of Page 63, 256 bytes */
#define ADDR_FLASH_PAGE_64  ((uint32_t)0x08004000) /* Base @ of Page 64, 256 bytes */
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */
