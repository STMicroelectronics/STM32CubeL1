/**
  @page BSP  Example on how to use the BSP drivers
  
  @verbatim
  ******************************************************************************
  * @file    BSP/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the BSP example.
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

This example provides a description of how to use the different BSP drivers. 

At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 32 MHz.

This example shows how to use the different functionalities of components 
available on the board by switching between all tests using key button. 

 ** Push the KEY button to start first Test.  
Blue Led (LD4) will blink between each test. Press key button to start another test.

 ** JOSTICK **
Use the joystick button to move a pointer inside a rectangle 
(up/down/right/left) and change the pointer color(select).

 ** LCD **
This example shows how to use the different LCD features to display string
with different fonts, to display different shapes and to draw a bitmap.

 ** SD **
This example shows how to erase, write and read the SD card and also 
how to detect the presence of the card.

 ** EEPROM **
This example show how to read and write data in EEPROM I2C M24LR64 connected on STM32L152D-EVAL
then EEPROM SPI M95040 mounted on STM32L152D-EVAL:
   * The I2C RF EEPROM memory (M24LR64) is available thru the connector CN12.
   * The SPI EEPROM memory (M95040) is directly mounted on STM32L152D-EVAL
   @note No specific jumpers to communicate with this EEPROM M95040

 ** TSENSOR **
This example show how to read a Temperature using the temperature sensor.

 ** AUDIO PLAY **
This example show how to play/pause/resume or change the volume (min 50% / max 100 %)
of an audio playback using Key or Joystick button.

      Connect a headphone to the audio jack connector (CN13), to hear the sound  /!\ Take care of yours ears.
      Default volume is 60%.
      A press of JOY_SEL button will pause the audio file play (LED 1 green keep previous state
       and LED2 orange ON).
      Another press on JOY_SEL button will resumes audio file play (only LED 1 green blink at each replay)
      @Note: Copy file 'audio.bin' (available in Utilities\Media folder) directly in the flash 
      at @0x08017000 using ST-Link utility
      A press of JOY_UP button will increment the volume of the audio playback.
      A press of JOY_DOWN button will decrement the volume of the audio playback.

 ** AUDIO RECORD **
This example will use microphone available on the board. Automatically, sound 
will be recorded and played on the headset.
LED3 will be ON during record (LED1 means that play is ongoing)
   @note Make sure that JP6 & JP8 jumpers are in MIC_INN and MIC_INP positions.

 ** NOR **
This example shows how to erase, write and read data available on the NOR flash 
available on the board.

 ** SRAM **
This example shows how to erase, write and read data available on the external 
SRAM available on the board.

 ** LCD LOG **
This example show how to use the LCD log features. 

@par Directory contents 

  - BSP/Src/main.c                 Main program
  - BSP/Src/system_stm32l1xx.c     STM32L1xx system clock configuration file
  - BSP/Src/stm32l1xx_it.c         Interrupt handlers 
  - BSP/Src/joystick.c             joystick feature
  - BSP/Src/lcd.c                  LCD drawing features
  - BSP/Src/log.c                  LCD Log firmware functions
  - BSP/Src/sd.c                   SD features
  - BSP/Src/eeprom.c               EEPROM Read/Write features
  - BSP/Src/temperature_sensor.c   Temperature Sensor features
  - BSP/Src/audio_play.c           Audio Playback features
  - BSP/Src/audio_record.c         Audio Record features
  - BSP/Src/nor.c                  NOR features
  - BSP/Src/sram.c                 SRAM features
  - BSP/Inc/main.h                 Main program header file  
  - BSP/Inc/stm32l1xx_hal_conf.h   HAL Configuration file
  - BSP/Inc/stm32l1xx_it.h         Interrupt handlers header file
  - BSP/Inc/lcd_log_conf.h         lcd_log configuration template file
  - BSP/Inc/stlogo.h               Image used for BSP example
        
@par Hardware and Software environment  

  - This example runs on STM32L152xD devices.
    
  - This example has been tested with STMicroelectronics STM32L152D-EVAL
    evaluation boards and can be easily tailored to any other supported device 
    and development board.
    @note Make sure that LCD Glass is in IO Position
  
@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 */
