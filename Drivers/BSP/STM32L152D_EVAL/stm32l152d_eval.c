/**
  ******************************************************************************
  * @file    stm32l152d_eval.c
  * @author  MCD Application Team
  * @brief   This file provides a set of firmware functions to manage Leds, 
  *          push-button and COM ports
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
  
/* Includes ------------------------------------------------------------------*/
#include "stm32l152d_eval.h"

/** @addtogroup BSP
  * @{
  */ 

/** @defgroup STM32L152D_EVAL STM32L152D-EVAL
  * @{
  */ 

/** @defgroup STM32L152D_EVAL_Common STM32L152D-EVAL Common
  * @{
  */ 

/** @defgroup STM32L152D_EVAL_Private_TypesDefinitions Private Types Definitions
  * @{
  */ 

typedef struct
{
  __IO uint16_t LCD_REG_R; /* Read Register */
  __IO uint16_t LCD_RAM_R; /* Read RAM */
  __IO uint16_t LCD_REG_W; /* Write Register */
  __IO uint16_t LCD_RAM_W; /* Write RAM */
} TFT_LCD_TypeDef;

/**
  * @}
  */ 

/** @defgroup STM32L152D_EVAL_Private_Defines Private Defines
  * @{
  */ 

/* LINK EEPROM SPI */
#define EEPROM_CMD_WREN         0x06  /*!< Write enable instruction */
#define EEPROM_CMD_WRDI         0x04  /*!< Write disable instruction */
#define EEPROM_CMD_RDSR         0x05  /*!< Read Status Register instruction  */
#define EEPROM_CMD_WRSR         0x01  /*!< Write Status Register instruction */
#define EEPROM_CMD_WRITE        0x02  /*!< Write to Memory instruction */
#define EEPROM_CMD_READ         0x03  /*!< Read from Memory instruction */

#define EEPROM_WIP_FLAG         0x01  /*!< Write In Progress (WIP) flag */

/**
 * @brief STM32L152D EVAL BSP Driver version number
   */
#define __STM32L152D_EVAL_BSP_VERSION_MAIN   (0x02) /*!< [31:24] main version */
#define __STM32L152D_EVAL_BSP_VERSION_SUB1   (0x01) /*!< [23:16] sub1 version */
#define __STM32L152D_EVAL_BSP_VERSION_SUB2   (0x01) /*!< [15:8]  sub2 version */
#define __STM32L152D_EVAL_BSP_VERSION_RC     (0x00) /*!< [7:0]  release candidate */
#define __STM32L152D_EVAL_BSP_VERSION            ((__STM32L152D_EVAL_BSP_VERSION_MAIN << 24)\
                                                |(__STM32L152D_EVAL_BSP_VERSION_SUB1 << 16)\
                                                |(__STM32L152D_EVAL_BSP_VERSION_SUB2 << 8 )\
                                                |(__STM32L152D_EVAL_BSP_VERSION_RC))


/* Note: LCD /CS is CE4 - Bank 4 of NOR/SRAM Bank 1~4 */
#define TFT_LCD_BASE           ((uint32_t)(0x60000000 | 0x0C000000))
#define TFT_LCD                ((TFT_LCD_TypeDef *) TFT_LCD_BASE)

/**
  * @}
  */


/** @defgroup STM32L152D_EVAL_Private_Variables Private Variables
  * @{
  */ 
/**
 * @brief LED variables
 */
GPIO_TypeDef* LED_PORT[LEDn] = {LED1_GPIO_PORT, 
                                LED2_GPIO_PORT, 
                                LED3_GPIO_PORT,
                                LED4_GPIO_PORT};

const uint16_t LED_PIN[LEDn] = {LED1_PIN, 
                                LED2_PIN, 
                                LED3_PIN,
                                LED4_PIN};

/**
 * @brief BUTTON variables
 */
GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {TAMPER_BUTTON_GPIO_PORT, 
                                      SEL_JOY_GPIO_PORT,
                                      LEFT_JOY_GPIO_PORT, 
                                      RIGHT_JOY_GPIO_PORT,
                                      DOWN_JOY_GPIO_PORT, 
                                      UP_JOY_GPIO_PORT}; 

const uint16_t BUTTON_PIN[BUTTONn] = {TAMPER_BUTTON_PIN, 
                                      SEL_JOY_PIN,
                                      LEFT_JOY_PIN, 
                                      RIGHT_JOY_PIN,
                                      DOWN_JOY_PIN, 
                                      UP_JOY_PIN}; 

const uint8_t BUTTON_IRQn[BUTTONn] = {TAMPER_BUTTON_EXTI_IRQn,
                                      SEL_JOY_EXTI_IRQn,
                                      LEFT_JOY_EXTI_IRQn,
                                      RIGHT_JOY_EXTI_IRQn,
                                      DOWN_JOY_EXTI_IRQn,
                                      UP_JOY_EXTI_IRQn};

/**
 * @brief JOYSTICK variables
 */
GPIO_TypeDef* JOY_PORT[JOYn] = {SEL_JOY_GPIO_PORT,
                                LEFT_JOY_GPIO_PORT, 
                                RIGHT_JOY_GPIO_PORT, 
                                DOWN_JOY_GPIO_PORT, 
                                UP_JOY_GPIO_PORT}; 

const uint16_t JOY_PIN[JOYn] = {SEL_JOY_PIN, 
                                LEFT_JOY_PIN, 
                                RIGHT_JOY_PIN, 
                                DOWN_JOY_PIN, 
                                UP_JOY_PIN}; 

const uint8_t JOY_IRQn[JOYn] = {SEL_JOY_EXTI_IRQn,
                                LEFT_JOY_EXTI_IRQn, 
                                RIGHT_JOY_EXTI_IRQn, 
                                DOWN_JOY_EXTI_IRQn, 
                                UP_JOY_EXTI_IRQn};

/**
 * @brief COM variables
 */
USART_TypeDef* COM_USART[COMn]   = {EVAL_COM1}; 

GPIO_TypeDef* COM_TX_PORT[COMn]   = {EVAL_COM1_TX_GPIO_PORT};
 
GPIO_TypeDef* COM_RX_PORT[COMn]   = {EVAL_COM1_RX_GPIO_PORT};

