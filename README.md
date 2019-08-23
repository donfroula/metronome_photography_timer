# metronome_photography_timer
Audible metronome timer for darkroom and long exposures

This ATTINY85 project is for a metronome timer that may be used in a darkroom for timing various processes in total darkness (omit LED or use a red LED, if it will not expose sensitive materials). It is also useful for making long exposures for wet plate collodion work and night shots.

The timer is started by pressing the start button, then releasing. It starts counting on the button release for more precise timing. Thereafter, the timer ticks and gives a short flash of the LED at one-second intervals, with a short beep and longer flash of the LED every 15 seconds.

15 seconds before the three minute mark, the timer gives a warning beep and longer LED flash every second until sounding the alarm at the three minute mark. The timer may be stopped and reset at any time by depressing the button again.

The time may be powered by a common CR2032 lithium cell. The device enters a ultra-low power sleep mode when not running. The battery will last for months of normal use. No on/off switch is required.

Since the timer uses the initially inaccurate internal oscillator, the unit should be calibrated by timing out the full three minutes using another time source, then adjusting the "OSCCAL -= 4;" statement on line 21 up or down until the three minute period is correct, reprogramming the ATTINY85 after each adjustment.

The circuit requires only a power and ground connection to the ATTINY85, and LED conncted to pin D0 and ground through a 150 ohm resistor, and a small piezo speaker connected between pin D1 and ground.
