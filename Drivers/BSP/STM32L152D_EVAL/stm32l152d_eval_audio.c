/**
  ******************************************************************************
  * @file    stm32l152d_eval_audio.c
  * @author  MCD Application Team
  * @brief   This file provides the Audio driver for the STM32L152D-Eval 
  *          board.  
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================  
   [..] 
  (#) This driver supports STM32L152xD devices on STM32L152D-Eval Kit:
       (++) to play an audio file (all functions names start by BSP_AUDIO_OUT_xxx)
       (++) to record an audio file through MP45DT02, ST MEMS (all functions names 
            start by AUDIO_IN_xxx)

  [..] 
   (#) PLAY A FILE:
       (++) Call the function BSP_AUDIO_OUT_Init(
              OutputDevice: physical output mode (OUTPUT_DEVICE_SPEAKER, 
                           OUTPUT_DEVICE_HEADPHONE, OUTPUT_DEVICE_AUTO or 
                           OUTPUT_DEVICE_BOTH)
              Volume: initial volume to be set (0 is min (mute), 100 is max (100%)
              AudioFreq: Audio frequency in Hz (8000, 16000, 22500, 32000 ...)
              this parameter is relative to the audio file/stream type.
               )
           This function configures all the hardware required for the audio application 
           (codec, I2C, I2S, GPIOs, DMA and interrupt if needed). This function returns 0
           if configuration is OK.
           If the returned value is different from 0 or the function is stuck then the 
           communication with the codec (try to un-plug the power or reset device in this case).
              (+++) OUTPUT_DEVICE_SPEAKER: only speaker will be set as output for the 
                    audio stream.
              (+++) OUTPUT_DEVICE_HEADPHONE: only headphones will be set as output for 
                    the audio stream.
              (+++) OUTPUT_DEVICE_AUTO: Selection of output device is made through external 
                    switch (implemented into the audio jack on the evaluation board). 
                    When the Headphone is connected it is used as output. 
                    When the headphone is disconnected from the audio jack, the output is
                    automatically switched to Speaker.
              (+++) OUTPUT_DEVICE_BOTH: both Speaker and Headphone are used as outputs 
                    for the audio stream at the same time.
       (++) Call the function BSP_AUDIO_OUT_Play(
                pBuffer: pointer to the audio data file address
                Size: size of the buffer to be sent in Bytes
               )
              to start playing (for the first time) from the audio file/stream.
       (++) Call the function BSP_AUDIO_OUT_Pause() to pause playing 
       (++) Call the function BSP_AUDIO_OUT_Resume() to resume playing.
            Note. After calling BSP_AUDIO_OUT_Pause() function for pause, 
            only BSP_AUDIO_OUT_Resume() should be called for resume 
            (it is not allowed to call BSP_AUDIO_OUT_Play() in this case).
            Note. This function should be called only when the audio file is played 
            or paused (not stopped).
       (++) For each mode, you may need to implement the relative callback functions 
            into your code.
            The Callback functions are named BSP_AUDIO_OUT_XXXCallBack() and only 
            their prototypes are declared in the stm32l152d_eval_audio.h file. 
            (refer to the example for more details on the callbacks implementations)
       (++) To Stop playing, to modify the volume level, the frequency or to mute, 
            use the functions BSP_AUDIO_OUT_Stop(), BSP_AUDIO_OUT_SetVolume(), 
            AUDIO_OUT_SetFrequency() BSP_AUDIO_OUT_SetOutputMode and BSP_AUDIO_OUT_SetMute().
       (++) The driver API and the callback functions are at the end of the 
            stm32l152d_eval_audio.h file.
   
       (++) This driver provide the High Audio Layer: consists of the function API 
            exported in the stm32l152d_eval_audio.h file (BSP_AUDIO_OUT_Init(), 
            BSP_AUDIO_OUT_Play() ...)
       (++) This driver provide also the Media Access Layer (MAL): which consists 
            of functions allowing to access the media containing/providing the 
            audio file/stream. These functions are also included as local functions into
            the stm32l152d_eval_audio.c file (I2SOUT_Init()...)

  [..] 
   (#) RECORD A FILE:
       (++) Call the function BSP_AUDIO_IN_Init(
              AudioFreq: Audio frequency in Hz (8000, 16000, 22500, 32000 ...)
              )
            This function configures all the hardware required for the audio application (I2S, 
            GPIOs, DMA and interrupt if needed). This function returns 0 if configuration is OK.

       (++) Call the function BSP_AUDIO_IN_Record(
                pbuf Main buffer pointer for the recorded data storing  
                size Current size of the recorded buffer
                )
            to start recording from the microphone.

       (++) User needs to implement user callbacks to retrieve data saved in the record buffer
           (AUDIO_IN_RxHalfCpltCallback/BSP_AUDIO_IN_ReceiveComplete_CallBack)

       (++) Call the function AUDIO_IN_STOP() to stop recording 
       
  [..] 
                     ##### Known Limitations #####
  ==============================================================================  
   (#) When using the Speaker, if the audio file quality is not high enough, the 
       speaker output may produce high and uncomfortable noise level. To avoid 
       this issue, to use speaker output properly, try to increase audio file 
       sampling rate (typically higher than 48KHz).
       This operation will lead to larger file size.
       
   (#) Communication with the audio codec (through I2C) may be corrupted if it 
       is interrupted by some user interrupt routines (in this case, interrupts 
       could be disabled just before the start of communication then re-enabled 
       when it is over). Note that this communication is only done at the 
       configuration phase (BSP_AUDIO_OUT_Init() or BSP_AUDIO_OUT_Stop()) 
       and when Volume control modification is performed (BSP_AUDIO_OUT_SetVolume() 
       or BSP_AUDIO_OUT_SetMute()or BSP_AUDIO_OUT_SetOutputMode()). 
       When the audio data is played, no communication is required with the audio codec.
       
   (#) Parsing of audio file is not implemented (in order to determine audio file
       properties: Mono/Stereo, Data size, File size, Audio Frequency, Audio Data 
       header size ...). The configuration is fixed for the given audio file.
       
   (#) Mono audio streaming is not supported (in order to play mono audio streams, 
       each data should be sent twice on the I2S or should be duplicated on the 
       source buffer. Or convert the stream in stereo before playing).
       
   (#) Supports only 16-bit audio data size.

  @endverbatim
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
#include "stm32l152d_eval_audio.h"

/** @addtogroup BSP
  * @{
  */
  
