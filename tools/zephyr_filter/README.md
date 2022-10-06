# Filter Tool for Zephyr Platform
This tool allows running our signal processing algorithms on the *Zephyr* platform
and also run performance timing on these algorithms.

Most development and testing of this tool has been on the STM32F750N8 MCU on the
STM32F7508-DK development board.

## Quick(ish) Start

1. Set up your *Zephyr* development environment. Follow the steps [here](https://docs.zephyrproject.org/latest/develop/getting_started/index.html)
   if needed.

2. Development and compiling is configured for work in a Zephyr *workspace*
   application.
    - The base location for the Zephyr files will be referred to as *zephyrproject*.
    - The top-level of this repository will need to be checked out into the
      *zephyrproject* location so that the repository files are now located at
      *zephyrproject/workshop*.

3. With your *Zephyr* environment fully configured, change to the *zephyrproject*
   directory and build the tools to target the STM32F7508-DK development board. \
   `west build -p always -b stm32f7508_dk workshop/tools/zephyr_filter`

4. With the development board connected via the USB cable for programming, flash
   the board with the image. \
   `west flash`

5. The development board should not be running with a flashing green LED.
