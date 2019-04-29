# STM32CubeL1 MCU Firmware Package

**STM32Cube** is an STMicroelectronics original initiative to ease the developers life by reducing efforts, time and cost.

**STM32Cube** covers the overall STM32 products portfolio. It includes a comprehensive embedded software platform (this repo), delivered for each series (such as the STM32CubeL1 for the STM32L1 series).
   * The CMSIS modules (core and device) corresponding to the ARM(tm) core implemented in this STM32 product
   * The STM32 HAL-LL drivers : an abstraction drivers layer, the API ensuring maximized portability across the STM32 portfolio 
   * The BSP Drivers of each evaluation or demonstration board provided by this STM32 series 
   * A consistent set of middlewares components such as RTOS, USB Device, FatFS, STM32_TouchSensing_Library ...
   * A full set of software projects (basic examples, applications or demonstrations) for each board provided by this STM32 series
   
The **STM32CubeL1 MCU Package** projects are directly running on the STM32L1 series boards. You can find in each Projects/*Board name* directories a set of software projects (Applications/Demonstration/Examples). 

In this FW Package, the module **Middlewares/ST/STemWin** is not directly accessible. It must be downloaded from a ST server, the URL is available in a readme.txt file inside the module.

## Boards available
  * STM32L1
    * [NUCLEO-L152RE](https://www.st.com/en/evaluation-tools/nucleo-l152re.html)
    * [32L100CDISCOVERY](https://www.st.com/en/evaluation-tools/32l100cdiscovery.html)
    * [32L152CDISCOVERY](https://www.st.com/en/evaluation-tools/32l152cdiscovery.html)
    * [STM32L152D-EVAL] - to be published soon.


## Troubleshooting

**Caution** : The **Issues** requests are strictly limited to submit problems or suggestions related to the software delivered in this repo 

**For any question** related to the STM32L1 product, the hardware performance, the hardware characteristics, the tools, the environment, you can submit a topic on the [ST Community/STM32 MCUs forum](https://community.st.com/s/group/0F90X000000AXsASAW/stm32-mcus)