/** @addtogroup STM32L152D_EVAL
  * @{
  */

/** @defgroup STM32L152D_EVAL_AUDIO STM32L152D-EVAL Audio
  * @brief This file includes the low layer audio driver available on STM32L152D-Eval
  * eval board.
  * @{
  */ 
  
/** @defgroup STM32L152D_EVAL_AUDIO_Private_Variables Private Variables
  * @{
  */
/*### PLAY ###*/
static AUDIO_DrvTypeDef         *pAudioDrv;
I2S_HandleTypeDef               hAudioOutI2s;

/*### RECORD ###*/
OPAMP_HandleTypeDef             hAudioInOpamp;

/* ADC channel configuration structure declaration */
ADC_HandleTypeDef               hAudioInAdc;
static ADC_ChannelConfTypeDef   hAudioInConfigAdc;

TIM_HandleTypeDef               hAudioInTim3;

__IO uint16_t AudioInVolume = DEFAULT_AUDIO_IN_VOLUME;
    
/**
  * @}
  */ 

/** @defgroup STM32L152D_EVAL_AUDIO_Private_Functions Private Functions
  * @{
  */ 
static void  I2SOUT_MspInit(void);
static void  I2SOUT_Init(uint32_t AudioFreq);

static void  ADCx_MspInit(ADC_HandleTypeDef *hadc);
static void  OPAMPx_MspInit(OPAMP_HandleTypeDef *hadc);
static void  TIMx_Base_MspInit(TIM_HandleTypeDef *hadc);

/**
  * @}
  */ 


/** @defgroup STM32L152D_EVAL_AUDIO_Exported_Functions Exported Functions
  * @{
  */ 

/**
  * @brief  Configure the audio peripherals.
  * @param  OutputDevice: OUTPUT_DEVICE_SPEAKER, OUTPUT_DEVICE_HEADPHONE,
  *                       OUTPUT_DEVICE_BOTH or OUTPUT_DEVICE_AUTO .
  * @param  Volume: Initial volume level (from 0 (Mute) to 100 (Max))
  * @param  AudioFreq: Audio frequency used to play the audio stream.
  * @retval 0 if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_Init(uint16_t OutputDevice, uint8_t Volume, uint32_t AudioFreq)
{    
  uint8_t ret = AUDIO_ERROR;
  uint32_t deviceid = 0x00;

  deviceid = cs43l22_drv.ReadID(AUDIO_I2C_ADDRESS);

  if((deviceid & CS43L22_ID_MASK) == CS43L22_ID)
  {  
    /* Initialize the audio driver structure */
    pAudioDrv = &cs43l22_drv; 
    ret = AUDIO_OK;
  }
  else
  {
    ret = AUDIO_ERROR;
  }
  
  if(ret == AUDIO_OK)
  {
    pAudioDrv->Init(AUDIO_I2C_ADDRESS, OutputDevice, Volume, AudioFreq);
    /* I2S data transfer preparation:
    Prepare the Media to be used for the audio transfer from memory to I2S peripheral */
    /* Configure the I2S peripheral */
    I2SOUT_Init(AudioFreq);
  }
  
  return ret;
}