const uint16_t COM_TX_PIN[COMn]   = {EVAL_COM1_TX_PIN};

const uint16_t COM_RX_PIN[COMn]   = {EVAL_COM1_RX_PIN};
 
const uint16_t COM_TX_AF[COMn]    = {EVAL_COM1_TX_AF};

const uint16_t COM_RX_AF[COMn]    = {EVAL_COM1_RX_AF};
 
/**
 * @brief BUS variables
 */
#ifdef HAL_SPI_MODULE_ENABLED
uint32_t SpixTimeout = EVAL_SPIx_TIMEOUT_MAX;        /*<! Value of Timeout when SPI communication fails */
static SPI_HandleTypeDef heval_Spi;
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_I2C_MODULE_ENABLED
uint32_t I2cxTimeout = EVAL_I2Cx_TIMEOUT_MAX;   /*<! Value of Timeout when I2C communication fails */
I2C_HandleTypeDef heval_I2c;
#endif /* HAL_I2C_MODULE_ENABLED */

/**
  * @}
  */ 

#if defined(HAL_SRAM_MODULE_ENABLED)

static void     FSMC_BANK4_WriteData(uint16_t Data);
static void     FSMC_BANK4_WriteReg(uint8_t Reg);
static uint16_t FSMC_BANK4_ReadData(void);
static void     FSMC_BANK4_Init(void);
static void     FSMC_BANK4_MspInit(void);

/* LCD IO functions */
void            LCD_IO_Init(void);
void            LCD_IO_WriteData(uint16_t RegValue);
void            LCD_IO_WriteMultipleData(uint8_t *pData, uint32_t Size);
void            LCD_IO_WriteReg(uint8_t Reg);
uint16_t        LCD_IO_ReadData(uint16_t Reg);
void            LCD_Delay (uint32_t delay);
#endif /*HAL_SRAM_MODULE_ENABLED*/

/* I2Cx bus function */
#ifdef HAL_I2C_MODULE_ENABLED
/* Link function for I2C EEPROM peripheral */
static void               I2Cx_Init(void);
static void               I2Cx_WriteData(uint16_t Addr, uint8_t Reg, uint8_t Value);
static HAL_StatusTypeDef  I2Cx_WriteBuffer(uint16_t Addr, uint8_t Reg, uint16_t RegSize, uint8_t *pBuffer, uint16_t Length);
static uint8_t            I2Cx_ReadData(uint16_t Addr, uint8_t Reg);
static HAL_StatusTypeDef  I2Cx_ReadBuffer(uint16_t Addr, uint8_t Reg, uint16_t RegSize, uint8_t *pBuffer, uint16_t Length);
static HAL_StatusTypeDef  I2Cx_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);
static void               I2Cx_Error (void);
static void               I2Cx_MspInit(I2C_HandleTypeDef *hi2c);  

/* Link function for EEPROM peripheral over I2C */
void                      EEPROM_I2C_IO_Init(void);
HAL_StatusTypeDef         EEPROM_I2C_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef         EEPROM_I2C_IO_ReadData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef         EEPROM_I2C_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);

/* Link functions for Temperature Sensor peripheral */
void                      TSENSOR_IO_Init(void);
void                      TSENSOR_IO_Write(uint16_t DevAddress, uint8_t* pBuffer, uint8_t WriteAddr, uint16_t Length);
void                      TSENSOR_IO_Read(uint16_t DevAddress, uint8_t* pBuffer, uint8_t ReadAddr, uint16_t Length);
uint16_t                  TSENSOR_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials);

/* Link function for Audio peripheral */
void                      AUDIO_IO_Init(void);
void          			  AUDIO_IO_DeInit(void);
void                      AUDIO_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t                   AUDIO_IO_Read(uint8_t Addr, uint8_t Reg);

#endif /* HAL_I2C_MODULE_ENABLED */

/* SPIx bus function */
#ifdef HAL_SPI_MODULE_ENABLED
static void               SPIx_Init(void);
static void               SPIx_Write(uint8_t Value);
static uint32_t           SPIx_Read(void);
static void               SPIx_Error (void);
static void               SPIx_MspInit(SPI_HandleTypeDef *hspi);

/* Link function for EEPROM peripheral over SPI */
void                      EEPROM_SPI_IO_Init(void);
void                      EEPROM_SPI_IO_WriteByte(uint8_t Data);
uint8_t                   EEPROM_SPI_IO_ReadByte(void);
HAL_StatusTypeDef         EEPROM_SPI_IO_WriteData(uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef         EEPROM_SPI_IO_ReadData(uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef         EEPROM_SPI_IO_WaitEepromStandbyState(void);

#endif /* HAL_SPI_MODULE_ENABLED */


/** @defgroup STM32L152D_EVAL_Exported_Functions Exported Functions
  * @{
  */ 

/**
  * @brief  This method returns the STM32L152D EVAL BSP Driver revision
  * @retval version : 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
  return __STM32L152D_EVAL_BSP_VERSION;
}

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void BSP_LED_Init(Led_TypeDef Led)
{
  GPIO_InitTypeDef  gpioinitstruct = {0};
  
  /* Enable the GPIO_LED clock */
  LEDx_GPIO_CLK_ENABLE(Led);

  /* Configure the GPIO_LED pin */
  gpioinitstruct.Pin    = LED_PIN[Led];
  gpioinitstruct.Mode   = GPIO_MODE_OUTPUT_PP;
  gpioinitstruct.Pull   = GPIO_NOPULL;
  gpioinitstruct.Speed  = GPIO_SPEED_FREQ_VERY_HIGH;

  HAL_GPIO_Init(LED_PORT[Led], &gpioinitstruct);

  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_SET);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void BSP_LED_On(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_RESET);
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void BSP_LED_Off(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_SET);
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void BSP_LED_Toggle(Led_TypeDef Led)
{
  HAL_GPIO_TogglePin(LED_PORT[Led], LED_PIN[Led]);
}

/**
  * @brief  Configures push button GPIO and EXTI Line.
  * @param  Button: Button to be configured.
  *   This parameter can be one of the following values: 
  *     @arg BUTTON_TAMPER: Key/Tamper Push Button 
  *     @arg BUTTON_SEL   : Sel Push Button on Joystick
  *     @arg BUTTON_LEFT  : Left Push Button on Joystick
  *     @arg BUTTON_RIGHT : Right Push Button on Joystick
  *     @arg BUTTON_DOWN  : Down Push Button on Joystick
  *     @arg BUTTON_UP    : Up Push Button on Joystick
  * @param  Button_Mode: Button mode requested.
  *   This parameter can be one of the following values:   
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line
  *                            with interrupt generation capability
  * @retval None
  */
void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode)
{
  GPIO_InitTypeDef gpioinitstruct = {0};

  /* Enable the corresponding Push Button clock */
  BUTTONx_GPIO_CLK_ENABLE(Button);
  
  /* Configure Push Button pin as input */
  gpioinitstruct.Pin    = BUTTON_PIN[Button];
  gpioinitstruct.Pull   = GPIO_NOPULL;
  gpioinitstruct.Speed  = GPIO_SPEED_FREQ_VERY_HIGH;
    
  if (Button_Mode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    gpioinitstruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(BUTTON_PORT[Button], &gpioinitstruct);
  }
  else if (Button_Mode == BUTTON_MODE_EXTI)
  {
    if(Button != BUTTON_TAMPER)
    {
      /* Configure Joystick Button pin as input with External interrupt, falling edge */
      gpioinitstruct.Mode = GPIO_MODE_IT_FALLING;
    }
    else
    { 
      /* Configure Key Push Button pin as input with External interrupt, rising edge */
      gpioinitstruct.Mode = GPIO_MODE_IT_RISING;
    }
    HAL_GPIO_Init(BUTTON_PORT[Button], &gpioinitstruct);

    /* Enable and set Button EXTI Interrupt to the lowest priority */
    HAL_NVIC_SetPriority((IRQn_Type)(BUTTON_IRQn[Button]), 0x0F, 0);
    HAL_NVIC_EnableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
  }
}

