# Zephyr Filter Tool
The *Zephyr Filter Tool* is an adaptation of the general *Filter Tool* to do
performance testing on the Zephyr based STM32 ARM platform.

This tool simple runs a vertical lines test pattern image of 256x256x1 through a
gaussian kernel while timing the processing time. Once processing is complete,
the timing results are output through the serial port and the cycle repeats
immediately.

![Zephyr Filter Tool State Machine](diagram/zephyr_filter_tool_state_machine.png)

## Notes
 - Originally, the on-board LED was going to flash to alert the user that the
   module was up and running but the current code does this by using a sleep delay.
   This is incompatible with our continuous filter loop running.
   - Will remove flashing LED until another option is implemented. It is nice to
     give the flashing feedback to the user that the system is running.
   - Instead of sleeping, could just read a counter to determine when to flash but
     our filters can take longer than the flash cycle. Even if the filter had a
     run time less than the LED flash cycle, the filter run does take time to
     process and will probably cause the flash cycle to be missed/delay and result
     in a somewhat erratic LED flash cycle.
   - Could put the LED flash cycle control on an interrupt but this will probably
     affect our filter performance timing.
   - Best option now seems to be tying the LED flash to a PWM to control. We
     would be able to configure the PWM and pretty much forget about controlling
     the LED once it is initialized.
     - Does our module support PWM at the slow speed of 1 Hz?