/**
  * @brief  Starts playing audio stream from a data buffer for a determined size. 
  * @param  pBuffer: Pointer to the buffer 
  * @param  Size: Number of audio data BYTES.
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_Play(uint16_t* pBuffer, uint32_t Size)
{
  /* Call the audio Codec Play function */
  if(pAudioDrv->Play(AUDIO_I2C_ADDRESS, pBuffer, Size) != 0)
  {
    return AUDIO_ERROR;
  }
  else 
  {
    /* Update the Media layer and enable it for play */  
    HAL_I2S_Transmit_DMA(&hAudioOutI2s, pBuffer, DMA_MAX(Size)); 
    
    return AUDIO_OK;
  }
}

/**
  * @brief Sends n-Bytes on the I2S interface.
  * @param pData: pointer on data address 
  * @param Size: number of data to be written
  * @retval None
  */
uint8_t BSP_AUDIO_OUT_ChangeBuffer(uint16_t *pData, uint16_t Size)
{
  return (HAL_I2S_Transmit_DMA(&hAudioOutI2s, pData, Size)); 
}

/**
  * @brief  This function Pauses the audio file stream. In case
  *         of using DMA, the DMA Pause feature is used.
  * @note When calling BSP_AUDIO_OUT_Pause() function for pause, only
  *          BSP_AUDIO_OUT_Resume() function should be called for resume (use of BSP_AUDIO_OUT_Play() 
  *          function for resume could lead to unexpected behavior).
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_Pause(void)
{    
  /* Call the Audio Codec Pause/Resume function */
  if(pAudioDrv->Pause(AUDIO_I2C_ADDRESS) != 0)
  {
    return AUDIO_ERROR;
  }
  else
  {
    /* Call the Media layer pause function */
    HAL_I2S_DMAPause(&hAudioOutI2s);
    
    /* Return AUDIO_OK if all operations are OK */
    return AUDIO_OK;
  }
}

/**
  * @brief  This function  Resumes the audio file stream.  
  * @note When calling BSP_AUDIO_OUT_Pause() function for pause, only
  *          BSP_AUDIO_OUT_Resume() function should be called for resume (use of BSP_AUDIO_OUT_Play() 
  *          function for resume could lead to unexpected behavior).
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_Resume(void)
{    
  /* Call the Audio Codec Pause/Resume function */
  if(pAudioDrv->Resume(AUDIO_I2C_ADDRESS) != 0)
  {
    return AUDIO_ERROR;
  }
  else
  {
    /* Call the Media layer resume function */
    HAL_I2S_DMAResume(&hAudioOutI2s);
    /* Return AUDIO_OK if all operations are OK */
    return AUDIO_OK;
  }
}

/**
  * @brief  Stops audio playing and Power down the Audio Codec. 
  * @param  Option: could be one of the following parameters 
  *           - CODEC_PDWN_HW: completely shut down the codec (physically). 
  *                            Then need to reconfigure the Codec after power on.  
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_Stop(uint32_t Option)
{
  /* Call DMA Stop to disable DMA stream before stopping codec */
  HAL_I2S_DMAStop(&hAudioOutI2s);
  
  /* Call Audio Codec Stop function */
  if(pAudioDrv->Stop(AUDIO_I2C_ADDRESS, Option) != 0)
  {
    return AUDIO_ERROR;
  }
  else
  {
    if(Option == CODEC_PDWN_HW)
    { 
      /* Wait at least 100us */
      HAL_Delay(1);
      
      /* Reset The pin */
      HAL_GPIO_WritePin(AUDIO_RESET_GPIO, AUDIO_RESET_PIN, GPIO_PIN_RESET);
    }
    /* Return AUDIO_OK when all operations are correctly done */
    return AUDIO_OK;
  }
}

/**
  * @brief  Controls the current audio volume level. 
  * @param  Volume: Volume level to be set in percentage from 0% to 100% (0 for 
  *         Mute and 100 for Max volume level).
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_SetVolume(uint8_t Volume)
{
  /* Call the codec volume control function with converted volume value */
  if(pAudioDrv->SetVolume(AUDIO_I2C_ADDRESS, Volume) != 0)
  {
    return AUDIO_ERROR;
  }
  else
  {
    /* Return AUDIO_OK when all operations are correctly done */
    return AUDIO_OK;
  }
}