/**
  * @brief  Returns the selected button state.
  * @param  Button: Button to be checked.
  *   This parameter can be one of the following values:
  *     @arg BUTTON_TAMPER: Key/Tamper Push Button 
  * @retval Button state
  */
uint32_t BSP_PB_GetState(Button_TypeDef Button)
{
  return HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/**
  * @brief  Configures all button of the joystick in GPIO or EXTI modes.
  * @param  Joy_Mode: Joystick mode.
  *    This parameter can be one of the following values:
  *     @arg  JOY_MODE_GPIO: Joystick pins will be used as simple IOs
  *     @arg  JOY_MODE_EXTI: Joystick pins will be connected to EXTI line 
  *                                 with interrupt generation capability  
  * @retval HAL_OK: if all initializations are OK. Other value if error.
  */
uint8_t BSP_JOY_Init(JOYMode_TypeDef Joy_Mode)
{
  JOYState_TypeDef joykey = JOY_NONE;
  GPIO_InitTypeDef gpioinitstruct = {0};

  /* Initialized the Joystick. */
  for(joykey = JOY_SEL; joykey < (JOY_SEL+JOYn) ; joykey++)
  {
    /* Enable the JOY clock */
    JOYx_GPIO_CLK_ENABLE(joykey);

    gpioinitstruct.Pin    = JOY_PIN[joykey];
    gpioinitstruct.Pull   = GPIO_NOPULL;
    gpioinitstruct.Speed  = GPIO_SPEED_FREQ_VERY_HIGH;

    if (Joy_Mode == JOY_MODE_GPIO)
    {
      /* Configure Joy pin as input */
      gpioinitstruct.Mode = GPIO_MODE_INPUT;
      HAL_GPIO_Init(JOY_PORT[joykey], &gpioinitstruct);
    }
    
    if (Joy_Mode == JOY_MODE_EXTI)
    {
      /* Configure Joy pin as input with External interrupt */
      gpioinitstruct.Mode = GPIO_MODE_IT_FALLING;
      HAL_GPIO_Init(JOY_PORT[joykey], &gpioinitstruct);

      /* Enable and set Joy EXTI Interrupt to the lowest priority */
      HAL_NVIC_SetPriority((IRQn_Type)(JOY_IRQn[joykey]), 0x0F, 0);
      HAL_NVIC_EnableIRQ((IRQn_Type)(JOY_IRQn[joykey]));
    }
  }
  
  return HAL_OK;
}

/**
  * @brief  Returns the current joystick status.
  * @retval Code of the joystick key pressed
  *          This code can be one of the following values:
  *            @arg  JOY_SEL
  *            @arg  JOY_DOWN
  *            @arg  JOY_LEFT
  *            @arg  JOY_RIGHT
  *            @arg  JOY_UP
  *            @arg  JOY_NONE
  */
JOYState_TypeDef BSP_JOY_GetState(void)
{
  JOYState_TypeDef joykey = JOY_NONE;
  
  for(joykey = JOY_SEL; joykey < (JOY_SEL+JOYn) ; joykey++)
  {
    if(HAL_GPIO_ReadPin(JOY_PORT[joykey], JOY_PIN[joykey]) == GPIO_PIN_RESET)
    {
      /* Return Code Joystick key pressed */
      return joykey;
    }
  }
  
  /* No Joystick key pressed */
  return JOY_NONE;
}

#ifdef HAL_UART_MODULE_ENABLED
/**
  * @brief  Configures COM port.
  * @param  COM: Specifies the COM port to be configured.
  *   This parameter can be one of following parameters:    
  *     @arg COM1
  * @param  huart: pointer to a UART_HandleTypeDef structure that
  *   contains the configuration information for the specified UART peripheral.
  * @retval None
  */
void BSP_COM_Init(COM_TypeDef COM, UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef gpioinitstruct = {0};

  /* Enable GPIO clock */
  COMx_TX_GPIO_CLK_ENABLE(COM);
  COMx_RX_GPIO_CLK_ENABLE(COM);

  /* Enable USART clock */
  COMx_CLK_ENABLE(COM);

  /* Configure USART Tx as alternate function push-pull */
  gpioinitstruct.Pin        = COM_TX_PIN[COM];
  gpioinitstruct.Mode       = GPIO_MODE_AF_PP;
  gpioinitstruct.Speed      = GPIO_SPEED_FREQ_VERY_HIGH;
  gpioinitstruct.Pull       = GPIO_PULLUP;
  gpioinitstruct.Alternate  = COM_TX_AF[COM];
  HAL_GPIO_Init(COM_TX_PORT[COM], &gpioinitstruct);
    
  /* Configure USART Rx as alternate function push-pull */
  gpioinitstruct.Pin        = COM_RX_PIN[COM];
  gpioinitstruct.Alternate  = COM_RX_AF[COM];
  HAL_GPIO_Init(COM_RX_PORT[COM], &gpioinitstruct);
  
  /* USART configuration */
  huart->Instance = COM_USART[COM];
  HAL_UART_Init(huart);
}
#endif /* HAL_UART_MODULE_ENABLED */

/**
  * @}
  */ 

/** @defgroup STM32L152D_EVAL_BusOperations_Functions Bus Operations Functions
  * @{
  */ 

/*******************************************************************************
                            BUS OPERATIONS
*******************************************************************************/

/*************************** FSMC Routines ************************************/
#if defined(HAL_SRAM_MODULE_ENABLED)
/**
  * @brief  Initializes FSMC_BANK4 MSP.
  * @retval None
  */
static void FSMC_BANK4_MspInit(void)
{
  GPIO_InitTypeDef gpioinitstruct = {0};
  
  /* Enable FMC clock */
  __HAL_RCC_FSMC_CLK_ENABLE();
  
  /* Enable GPIOs clock */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  
  /* Common GPIO configuration */
  gpioinitstruct.Mode      = GPIO_MODE_AF_PP;
  gpioinitstruct.Pull      = GPIO_PULLUP;
  gpioinitstruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  gpioinitstruct.Alternate = GPIO_AF12_FSMC;
  
  /* GPIOD configuration */
  /* Set PD.00(D2), PD.01(D3), PD.04(NOE), PD.05(NWE), PD.08(D13), PD.09(D14),
     PD.10(D15), PD.14(D0), PD.15(D1) as alternate function push pull */
  gpioinitstruct.Pin   = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 |
                         GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 | 
                         GPIO_PIN_15;
   
  HAL_GPIO_Init(GPIOD, &gpioinitstruct);

  /* GPIOE configuration */  
  /* Set PE.07(D4), PE.08(D5), PE.09(D6), PE.10(D7), PE.11(D8), PE.12(D9), PE.13(D10),
     PE.14(D11), PE.15(D12) as alternate function push pull */
  gpioinitstruct.Pin   = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | 
                         GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | 
                         GPIO_PIN_15;
  HAL_GPIO_Init(GPIOE, &gpioinitstruct);
  
  /* GPIOF configuration */  
  /* Set PF.00(A0 (RS)) and PF.01 (A1 (Level Shifter Direction) as alternate 
     function push pull */
  gpioinitstruct.Pin   = GPIO_PIN_0 | GPIO_PIN_1;
  HAL_GPIO_Init(GPIOF, &gpioinitstruct);
  
  /* GPIOG configuration */  
  /* Set PG.12(NE4 (LCD/CS)) as alternate function push pull - NE4(LCD /CS) */
  gpioinitstruct.Pin   = GPIO_PIN_12;
  HAL_GPIO_Init(GPIOG, &gpioinitstruct);  
}

/**
  * @brief  Initializes LCD IO.
  * @retval None
  */
static void FSMC_BANK4_Init(void) 
{  
  SRAM_HandleTypeDef          hsram;
  FSMC_NORSRAM_TimingTypeDef  sramtiming = {0};
  
  /*** Configure the SRAM Bank 4 ***/  
  /* Configure IPs */
  hsram.Instance  = FSMC_NORSRAM_DEVICE;
  hsram.Extended  = FSMC_NORSRAM_EXTENDED_DEVICE;

  sramtiming.AddressSetupTime       = 4;
  sramtiming.AddressHoldTime        = 3;
  sramtiming.DataSetupTime          = 7;
  sramtiming.BusTurnAroundDuration  = 1;
  sramtiming.CLKDivision            = 2;
  sramtiming.DataLatency            = 2;
  sramtiming.AccessMode             = FSMC_ACCESS_MODE_A;
  
  hsram.Init.NSBank             = FSMC_NORSRAM_BANK4;
  hsram.Init.DataAddressMux     = FSMC_DATA_ADDRESS_MUX_DISABLE;
  hsram.Init.MemoryType         = FSMC_MEMORY_TYPE_SRAM;
  hsram.Init.MemoryDataWidth    = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram.Init.BurstAccessMode    = FSMC_BURST_ACCESS_MODE_DISABLE;
  hsram.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram.Init.WrapMode           = FSMC_WRAP_MODE_DISABLE;
  hsram.Init.WaitSignalActive   = FSMC_WAIT_TIMING_BEFORE_WS;
  hsram.Init.WriteOperation     = FSMC_WRITE_OPERATION_ENABLE;
  hsram.Init.WaitSignal         = FSMC_WAIT_SIGNAL_DISABLE;
  hsram.Init.ExtendedMode       = FSMC_EXTENDED_MODE_DISABLE;
  hsram.Init.AsynchronousWait   = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram.Init.WriteBurst         = FSMC_WRITE_BURST_DISABLE;
  hsram.Init.PageSize           = FSMC_PAGE_SIZE_128;

  /* Initialize the SRAM controller */
  FSMC_BANK4_MspInit();
  HAL_SRAM_Init(&hsram, &sramtiming, &sramtiming);   
}

/**
  * @brief  Writes register value.
  * @param  Data: 
  * @retval None
  */
static void FSMC_BANK4_WriteData(uint16_t Data) 
{
  /* Write 16-bit Data */
  TFT_LCD->LCD_RAM_W = Data;
}

/**
  * @brief  Writes register address.
  * @param  Reg: 
  * @retval None
  */
static void FSMC_BANK4_WriteReg(uint8_t Reg) 
{
  /* Write 16-bit Index, then Write Reg */
  TFT_LCD->LCD_REG_W = Reg;
}

/**
  * @brief  Reads register value.
  * @retval Read value
  */
static uint16_t FSMC_BANK4_ReadData(void) 
{
  /* Read 16-bit Reg */
  return (TFT_LCD->LCD_RAM_R);
}
#endif /*HAL_SRAM_MODULE_ENABLED*/

#ifdef HAL_I2C_MODULE_ENABLED
/******************************* I2C Routines**********************************/

/**
  * @brief Eval I2Cx MSP Initialization
  * @param hi2c: I2C handle
  * @retval None
  */
static void I2Cx_MspInit(I2C_HandleTypeDef *hi2c)
{
  GPIO_InitTypeDef  gpioinitstruct = {0};  

  if (hi2c->Instance == EVAL_I2Cx)
  {
    /*## Configure the GPIOs ################################################*/  

    /* Enable GPIO clock */
    EVAL_I2Cx_SDA_GPIO_CLK_ENABLE();
    EVAL_I2Cx_SCL_GPIO_CLK_ENABLE();
      
    /* Configure I2C Tx as alternate function  */
    gpioinitstruct.Pin       = EVAL_I2Cx_SCL_PIN;
    gpioinitstruct.Mode      = GPIO_MODE_AF_OD;
    gpioinitstruct.Pull      = GPIO_NOPULL;
    gpioinitstruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
    gpioinitstruct.Alternate = EVAL_I2Cx_SCL_SDA_AF;
    HAL_GPIO_Init(EVAL_I2Cx_SCL_GPIO_PORT, &gpioinitstruct);
      
    /* Configure I2C Rx as alternate function  */
    gpioinitstruct.Pin = EVAL_I2Cx_SDA_PIN;
    HAL_GPIO_Init(EVAL_I2Cx_SDA_GPIO_PORT, &gpioinitstruct);
    
    
    /*## Configure the Eval I2Cx peripheral #######################################*/ 
    /* Enable Eval_I2Cx clock */
    EVAL_I2Cx_CLK_ENABLE();
    
    /* Force the I2C Periheral Clock Reset */  
    EVAL_I2Cx_FORCE_RESET();
      
    /* Release the I2C Periheral Clock Reset */  
    EVAL_I2Cx_RELEASE_RESET(); 
    
    /* Enable and set Eval I2Cx Interrupt to the highest priority */
    HAL_NVIC_SetPriority(EVAL_I2Cx_EV_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(EVAL_I2Cx_EV_IRQn);
    
    /* Enable and set Eval I2Cx Interrupt to the highest priority */
    HAL_NVIC_SetPriority(EVAL_I2Cx_ER_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(EVAL_I2Cx_ER_IRQn);  
  }
}

/**
  * @brief Eval I2Cx Bus initialization
  * @retval None
  */
static void I2Cx_Init(void)
{
  if(HAL_I2C_GetState(&heval_I2c) == HAL_I2C_STATE_RESET)
  {
    heval_I2c.Instance              = EVAL_I2Cx;
    heval_I2c.Init.ClockSpeed       = EVAL_I2C_SPEED;
    heval_I2c.Init.DutyCycle        = I2C_DUTYCYCLE_2;
    heval_I2c.Init.OwnAddress1      = 0;
    heval_I2c.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
    heval_I2c.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
    heval_I2c.Init.OwnAddress2      = 0;
    heval_I2c.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
    heval_I2c.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;  

    /* Init the I2C */
    I2Cx_MspInit(&heval_I2c);
    HAL_I2C_Init(&heval_I2c);
  }
}

/**
  * @brief  Write a value in a register of the device through BUS.
  * @param  Addr: Device address on BUS Bus.  
  * @param  Reg: The target register address to write
  * @param  Value: The target register value to be written 
  * @retval  None
  */
static void I2Cx_WriteData(uint16_t Addr, uint8_t Reg, uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_I2C_Mem_Write(&heval_I2c, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, I2cxTimeout);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    I2Cx_Error();
  }
}

/**
  * @brief  Write a value in a register of the device through BUS.
  * @param  Addr: Device address on BUS Bus.  
  * @param  Reg: The target register address to write
  * @param  RegSize: The target register size (can be 8BIT or 16BIT)
  * @param  pBuffer: The target register value to be written 
  * @param  Length: buffer size to be written
  * @retval None
  */
static HAL_StatusTypeDef I2Cx_WriteBuffer(uint16_t Addr, uint8_t Reg, uint16_t RegSize, uint8_t *pBuffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  status = HAL_I2C_Mem_Write(&heval_I2c, Addr, (uint16_t)Reg, RegSize, pBuffer, Length, I2cxTimeout); 

/* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initiaize the BUS */
    I2Cx_Error();
  }        
  return status;
}

/**
  * @brief  Read a value in a register of the device through BUS.
  * @param  Addr: Device address on BUS Bus.  
  * @param  Reg: The target register address to write
  * @retval Data read at register @
  */
static uint8_t I2Cx_ReadData(uint16_t Addr, uint8_t Reg)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t value = 0;
  
  status = HAL_I2C_Mem_Read(&heval_I2c, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &value, 1, I2cxTimeout);
 
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    I2Cx_Error();
  
  }
  return value;
}

