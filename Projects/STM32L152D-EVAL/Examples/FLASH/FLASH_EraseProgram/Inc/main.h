/**
  ******************************************************************************
  * @file    FLASH/FLASH_EraseProgram/Inc/main.h
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


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Base address of the Flash sectors */
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
#define ADDR_FLASH_PAGE_65  ((uint32_t)0x08004100) /* Base @ of Page 65, 256 bytes */
#define ADDR_FLASH_PAGE_66  ((uint32_t)0x08004200) /* Base @ of Page 66, 256 bytes */
#define ADDR_FLASH_PAGE_67  ((uint32_t)0x08004300) /* Base @ of Page 67, 256 bytes */
#define ADDR_FLASH_PAGE_68  ((uint32_t)0x08004400) /* Base @ of Page 68, 256 bytes */
#define ADDR_FLASH_PAGE_69  ((uint32_t)0x08004500) /* Base @ of Page 69, 256 bytes */
#define ADDR_FLASH_PAGE_70  ((uint32_t)0x08004600) /* Base @ of Page 70, 256 bytes */
#define ADDR_FLASH_PAGE_71  ((uint32_t)0x08004700) /* Base @ of Page 71, 256 bytes */
#define ADDR_FLASH_PAGE_72  ((uint32_t)0x08004800) /* Base @ of Page 72, 256 bytes */
#define ADDR_FLASH_PAGE_73  ((uint32_t)0x08004900) /* Base @ of Page 73, 256 bytes */
#define ADDR_FLASH_PAGE_74  ((uint32_t)0x08004A00) /* Base @ of Page 74, 256 bytes */
#define ADDR_FLASH_PAGE_75  ((uint32_t)0x08004B00) /* Base @ of Page 75, 256 bytes */
#define ADDR_FLASH_PAGE_76  ((uint32_t)0x08004C00) /* Base @ of Page 76, 256 bytes */
#define ADDR_FLASH_PAGE_77  ((uint32_t)0x08004D00) /* Base @ of Page 77, 256 bytes */
#define ADDR_FLASH_PAGE_78  ((uint32_t)0x08004E00) /* Base @ of Page 78, 256 bytes */
#define ADDR_FLASH_PAGE_79  ((uint32_t)0x08004F00) /* Base @ of Page 79, 256 bytes */
#define ADDR_FLASH_PAGE_80  ((uint32_t)0x08005000) /* Base @ of Page 80, 256 bytes */
#define ADDR_FLASH_PAGE_81  ((uint32_t)0x08005100) /* Base @ of Page 81, 256 bytes */
#define ADDR_FLASH_PAGE_82  ((uint32_t)0x08005200) /* Base @ of Page 82, 256 bytes */
#define ADDR_FLASH_PAGE_83  ((uint32_t)0x08005300) /* Base @ of Page 83, 256 bytes */
#define ADDR_FLASH_PAGE_84  ((uint32_t)0x08005400) /* Base @ of Page 84, 256 bytes */
#define ADDR_FLASH_PAGE_85  ((uint32_t)0x08005500) /* Base @ of Page 85, 256 bytes */
#define ADDR_FLASH_PAGE_86  ((uint32_t)0x08005600) /* Base @ of Page 86, 256 bytes */
#define ADDR_FLASH_PAGE_87  ((uint32_t)0x08005700) /* Base @ of Page 87, 256 bytes */
#define ADDR_FLASH_PAGE_88  ((uint32_t)0x08005800) /* Base @ of Page 88, 256 bytes */
#define ADDR_FLASH_PAGE_89  ((uint32_t)0x08005900) /* Base @ of Page 89, 256 bytes */
#define ADDR_FLASH_PAGE_90  ((uint32_t)0x08005A00) /* Base @ of Page 90, 256 bytes */
#define ADDR_FLASH_PAGE_91  ((uint32_t)0x08005B00) /* Base @ of Page 91, 256 bytes */
#define ADDR_FLASH_PAGE_92  ((uint32_t)0x08005C00) /* Base @ of Page 92, 256 bytes */
#define ADDR_FLASH_PAGE_93  ((uint32_t)0x08005D00) /* Base @ of Page 93, 256 bytes */
#define ADDR_FLASH_PAGE_94  ((uint32_t)0x08005E00) /* Base @ of Page 94, 256 bytes */
#define ADDR_FLASH_PAGE_95  ((uint32_t)0x08005F00) /* Base @ of Page 95, 256 bytes */
#define ADDR_FLASH_PAGE_96  ((uint32_t)0x08006000) /* Base @ of Page 96, 256 bytes */
#define ADDR_FLASH_PAGE_97  ((uint32_t)0x08006100) /* Base @ of Page 97, 256 bytes */
#define ADDR_FLASH_PAGE_98  ((uint32_t)0x08006200) /* Base @ of Page 98, 256 bytes */
#define ADDR_FLASH_PAGE_99  ((uint32_t)0x08006300) /* Base @ of Page 99, 256 bytes */
#define ADDR_FLASH_PAGE_100 ((uint32_t)0x08006400) /* Base @ of Page 100, 256 bytes */
#define ADDR_FLASH_PAGE_101 ((uint32_t)0x08006500) /* Base @ of Page 101, 256 bytes */
#define ADDR_FLASH_PAGE_102 ((uint32_t)0x08006600) /* Base @ of Page 102, 256 bytes */
#define ADDR_FLASH_PAGE_103 ((uint32_t)0x08006700) /* Base @ of Page 103, 256 bytes */
#define ADDR_FLASH_PAGE_104 ((uint32_t)0x08006800) /* Base @ of Page 104, 256 bytes */
#define ADDR_FLASH_PAGE_105 ((uint32_t)0x08006900) /* Base @ of Page 105, 256 bytes */
#define ADDR_FLASH_PAGE_106 ((uint32_t)0x08006A00) /* Base @ of Page 106, 256 bytes */
#define ADDR_FLASH_PAGE_107 ((uint32_t)0x08006B00) /* Base @ of Page 107, 256 bytes */
#define ADDR_FLASH_PAGE_108 ((uint32_t)0x08006C00) /* Base @ of Page 108, 256 bytes */
#define ADDR_FLASH_PAGE_109 ((uint32_t)0x08006D00) /* Base @ of Page 109, 256 bytes */
#define ADDR_FLASH_PAGE_110 ((uint32_t)0x08006E00) /* Base @ of Page 110, 256 bytes */
#define ADDR_FLASH_PAGE_111 ((uint32_t)0x08006F00) /* Base @ of Page 111, 256 bytes */
#define ADDR_FLASH_PAGE_112 ((uint32_t)0x08007000) /* Base @ of Page 112, 256 bytes */
#define ADDR_FLASH_PAGE_113 ((uint32_t)0x08007100) /* Base @ of Page 113, 256 bytes */
#define ADDR_FLASH_PAGE_114 ((uint32_t)0x08007200) /* Base @ of Page 114, 256 bytes */
#define ADDR_FLASH_PAGE_115 ((uint32_t)0x08007300) /* Base @ of Page 115, 256 bytes */
#define ADDR_FLASH_PAGE_116 ((uint32_t)0x08007400) /* Base @ of Page 116, 256 bytes */
#define ADDR_FLASH_PAGE_117 ((uint32_t)0x08007500) /* Base @ of Page 117, 256 bytes */
#define ADDR_FLASH_PAGE_118 ((uint32_t)0x08007600) /* Base @ of Page 118, 256 bytes */
#define ADDR_FLASH_PAGE_119 ((uint32_t)0x08007700) /* Base @ of Page 119, 256 bytes */
#define ADDR_FLASH_PAGE_120 ((uint32_t)0x08007800) /* Base @ of Page 120, 256 bytes */
#define ADDR_FLASH_PAGE_121 ((uint32_t)0x08007900) /* Base @ of Page 121, 256 bytes */
#define ADDR_FLASH_PAGE_122 ((uint32_t)0x08007A00) /* Base @ of Page 122, 256 bytes */
#define ADDR_FLASH_PAGE_123 ((uint32_t)0x08007B00) /* Base @ of Page 123, 256 bytes */
#define ADDR_FLASH_PAGE_124 ((uint32_t)0x08007C00) /* Base @ of Page 124, 256 bytes */
#define ADDR_FLASH_PAGE_125 ((uint32_t)0x08007D00) /* Base @ of Page 125, 256 bytes */
#define ADDR_FLASH_PAGE_126 ((uint32_t)0x08007E00) /* Base @ of Page 126, 256 bytes */
#define ADDR_FLASH_PAGE_127 ((uint32_t)0x08007F00) /* Base @ of Page 127, 256 bytes */

/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