/**
  * @brief  Enables or disables the MUTE mode by software 
  * @param  Cmd: could be AUDIO_MUTE_ON to mute sound or AUDIO_MUTE_OFF to 
  *         unmute the codec and restore previous volume level.
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_SetMute(uint32_t Cmd)
{ 
  /* Call the Codec Mute function */
  if(pAudioDrv->SetMute(AUDIO_I2C_ADDRESS, Cmd) != 0)
  {
    return AUDIO_ERROR;
  }
  else
  {
    /* Return AUDIO_OK when all operations are correctly done */
    return AUDIO_OK;
  }
}

/**
  * @brief  Switch dynamically (while audio file is played) the output target 
  *         (speaker or headphone).
  * @note   This function modifies a global variable of the audio codec driver: OutputDev.
  * @param  Output: specifies the audio output target: OUTPUT_DEVICE_SPEAKER,
  *         OUTPUT_DEVICE_HEADPHONE, OUTPUT_DEVICE_BOTH or OUTPUT_DEVICE_AUTO 
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_SetOutputMode(uint8_t Output)
{
  /* Call the Codec output Device function */
  if(pAudioDrv->SetOutputMode(AUDIO_I2C_ADDRESS, Output) != 0)
  {
    return AUDIO_ERROR;
  }
  else
  {
    /* Return AUDIO_OK when all operations are correctly done */
    return AUDIO_OK;
  }
}

/**
  * @brief  Update the audio frequency.
  * @param  AudioFreq: Audio frequency used to play the audio stream.
  * @retval None
  * @note This API should be called after the BSP_AUDIO_OUT_Init() to adjust the
  * audio frequency. 
  */
void BSP_AUDIO_OUT_SetFrequency(uint32_t AudioFreq)
{ 
  /* Update the I2S audio frequency configuration */
  I2SOUT_Init(AudioFreq);
}

/**
  * @brief  Manages the DMA full Transfer complete event.
  * @retval None
  */
__weak void BSP_AUDIO_OUT_TransferComplete_CallBack(void)
{
}

/**
  * @brief  Manages the DMA Half Transfer complete event.
  * @retval None
  */
__weak void BSP_AUDIO_OUT_HalfTransfer_CallBack(void)
{
}

/**
  * @brief  Manages the DMA FIFO error event.
  * @retval None
  */
__weak void BSP_AUDIO_OUT_Error_CallBack(void)
{
}