/**
  * @brief  Reads multiple data on the BUS.
  * @param  Addr: I2C Address
  * @param  Reg: Reg Address 
  * @param  RegSize : The target register size (can be 8BIT or 16BIT)
  * @param  pBuffer: pointer to read data buffer
  * @param  Length: length of the data
  * @retval 0 if no problems to read multiple data
  */
static HAL_StatusTypeDef I2Cx_ReadBuffer(uint16_t Addr, uint8_t Reg, uint16_t RegSize, uint8_t *pBuffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Read(&heval_I2c, Addr, (uint16_t)Reg, RegSize, pBuffer, Length, I2cxTimeout);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initiaize the BUS */
    I2Cx_Error();
  }        
  return status;
}

/**
* @brief  Checks if target device is ready for communication. 
* @note   This function is used with Memory devices
* @param  DevAddress: Target device address
* @param  Trials: Number of trials
* @retval HAL status
*/
static HAL_StatusTypeDef I2Cx_IsDeviceReady(uint16_t DevAddress, uint32_t Trials)
{ 
  return (HAL_I2C_IsDeviceReady(&heval_I2c, DevAddress, Trials, I2cxTimeout));
}


/**
  * @brief Eval I2Cx error treatment function
  * @retval None
  */
static void I2Cx_Error (void)
{
  /* De-initialize the I2C communication BUS */
  HAL_I2C_DeInit(&heval_I2c);
  
  /* Re- Initiaize the I2C communication BUS */
  I2Cx_Init();
}

