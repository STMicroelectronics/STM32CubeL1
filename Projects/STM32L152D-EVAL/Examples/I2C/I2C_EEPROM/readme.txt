/**
  @page I2C_EEPROM I2C EEPROM DMA example
  
  @verbatim
  ******************************************************************************
  * @file    I2C/I2C_EEPROM/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the I2C EEPROM DMA example.
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
  @endverbatim

@par Example Description 

How to handle I2C data buffer transmission/reception with DMA. In the example, 
the device communicates with an I2C EEPROM memory.

SCL Pin: PB.08
SDA Pin: PB.09

   __________________________________________________________________________                        
  |           ______________                        ______________           |
  |          | I2C1         |                      |    I2C_EEPROM|          |
  |          |              |                      |              |          |
  |          |           SCL|______________________|CLOCK         |          |
  |          |              |                      |              |          |
  |          |              |                      |              |          |
  |          |              |                      |              |          |
  |          |           SDA|______________________|DATA          |          |
  |          |              |                      |              |          |
  |          |______________|                      |______________|          |
  |      __                                                                  |
  |     |__|                                                                 |
  |    TAMPER                                                                |
  |                                                                          |
  |__________________________________________________________________________|
      STM32L152D-EVAL

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 32 MHz.

The I2C peripheral configuration is ensured by the HAL_I2C_Init() function.
This later is calling the HAL_I2C_MspInit()function which core is implementing
the configuration of the needed I2C resources according to the used hardware (CLOCK, 
GPIO, DMA and NVIC). You may update this function to change I2C configuration.

The I2C/EEPROM communication is then initiated.
The HAL_I2C_Mem_Read_DMA() and the HAL_I2C_Mem_Write_DMA() functions allow respectively 
the reception of Data from EEPROM and the transmission of a predefined data 
buffer.

For this example the TxBuffer is predefined and the aRxBuffer size is same as aTxBuffer.

In a first step the I2C writes the aTxBuffer by group of 4 bytes (RF EEPROM 
Page size) using HAL_I2C_Mem_Write_DMA() then read back the data through aRxBuffer
using HAL_I2C_Mem_Read_DMA(). 
The end of this two steps are monitored through the HAL_I2C_GetState() function
result.
Finally, aRxBuffer and aRxBuffer are compared through Buffercmp() in order to 
check buffers correctness.  

STM32 Eval board's LEDs can be used to monitor the transfer status:
 - LED1 is ON when the transmission process is complete.
 - LED2 is ON when the reception process is complete.
 - LED3 is ON when there is an error in transmission/reception process.  

 @note I2Cx instance used and associated resources can be updated in "main.h"
       file depending hardware configuration used.


@par Directory contents 

  - I2C/I2C_EEPROM/Inc/stm32l1xx_hal_conf.h    HAL configuration file
  - I2C/I2C_EEPROM/Inc/stm32l1xx_it.h          Interrupt handlers header file
  - I2C/I2C_EEPROM/Inc/main.h                  Header for main.c module  
  - I2C/I2C_EEPROM/Src/stm32l1xx_it.c          Interrupt handlers
  - I2C/I2C_EEPROM/Src/main.c                  Main program
  - I2C/I2C_EEPROM/Src/system_stm32l1xx.c      STM32L1xx system source file
  - I2C/I2C_EEPROM/Src/stm32l1xx_hal_msp.c     HAL MSP file    


@par Hardware and Software environment

  - This example runs on STM32L152xD devices.
    
  - This example has been tested with STM32L152D-EVAL board and can be
    easily tailored to any other supported device and development board.      

  - STM32L152D-EVAL Set-up 
    - When communicating with M24LR64 EEPROM, make sure that ANT7-M24LR is inserted in CN12 connector.
    @Note: make sure that LCD glass module has to be mounted on IO position

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files: Project->Rebuild all
 - Load project image: Project->Download and Debug
 - Run program: Debug->Go(F5) 



 */