/**
  * @brief  Initialize wave recording
  * @param  AudioFreq Audio frequency acquisition.
  *         Note: On STM32L1 evaluation board, the microphone acquisition is 
  *               done through an analong amplifier with a band-pass filter 
  *               centered at 32kHz.
  *               Therefore, this parameter value should be set at maximum 
  *               to 32kHz (value "32000").
  * @param  BitRes Audio frequency to be configured for the I2S peripheral.
  *         Note: On STM32L1 evaluation board, this parameter is not used, but
  *               kept as parameter for compatibility with other STM32 BSP 
  *               drivers.
  * @param ChnlNbr Audio frequency to be configured for the I2S peripheral.
  *         Note: On STM32L1 evaluation board, this parameter is not used, but
  *               kept as parameter for compatibility with other STM32 BSP 
  *               drivers.
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_IN_Init(uint32_t AudioFreq, uint32_t BitRes, uint32_t ChnlNbr)
{
  
  /*## Configure the OPAMP ###################################################*/
  
  /* Set OPAMP instance */
  hAudioInOpamp.Instance = OPAMP1;
  
  /* Configure the OPAMP if not already configured (on the first occurrence   */
  /* of this function ().                                                     */
  if(HAL_OPAMP_GetState(&hAudioInOpamp) == HAL_OPAMP_STATE_RESET)
  {
    /* Configuration of OPAMP */
    hAudioInOpamp.Init.Mode               = OPAMP_STANDALONE_MODE;
    hAudioInOpamp.Init.NonInvertingInput  = OPAMP_NONINVERTINGINPUT_IO0;
    hAudioInOpamp.Init.InvertingInput     = OPAMP_INVERTINGINPUT_IO0;
    hAudioInOpamp.Init.PowerMode          = OPAMP_POWERMODE_NORMAL;
    hAudioInOpamp.Init.PowerSupplyRange   = OPAMP_POWERSUPPLY_HIGH;
    hAudioInOpamp.Init.UserTrimming       = OPAMP_TRIMMING_FACTORY;

    /* Init MSP of OPAMPx */
    OPAMPx_MspInit(&hAudioInOpamp);
    
    /* Init OPAMPx */
    if (HAL_OPAMP_Init(&hAudioInOpamp) != HAL_OK)
    {
      return AUDIO_ERROR;
    }
  }
    
  /* Enable OPAMPx */
  if (HAL_OPAMP_Start(&hAudioInOpamp) != HAL_OK)
  {
    return AUDIO_ERROR;
  }  
  
  /*## Configure the ADC #####################################################*/
  
  /* Set ADC instance */
  hAudioInAdc.Instance = ADC1;
  
  /* Deinitialize the ADC peripheral registers to its default reset values */
  HAL_ADC_DeInit(&hAudioInAdc);
  
  /* Configure the ADC */
  /* Configuration of ADCx init structure: ADC parameters and regular group */
  hAudioInAdc.Init.ClockPrescaler        = ADC_CLOCK_ASYNC_DIV1;         /* ADC clock equal to HSI frequency: 16MHz */
  hAudioInAdc.Init.Resolution            = ADC_RESOLUTION_12B;
  hAudioInAdc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
  hAudioInAdc.Init.ScanConvMode          = DISABLE;                      /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
  hAudioInAdc.Init.EOCSelection          = ADC_EOC_SEQ_CONV;
  hAudioInAdc.Init.LowPowerAutoWait      = ADC_AUTOWAIT_DISABLE;
  hAudioInAdc.Init.LowPowerAutoPowerOff  = ADC_AUTOPOWEROFF_DISABLE;
  hAudioInAdc.Init.ChannelsBank          = ADC_CHANNELS_BANK_A;
  hAudioInAdc.Init.ContinuousConvMode    = DISABLE;                      /* Continuous mode disabled to have only 1 conversion at each ADC external event trig */
  hAudioInAdc.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T3_TRGO; /* Trig of conversion start done by external event */
  hAudioInAdc.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_RISING;
  hAudioInAdc.Init.DMAContinuousRequests = ENABLE;
  
  /* Init MSP of ADCx */
  ADCx_MspInit(&hAudioInAdc);

  /* Init ADCx */
  if (HAL_ADC_Init(&hAudioInAdc) != HAL_OK)
  {
    return AUDIO_ERROR;
  }

  /* Configuration of channel on ADCx regular group on rank 1 */
  hAudioInConfigAdc.Channel       = AUDIO_IN_ADC_CHANNEL;
  hAudioInConfigAdc.SamplingTime  = ADC_SAMPLETIME_384CYCLES;  /* With ADC frequency of 16MHz, conversion time will be 24.75us. This is compliant with sampling time of 32kHz (31.25us) or below */
  hAudioInConfigAdc.Rank          = ADC_REGULAR_RANK_1;
  HAL_ADC_ConfigChannel(&hAudioInAdc, &hAudioInConfigAdc);

  
  /*## Configure the Timer ###################################################*/
  
  /* Set TIM3 period to AudioFreq using system clock 32Mhz */
  hAudioInTim3.Instance           = TIM3;
  hAudioInTim3.Init.Period        = (HAL_RCC_GetPCLK1Freq() / (AudioFreq)) -1;
  hAudioInTim3.Init.Prescaler     = 0;
  hAudioInTim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  hAudioInTim3.Init.CounterMode   = TIM_COUNTERMODE_UP;
  
  /* Init MSP of TIMx */
  TIMx_Base_MspInit(&hAudioInTim3);
  
  /* Init TIMx time base */
  HAL_TIM_Base_Init(&hAudioInTim3);
  
  /* Return 0 if all operations are OK */
  return AUDIO_OK;
}

/**
  * @brief  Start audio recording
  * @param  pbuf Main buffer pointer for the recorded data storing  
  * @param  size Current size of the recorded buffer
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_IN_Record(uint16_t* pbuf, uint32_t size)
{
  uint32_t                ret = AUDIO_OK;
  TIM_MasterConfigTypeDef master_config = {0};

  if (HAL_ADC_Start_DMA(&hAudioInAdc, (uint32_t*)pbuf, size) == HAL_OK)
  {
    master_config.MasterOutputTrigger = TIM_TRGO_UPDATE;
    master_config.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    
    HAL_TIMEx_MasterConfigSynchronization(&hAudioInTim3, &master_config);
    
    /* Start the time base triggering the ADC */
    if (HAL_TIM_Base_Start(&hAudioInTim3) != HAL_OK)
    {
      ret = AUDIO_ERROR;
    }
  }
  else
  {
    ret = AUDIO_ERROR;
  }
  
  return ret;
}