#endif /* HAL_I2C_MODULE_ENABLED */

/******************************* SPI Routines**********************************/
#ifdef HAL_SPI_MODULE_ENABLED
/**
  * @brief  Initializes SPI MSP.
  * @retval None
  */
static void SPIx_MspInit(SPI_HandleTypeDef *hspi)
{
  GPIO_InitTypeDef  gpioinitstruct = {0};
  
  /*** Configure the GPIOs ***/  
  /* Enable GPIO clock */
  EVAL_SPIx_SCK_GPIO_CLK_ENABLE();
  EVAL_SPIx_MISO_MOSI_GPIO_CLK_ENABLE();
  
  /* configure SPI SCK */
  gpioinitstruct.Pin        = EVAL_SPIx_SCK_PIN;
  gpioinitstruct.Mode       = GPIO_MODE_AF_PP;
  gpioinitstruct.Pull       = GPIO_NOPULL;
  gpioinitstruct.Speed      = GPIO_SPEED_FREQ_VERY_HIGH;
  gpioinitstruct.Alternate  = EVAL_SPIx_SCK_AF;
  HAL_GPIO_Init(EVAL_SPIx_SCK_GPIO_PORT, &gpioinitstruct);

  /* configure SPI MISO and MOSI */
  gpioinitstruct.Pin        = (EVAL_SPIx_MISO_PIN | EVAL_SPIx_MOSI_PIN);
  gpioinitstruct.Mode       = GPIO_MODE_AF_PP;
  gpioinitstruct.Pull       = GPIO_NOPULL;
  gpioinitstruct.Speed      = GPIO_SPEED_FREQ_VERY_HIGH;
  gpioinitstruct.Alternate  = EVAL_SPIx_MISO_MOSI_AF;
  HAL_GPIO_Init(EVAL_SPIx_MISO_MOSI_GPIO_PORT, &gpioinitstruct);

  /*** Configure the SPI peripheral ***/ 
  /* Enable SPI clock */
  EVAL_SPIx_CLK_ENABLE();
}

