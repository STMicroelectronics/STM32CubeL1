# STM32CubeL1 MCU Firmware Package

![latest tag](https://img.shields.io/github/v/tag/STMicroelectronics/STM32CubeL1.svg?color=brightgreen)

**STM32Cube** is an STMicroelectronics original initiative to ease developers' life by reducing efforts, time and cost.

**STM32Cube** covers the overall STM32 products portfolio. It includes a comprehensive embedded software platform delivered for each STM32 series.
   * The CMSIS modules (core and device) corresponding to the ARM(tm) core implemented in this STM32 product.
   * The STM32 HAL-LL drivers, an abstraction layer offering a set of APIs ensuring maximized portability across the STM32 portfolio.
   * The BSP drivers of each evaluation, demonstration or nucleo board provided for this STM32 series.
   * A consistent set of middleware libraries such as RTOS, USB, FatFS, graphics, touch sensing library...
   * A full set of software projects (basic examples, applications, and demonstrations) for each board provided for this STM32 series.

The **STM32CubeL1 MCU Package** projects are directly running on the STM32L1 series boards. You can find in each Projects/*Board name* directories a set of software projects (Applications/Demonstration/Examples).

In this FW Package, the modules **Middlewares/ST/TouchGFX** and **Middlewares/ST/STemWin** are not directly accessible. They must be downloaded from a ST server. The respective URL are available in a readme.txt file inside each module.

## Release note

Details about the content of this release are available in the release note [here](https://htmlpreview.github.io/?https://github.com/STMicroelectronics/STM32CubeL1/blob/master/Release_Notes.html).

## Boards available

  * STM32L1
    * [32L100CDISCOVERY](https://www.st.com/en/evaluation-tools/32l100cdiscovery.html)
    * [32L152CDISCOVERY](https://www.st.com/en/evaluation-tools/32l152cdiscovery.html)
    * [NUCLEO-L152RE](https://www.st.com/en/evaluation-tools/nucleo-l152re.html)
    * [STM32L152D-EVAL](https://www.st.com/en/evaluation-tools/stm32l152d-eval.html)

## Troubleshooting

**Caution** : The issues and the pull-requests are **strictly limited** to submit problems or suggestions related to the software delivered in this repository.

**For any other question** related to the product, the hardware performance or characteristics, the tools, the environment, you can submit it to the **ST Community** on the STM32 MCUs related [page](https://community.st.com/s/group/0F90X000000AXsASAW/stm32-mcus).