/**
  * @brief  Stop audio recording
  * @retval None
  */
uint8_t BSP_AUDIO_IN_Stop(void)
{
  uint32_t ret = AUDIO_OK;
  
  /* Stop the time base triggering the ADC */
  if (HAL_TIM_Base_Stop(&hAudioInTim3) != HAL_OK)
  {
    ret = AUDIO_ERROR;
  } 
  
  if (HAL_ADC_Stop_DMA(&hAudioInAdc) != HAL_OK)
  {
    /* Return 0 if all operations are OK */
    ret = AUDIO_ERROR;
  }
  
  /* Disable OPAMPx */
  if (HAL_OPAMP_Stop(&hAudioInOpamp) != HAL_OK)
  {
    ret = AUDIO_ERROR;
  }  
  
  return ret;
}

/**
  * @brief  This function Pauses the audio file stream.
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_IN_Pause(void)
{    
  uint32_t ret = AUDIO_OK;
  
  /* Stop the time base triggering the ADC */
  if (HAL_TIM_Base_Stop(&hAudioInTim3) != HAL_OK)
  {
    ret = AUDIO_ERROR;
  } 
  
  /* Return AUDIO_OK if all operations are OK */
  return ret;
}

/**
  * @brief  This function Resumes the audio file stream.  
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_IN_Resume(void)
{    
  uint32_t ret = AUDIO_OK;
  
  /* Start the time base triggering the ADC */
  if (HAL_TIM_Base_Start(&hAudioInTim3) != HAL_OK)
  {
    ret = AUDIO_ERROR;
  } 
  
  /* Return AUDIO_OK if all operations are OK */
  return ret;
}

/**
  * @brief Controls the audio in volume level. 
  * @param Volume: Volume level to be set in percentage from 0% to 100% (0 for 
  *         Mute and 100 for Max volume level).
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_IN_SetVolume(uint8_t Volume)
{
  /* Set the Global variable AudioInVolume  */
  AudioInVolume = Volume; 
  /* Return AUDIO_OK when all operations are correctly done */
  return AUDIO_OK;
}

/**
  * @brief User callback when record buffer is filled
  * @retval None
  */
__weak void BSP_AUDIO_IN_TransferComplete_CallBack(void)
{
  /* This function should be implemented by the user application.
  It is called into this driver when the current buffer is filled
  to prepare the next buffer pointer and its size. */
}

/**
  * @brief  Manages the DMA Half Transfer complete event.
  * @retval None
  */
__weak void BSP_AUDIO_IN_HalfTransfer_CallBack(void)
{
  /* This function should be implemented by the user application.
     It is called into this driver when the current buffer is filled
     to prepare the next buffer pointer and its size. */
}

/**
  * @brief  Audio IN Error callback function
  * @retval None
  */
__weak void BSP_AUDIO_IN_Error_Callback(void)
{   
  /* This function is called when an Interrupt due to transfer error on or peripheral
       error occurs. */
}

/**
  * @}
  */ 

/** @addtogroup STM32L152D_EVAL_AUDIO_Private_Functions
  * @{
  */ 

/******************************************************************************
                            Static Function
*******************************************************************************/

/**
  * @brief AUDIO OUT I2S MSP Init
  * @retval None
  */