/**
  * @brief  Initializes SPI HAL.
  * @retval None
  */
static void SPIx_Init(void)
{
  /* DeInitializes the SPI peripheral */
  heval_Spi.Instance = EVAL_SPIx;
  HAL_SPI_DeInit(&heval_Spi);

  /* SPI Config */
  /* SPI baudrate is set to 32 MHz (PCLK2/SPI_BaudRatePrescaler = 32/2 = 16 MHz) */
  heval_Spi.Init.BaudRatePrescaler  = SPI_BAUDRATEPRESCALER_2;
  heval_Spi.Init.Direction          = SPI_DIRECTION_2LINES;
  heval_Spi.Init.CLKPhase           = SPI_PHASE_1EDGE;
  heval_Spi.Init.CLKPolarity        = SPI_POLARITY_LOW;
  heval_Spi.Init.CRCCalculation     = SPI_CRCCALCULATION_DISABLE;
  heval_Spi.Init.CRCPolynomial      = 7;
  heval_Spi.Init.DataSize           = SPI_DATASIZE_8BIT;
  heval_Spi.Init.FirstBit           = SPI_FIRSTBIT_MSB;
  heval_Spi.Init.NSS                = SPI_NSS_SOFT;
  heval_Spi.Init.TIMode             = SPI_TIMODE_DISABLE;
  heval_Spi.Init.Mode               = SPI_MODE_MASTER;
  
  SPIx_MspInit(&heval_Spi);
  if (HAL_SPI_Init(&heval_Spi) != HAL_OK)
  {
    /* Should not occur */
    while(1) {};
  }
}

/**
  * @brief SPI Read 4 bytes from device
  * @retval Read data
*/
static uint32_t SPIx_Read(void)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint32_t          readvalue = 0;
  uint32_t          writevalue = 0xFFFFFFFF;
  
  status = HAL_SPI_TransmitReceive(&heval_Spi, (uint8_t*) &writevalue, (uint8_t*) &readvalue, 1, SpixTimeout);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    SPIx_Error();
  }

  return readvalue;
}

/**
  * @brief SPI Write a byte to device
  * @param Value: value to be written
  * @retval None
  */
static void SPIx_Write(uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_SPI_Transmit(&heval_Spi, (uint8_t*) &Value, 1, SpixTimeout);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    SPIx_Error();
  }
}

/**
  * @brief SPI error treatment function
  * @retval None
  */
static void SPIx_Error (void)
{
  /* De-initialize the SPI communication BUS */
  HAL_SPI_DeInit(&heval_Spi);
  
  /* Re- Initiaize the SPI communication BUS */
  SPIx_Init();
}
#endif /* HAL_SPI_MODULE_ENABLED */

/**
  * @}
  */ 

/** @defgroup STM32L152D_EVAL_LinkOperations_Functions Link Operations Functions
  * @{
  */ 

/*******************************************************************************
                            LINK OPERATIONS
*******************************************************************************/

#if defined(HAL_SRAM_MODULE_ENABLED)
/********************************* LINK LCD ***********************************/

/**
  * @brief  Initializes LCD low level.
  * @retval None
  */
void LCD_IO_Init(void) 
{
  FSMC_BANK4_Init();
}

/**
  * @brief  Writes data on LCD data register.
  * @param  RegValue: Data to be written
  * @retval None
  */
void  LCD_IO_WriteData(uint16_t RegValue)
{
    FSMC_BANK4_WriteData(RegValue);
}

/**
  * @brief  Writes multiple data on LCD data register.
  * @param  pData: Data to be written
  * @param  Size: number of data to write
  * @retval None
  */
