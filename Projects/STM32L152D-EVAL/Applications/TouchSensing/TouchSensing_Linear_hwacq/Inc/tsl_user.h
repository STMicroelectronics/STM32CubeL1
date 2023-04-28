/**
  ******************************************************************************
  * @file    TouchSensing/TouchSensing_Linear_hwacq/Inc/tsl_user.h
  * @author  MCD Application Team
  * @brief   Touch-Sensing user configuration.
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
#ifndef __TSL_USER_H
#define __TSL_USER_H

#include "tsl.h"
#include "stm32l1xx_hal.h"

/* Select if you use STMStudio software (0=No, 1=Yes) */
#define USE_STMSTUDIO (0)

#if USE_STMSTUDIO > 0
#include "stmCriticalSection.h"
#define STMSTUDIO_LOCK {enterLock();}
#define STMSTUDIO_UNLOCK {exitLock();}
#else
#define STMSTUDIO_LOCK
#define STMSTUDIO_UNLOCK
#endif

typedef enum
{
  TSL_USER_STATUS_BUSY       = 0, /**< The bank acquisition is on-going */
  TSL_USER_STATUS_OK_NO_ECS  = 1, /**< The bank acquisition is ok, no time for ECS */
  TSL_USER_STATUS_OK_ECS_ON  = 2, /**< The bank acquisition is ok, ECS finished */
  TSL_USER_STATUS_OK_ECS_OFF = 3  /**< The bank acquisition is ok, ECS not executed */
} tsl_user_status_t;

/* Channel IOs definition */
#define CHANNEL_0_SRC    ((uint32_t)(GR11))
#define CHANNEL_0_DEST   (0)
#define CHANNEL_0_SAMPLE    (TSL_GROUP11_IO4)
#define CHANNEL_0_CHANNEL   (TSL_GROUP11_IO1)

#define CHANNEL_1_SRC    ((uint32_t)(GR11))
#define CHANNEL_1_DEST   (1)
#define CHANNEL_1_SAMPLE    (TSL_GROUP11_IO4)
#define CHANNEL_1_CHANNEL   (TSL_GROUP11_IO2)

#define CHANNEL_2_SRC    ((uint32_t)(GR11))
#define CHANNEL_2_DEST   (2)
#define CHANNEL_2_SAMPLE    (TSL_GROUP11_IO4)
#define CHANNEL_2_CHANNEL   (TSL_GROUP11_IO3)

/* Banks definition */
#define BANK_0_NBCHANNELS    (1)
#define BANK_0_SHIELD_SAMPLE        (TSL_GROUP6_IO4)
#define BANK_0_SHIELD_CHANNEL       (TSL_GROUP6_IO3)

#define BANK_1_NBCHANNELS    (1)
#define BANK_1_SHIELD_SAMPLE        (TSL_GROUP6_IO4)
#define BANK_1_SHIELD_CHANNEL       (TSL_GROUP6_IO3)

#define BANK_2_NBCHANNELS    (1)
#define BANK_2_SHIELD_SAMPLE        (TSL_GROUP6_IO4)
#define BANK_2_SHIELD_CHANNEL       (TSL_GROUP6_IO3)

/* User Parameters */
extern CONST TSL_Bank_T MyBanks[];
extern CONST TSL_LinRot_T MyLinRots[];
extern CONST TSL_Object_T MyObjects[];
extern TSL_ObjectGroup_T MyObjGroup;

void tsl_user_Init(void);
tsl_user_status_t tsl_user_Exec(void);
void tsl_user_SetThresholds(void);

#endif /* __TSL_USER_H */