static void I2SOUT_MspInit(void)
{
  static DMA_HandleTypeDef  hdma_i2stx;
  GPIO_InitTypeDef          gpioinitstruct = {0};
  I2S_HandleTypeDef         *hi2s = &hAudioOutI2s;

  /* Enable I2SOUT clock */
  I2SOUT_CLK_ENABLE();

  /*** Configure the GPIOs ***/  
  /* Enable I2S GPIO clocks */
  I2SOUT_SCK_SD_CLK_ENABLE();
  I2SOUT_WS_CLK_ENABLE();

  /* I2SOUT pins configuration: WS, SCK and SD pins -----------------------------*/
  gpioinitstruct.Pin         = I2SOUT_SCK_PIN | I2SOUT_SD_PIN; 
  gpioinitstruct.Mode        = GPIO_MODE_AF_PP;
  gpioinitstruct.Pull        = GPIO_NOPULL;
  gpioinitstruct.Speed       = GPIO_SPEED_FREQ_HIGH;
  gpioinitstruct.Alternate   = I2SOUT_SCK_SD_WS_AF;
  HAL_GPIO_Init(I2SOUT_SCK_SD_GPIO_PORT, &gpioinitstruct);
  
  gpioinitstruct.Pin         = I2SOUT_WS_PIN ;
  HAL_GPIO_Init(I2SOUT_WS_GPIO_PORT, &gpioinitstruct); 

  /* I2SOUT pins configuration: MCK pin */
  I2SOUT_MCK_CLK_ENABLE();
  gpioinitstruct.Pin         = I2SOUT_MCK_PIN; 
  HAL_GPIO_Init(I2SOUT_MCK_GPIO_PORT, &gpioinitstruct);   

  /* Enable the I2S DMA clock */
  I2SOUT_DMAx_CLK_ENABLE(); 
  
  if(hi2s->Instance == I2SOUT)
  {
    /* Configure the hdma_i2stx handle parameters */   
    hdma_i2stx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    hdma_i2stx.Init.PeriphInc           = DMA_PINC_DISABLE;
    hdma_i2stx.Init.MemInc              = DMA_MINC_ENABLE;
    hdma_i2stx.Init.PeriphDataAlignment = I2SOUT_DMAx_PERIPH_DATA_SIZE;
    hdma_i2stx.Init.MemDataAlignment    = I2SOUT_DMAx_MEM_DATA_SIZE;
    hdma_i2stx.Init.Mode                = DMA_NORMAL;
    hdma_i2stx.Init.Priority            = DMA_PRIORITY_HIGH;

    hdma_i2stx.Instance                 = I2SOUT_DMAx_CHANNEL;

    /* Associate the DMA handle */
    __HAL_LINKDMA(hi2s, hdmatx, hdma_i2stx);
    
    /* Deinitialize the Channel for new transfer */
    HAL_DMA_DeInit(&hdma_i2stx);
    
    /* Configure the DMA Channel */
    HAL_DMA_Init(&hdma_i2stx);
  }
  
  /* I2S DMA IRQ Channel configuration */
  HAL_NVIC_SetPriority(I2SOUT_DMAx_IRQ, AUDIO_OUT_IRQ_PREPRIO, 0);
  HAL_NVIC_EnableIRQ(I2SOUT_DMAx_IRQ); 
}

/**
  * @brief  Initializes the Audio Codec audio interface (I2S)
  * @param  AudioFreq: Audio frequency to be configured for the I2S peripheral. 
  */
static void I2SOUT_Init(uint32_t AudioFreq)
{
  /* Initialize the hAudioOutI2s Instance parameter */
  hAudioOutI2s.Instance         = I2SOUT;

 /* Disable I2S block */
  __HAL_I2S_DISABLE(&hAudioOutI2s);
  
  /* I2SOUT peripheral configuration */
  hAudioOutI2s.Init.AudioFreq   = AudioFreq;
  hAudioOutI2s.Init.CPOL        = I2S_CPOL_LOW;
  hAudioOutI2s.Init.DataFormat  = I2S_DATAFORMAT_16B;
  hAudioOutI2s.Init.MCLKOutput  = I2S_MCLKOUTPUT_ENABLE;
  hAudioOutI2s.Init.Mode        = I2S_MODE_MASTER_TX;
  hAudioOutI2s.Init.Standard    = I2S_STANDARD;
  /* Initialize the I2S peripheral with the structure above */
  if(HAL_I2S_GetState(&hAudioOutI2s) == HAL_I2S_STATE_RESET)
  { 
    I2SOUT_MspInit();
  }
  
  HAL_I2S_Init(&hAudioOutI2s);
}
  
/**
  * @}
  */ 
  
/** @defgroup STM32L152D_EVAL_AUDIO_Exported_Functions Exported Functions
  * @{
  */ 
  
/**
  * @brief  Initializes ADC MSP.
  * @param  hadc : ADC handle
  * @retval None
  */