void LCD_IO_WriteMultipleData(uint8_t *pData, uint32_t Size)
{
  uint32_t index = 0;
  uint16_t data = 0;
  
  for(index = 0; index < (Size / 2); index++)
  {
    data = *pData;
    pData++;
    data |= (*pData++ << 8);
    FSMC_BANK4_WriteData(data);
  }
}

/**
  * @brief  Writes register on LCD register.
  * @param  Reg: Register to be written
  * @retval None
  */
void LCD_IO_WriteReg(uint8_t Reg) 
{
  FSMC_BANK4_WriteReg(Reg);
}

/**
  * @brief  Reads data from LCD data register.
  * @param  Reg: Register to be read
  * @retval Read data.
  */
uint16_t LCD_IO_ReadData(uint16_t Reg)
{
  FSMC_BANK4_WriteReg(Reg);
  
  /* Read 16-bit Reg */
  return (FSMC_BANK4_ReadData());
}

/**
  * @brief  Wait for loop in ms.
  * @param  Delay in ms.
  * @retval None
  */
void LCD_Delay (uint32_t Delay)
{
  HAL_Delay(Delay);
}

#endif /*HAL_SRAM_MODULE_ENABLED*/

#ifdef HAL_SPI_MODULE_ENABLED
/******************************** LINK EEPROM SPI ********************************/

/**
  * @brief  Initializes the EEPROM SPI and put it into StandBy State (Ready for 
  *         data transfer).
  * @retval None
  */
void EEPROM_SPI_IO_Init(void)
{
  GPIO_InitTypeDef  gpioinitstruct = {0};

  /* EEPROM_CS_GPIO Periph clock enable */
  EEPROM_CS_GPIO_CLK_ENABLE();

  /* Configure EEPROM_CS_PIN pin: EEPROM SPI CS pin */
  gpioinitstruct.Pin    = EEPROM_CS_PIN;
  gpioinitstruct.Mode   = GPIO_MODE_OUTPUT_PP;
  gpioinitstruct.Pull   = GPIO_PULLUP;
  gpioinitstruct.Speed  = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(EEPROM_CS_GPIO_PORT, &gpioinitstruct);

  /*------------Put EEPROM in SPI mode--------------*/
  /* EEPROM SPI Config */
  SPIx_Init();
  
  /* EEPROM chip select high */
  EEPROM_CS_HIGH();
}

/**
  * @brief  Write a byte on the EEPROM.
  * @param  Data: byte to send.
  * @retval None
  */
void EEPROM_SPI_IO_WriteByte(uint8_t Data)
{
  /* Send the byte */
  SPIx_Write(Data);
}

/**
  * @brief  Read a byte from the EEPROM.
  * @retval uint8_t (The received byte).
  */
uint8_t EEPROM_SPI_IO_ReadByte(void)
{
  uint8_t data = 0;
  
  /* Get the received data */
  data = SPIx_Read();

  /* Return the shifted data */
  return data;
}

/**
  * @brief  Write data to SPI EEPROM driver
  * @param  MemAddress: Internal memory address
  * @param  pBuffer: Pointer to data buffer
  * @param  BufferSize: Amount of data to be read
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef EEPROM_SPI_IO_WriteData(uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize)
{
  /*!< Enable the write access to the EEPROM */
  /*!< Select the EEPROM: Chip Select low */
  EEPROM_CS_LOW();

  /*!< Send "Write Enable" instruction */
  SPIx_Write(EEPROM_CMD_WREN);

  /*!< Deselect the EEPROM: Chip Select high */
  EEPROM_CS_HIGH();
  
  /*!< Select the EEPROM: Chip Select low */
  EEPROM_CS_LOW();

  /*!< Send "Write to Memory" instruction and MSB of MemAddress   */
  SPIx_Write(EEPROM_CMD_WRITE | (uint8_t)((MemAddress & 0x0100)>>5));
  
  /*!< Send MemAddress address byte to write to */
  SPIx_Write(MemAddress & 0xFF);
  
  /*!< while there is data to be written on the EEPROM */
  while ((BufferSize)--)
  {
    /*!< Send the current byte */
    SPIx_Write(*pBuffer);
    /*!< Point on the next byte to be written */
    pBuffer++;
  }
  
  /*!< Deselect the EEPROM: Chip Select high */
  EEPROM_CS_HIGH();
  
  /*!< Wait the end of EEPROM writing */
  EEPROM_SPI_IO_WaitEepromStandbyState();
  
  /*!< Disable the write access to the EEROM */
  EEPROM_CS_LOW();

  /*!< Send "Write Disable" instruction */
  SPIx_Write(EEPROM_CMD_WRDI);

  /*!< Deselect the EEPROM: Chip Select high */
  EEPROM_CS_HIGH();

  return HAL_OK;
}

/**
  * @brief  Read data from SPI EEPROM driver
  * @param  MemAddress: Internal memory address
  * @param  pBuffer: Pointer to data buffer
  * @param  BufferSize: Amount of data to be read
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef EEPROM_SPI_IO_ReadData(uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize)
{
  /*!< Select the EEPROM: Chip Select low */
  EEPROM_CS_LOW();
 
  /*!< Send "Read from Memory" instruction and MSB of MemAddress */
  SPIx_Write(EEPROM_CMD_READ | (uint8_t)((MemAddress & 0x100)>>5));
  
  /*!< Send MemAddress address byte to read to*/
  SPIx_Write(MemAddress & 0xFF);
  
  while ((BufferSize)--) /*!< while there is data to be read */
  {
    /*!< Read a byte from the EEPROM */
    *pBuffer = SPIx_Read();
    /*!< Point to the next location where the byte read will be saved */
    pBuffer++;
  }
  
  /*!< Deselect the EEPROM: Chip Select high */
  EEPROM_CS_HIGH();

  return HAL_OK;
}

/**
  * @brief  Wait response from the SPI EEPROM
  * @retval HAL_StatusTypeDef HAL Status
  */