static void ADCx_MspInit(ADC_HandleTypeDef *hadc)
{
  static DMA_HandleTypeDef  hdma_adc;
  GPIO_InitTypeDef          gpioinitstruct = {0};
  RCC_OscInitTypeDef        oscinitstruct = {0};
  
  /*** Configure the GPIOs ***/  
  /* Configure pin corresponding to the selected ADC Channel as analog input */
  /* Enable GPIO clock */
  AUDIO_IN_ADC_GPIO_CLK_ENABLE();
  
  gpioinitstruct.Pin   = AUDIO_IN_ADC_PIN;
  gpioinitstruct.Mode  = GPIO_MODE_ANALOG;
  gpioinitstruct.Pull  = GPIO_NOPULL;
  gpioinitstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(AUDIO_IN_ADC_PORT, &gpioinitstruct);
  
  /*** Configure the ADC peripheral ***/
  
  /* Enable asynchronous clock source of ADCx */
  HAL_RCC_GetOscConfig(&oscinitstruct);
  oscinitstruct.OscillatorType      = RCC_OSCILLATORTYPE_HSI;
  oscinitstruct.HSIState            = RCC_HSI_ON;
  oscinitstruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  HAL_RCC_OscConfig(&oscinitstruct);
  
  /* Enable ADC clock */
  __HAL_RCC_ADC1_CLK_ENABLE(); 
  
  /* DMA clock enable */
  AUDIO_IN_DMAx_CLK_ENABLE();
  
  /* Configure DMA handle init parameters */
  hdma_adc.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  hdma_adc.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_adc.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_adc.Init.PeriphDataAlignment = AUDIO_IN_DMAx_PERIPH_DATA_SIZE;
  hdma_adc.Init.MemDataAlignment    = AUDIO_IN_DMAx_MEM_DATA_SIZE;
  hdma_adc.Init.Mode                = DMA_CIRCULAR;
  hdma_adc.Init.Priority            = DMA_PRIORITY_HIGH;
  hdma_adc.Instance                 = AUDIO_IN_DMAx_CHANNEL;
  
  /* Associate the DMA handle */
  __HAL_LINKDMA(hadc, DMA_Handle, hdma_adc);
  
  /* Deinitialize the Channel for new transfer */
  HAL_DMA_DeInit(&hdma_adc);
  
  /* Configure the DMA Channel */
  HAL_DMA_Init(&hdma_adc);
  
  /* ADC DMA IRQ Channel configuration */
  HAL_NVIC_SetPriority(AUDIO_IN_DMAx_IRQ, AUDIO_IN_IRQ_PREPRIO, 0);
  HAL_NVIC_EnableIRQ(AUDIO_IN_DMAx_IRQ); 
}
  
/**
  * @brief  Initializes the OPAMP BSP.
  * @param  hopamp : OPAMP handle
  * @retval None
  */
void OPAMPx_MspInit(OPAMP_HandleTypeDef* hopamp)
{
  GPIO_InitTypeDef  gpioinitstruct = {0};
  
  /*** Configure the GPIOs ***/  
  /* Enable GPIO clock */
  AUDIO_IN_OPAMP_GPIO_CLK_ENABLE();

  gpioinitstruct.Pin    = AUDIO_IN_OPAMP_PIN;
  gpioinitstruct.Mode   = GPIO_MODE_ANALOG;
  gpioinitstruct.Pull   = GPIO_NOPULL;
  gpioinitstruct.Speed  = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(AUDIO_IN_OPAMP_PORT, &gpioinitstruct);
  
  /*** Configure the OPAMP peripheral ***/
  /* Enable OPAMP clock */
  __HAL_RCC_OPAMP_CLK_ENABLE();
}

/**
  * @brief Tx Transfer completed callbacks
  * @param hi2s: I2S handle
  * @retval None
  */
void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
  if(hi2s->Instance == I2SOUT)
  {
    /* Call the user function which will manage directly transfer complete*/  
    BSP_AUDIO_OUT_TransferComplete_CallBack();       
  }
}

/**
  * @brief Tx Transfer Half completed callbacks
  * @param hi2s: I2S handle
  * @retval None
  */
void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
  if(hi2s->Instance == I2SOUT)
  {
    /* Manage the remaining file size and new address offset: This function 
    should be coded by user (its prototype is already declared in stm32l152d_eval_audio.h) */  
    BSP_AUDIO_OUT_HalfTransfer_CallBack();
  }
}

/**
  * @brief I2S error callbacks
  * @param hi2s: I2S handle
  * @retval None
  */
void HAL_I2S_ErrorCallback(I2S_HandleTypeDef *hi2s)
{
  /* Manage the error generated on DMA FIFO: This function 
     should be coded by user (its prototype is already declared in stm32l152d_eval_audio.h) */  
  if(hi2s->Instance == I2SOUT)
  {
    BSP_AUDIO_OUT_Error_CallBack();
  }
}

/**
  * @brief  Initializes the TIM Base BSP.
  * @param  htim : Timer handle
  * @retval None
  */
void TIMx_Base_MspInit(TIM_HandleTypeDef* htim)
{
  if (htim->Instance == TIM3)
  {
    __HAL_RCC_TIM3_CLK_ENABLE();
  }
}

/**
  * @brief  Conversion complete callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    BSP_AUDIO_IN_TransferComplete_CallBack();
}

/**
  * @brief  Conversion DMA half-transfer callback in non blocking mode 
  * @param  hadc: ADC handle
  * @retval None
  */
void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc)
{
    BSP_AUDIO_IN_HalfTransfer_CallBack();
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