HAL_StatusTypeDef EEPROM_SPI_IO_WaitEepromStandbyState(void)
{
  uint32_t timeout = 0xFFFF;
  uint32_t eepromstatus = 0;
  
  /*!< Select the EEPROM: Chip Select low */
  EEPROM_CS_LOW();
  
  /*!< Send "Read Status Register" instruction */
  SPIx_Write(EEPROM_CMD_RDSR);

  /*!< Loop as long as the memory is busy with a write cycle */
  do
  {
    /*!< Send a dummy byte to generate the clock needed by the EEPROM
    and put the value of the status register in EEPROM Status variable */
    eepromstatus = SPIx_Read();
    timeout --;
  }
  while (((eepromstatus & EEPROM_WIP_FLAG) == SET) && timeout); /* Write in progress */

  /*!< Deselect the EEPROM: Chip Select high */
  EEPROM_CS_HIGH();

  if ((eepromstatus & EEPROM_WIP_FLAG) != SET)
  {
    /* Right response got */
    return HAL_OK;
  }
  else
  {
    /* After time out */
    return HAL_TIMEOUT;
  }
}
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_I2C_MODULE_ENABLED
/********************************* LINK I2C EEPROM *****************************/
/**
  * @brief  Initializes peripherals used by the I2C EEPROM driver.
  * @retval None
  */
void EEPROM_I2C_IO_Init(void)
{
  I2Cx_Init();
}

/**
  * @brief  Write data to I2C EEPROM driver
  * @param  DevAddress: Target device address
  * @param  MemAddress: Internal memory address
  * @param  pBuffer: Pointer to data buffer
  * @param  BufferSize: Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef EEPROM_I2C_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize)
{
  return (I2Cx_WriteBuffer(DevAddress, MemAddress, I2C_MEMADD_SIZE_16BIT, pBuffer, BufferSize));
}

/**
  * @brief  Read data from I2C EEPROM driver
  * @param  DevAddress: Target device address
  * @param  MemAddress: Internal memory address
  * @param  pBuffer: Pointer to data buffer
  * @param  BufferSize: Amount of data to be read
  * @retval HAL status
  */
HAL_StatusTypeDef EEPROM_I2C_IO_ReadData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize)
{
  return (I2Cx_ReadBuffer(DevAddress, MemAddress, I2C_MEMADD_SIZE_16BIT, pBuffer, BufferSize));
}

/**
* @brief  Checks if target device is ready for communication. 
* @note   This function is used with Memory devices
* @param  DevAddress: Target device address
* @param  Trials: Number of trials
* @retval HAL status
*/
HAL_StatusTypeDef EEPROM_I2C_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials)
{ 
  return (I2Cx_IsDeviceReady(DevAddress, Trials));
}

/********************************* LINK I2C TEMPERATURE SENSOR *****************************/
/**
  * @brief  Initializes peripherals used by the I2C Temperature Sensor driver.
  * @retval None
  */
void TSENSOR_IO_Init(void)
{
  I2Cx_Init();
}

/**
  * @brief  Writes one byte to the TSENSOR.
  * @param  DevAddress: Target device address
  * @param  pBuffer: Pointer to data buffer
  * @param  WriteAddr: TSENSOR's internal address to write to.
  * @param  Length: Number of data to write
  * @retval None
  */
void TSENSOR_IO_Write(uint16_t DevAddress, uint8_t* pBuffer, uint8_t WriteAddr, uint16_t Length)
{
  I2Cx_WriteBuffer(DevAddress, WriteAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, Length);
}

/**
  * @brief  Reads one byte from the TSENSOR.
  * @param  DevAddress: Target device address
  * @param  pBuffer : pointer to the buffer that receives the data read from the TSENSOR.
  * @param  ReadAddr : TSENSOR's internal address to read from.
  * @param  Length: Number of data to read
  * @retval None
  */
void TSENSOR_IO_Read(uint16_t DevAddress, uint8_t* pBuffer, uint8_t ReadAddr, uint16_t Length)
{
  I2Cx_ReadBuffer(DevAddress, ReadAddr, I2C_MEMADD_SIZE_8BIT, pBuffer, Length);
}

/**
* @brief  Checks if Temperature Sensor is ready for communication. 
  * @param  DevAddress: Target device address
  * @param  Trials: Number of trials
* @retval HAL status
*/
uint16_t TSENSOR_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials)
{ 
  return (I2Cx_IsDeviceReady(DevAddress, Trials));
}

/********************************* LINK AUDIO ***********************************/

/**
  * @brief  Initializes Audio low level.
  * @retval None
  */
void AUDIO_IO_Init (void) 
{
  GPIO_InitTypeDef  gpioinitstruct = {0};
  
  /* Enable Reset GPIO Clock */
  AUDIO_RESET_GPIO_CLK_ENABLE();

  /* Audio reset pin configuration -------------------------------------------------*/
  gpioinitstruct.Pin   = AUDIO_RESET_PIN; 
  gpioinitstruct.Mode  = GPIO_MODE_OUTPUT_PP;
  gpioinitstruct.Speed = GPIO_SPEED_FREQ_HIGH;
  gpioinitstruct.Pull  = GPIO_NOPULL;
  HAL_GPIO_Init(AUDIO_RESET_GPIO, &gpioinitstruct);    
  
  I2Cx_Init();

  /* Power Down the codec */
  HAL_GPIO_WritePin(AUDIO_RESET_GPIO, AUDIO_RESET_PIN, GPIO_PIN_RESET);

  /* wait for a delay to insure registers erasing */
  HAL_Delay(5); 

  /* Power on the codec */
  HAL_GPIO_WritePin(AUDIO_RESET_GPIO, AUDIO_RESET_PIN, GPIO_PIN_SET);
   
  /* wait for a delay to insure registers erasing */
  HAL_Delay(5); 
}

/**
  * @brief  DeInitializes Audio low level.
  * @note   This function is intentionally kept empty, user should define it.
  */
void AUDIO_IO_DeInit(void)
{

}

/**
  * @brief  Writes a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address 
  * @param  Value: Data to be written
  * @retval None
  */
void AUDIO_IO_Write (uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_WriteData(Addr, Reg, Value);
}

/**
  * @brief  Reads a single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address 
  * @retval Data to be read
  */
uint8_t AUDIO_IO_Read (uint8_t Addr, uint8_t Reg)
{
  return I2Cx_ReadData(Addr, Reg);
}

#endif /* HAL_I2C_MODULE_ENABLED */

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


