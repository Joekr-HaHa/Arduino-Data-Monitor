# Arduino-Data-Monitor
An Arduino program with output to an LCD screen allowing users to browse and alter data of channels

Uses Finite State Machines (FSMs) to allow a user to scroll through channels on an LCD display, and use commands to change values, descriptions and maximum and minimum boundaries for each channel.

The LCD screen changes colours if an entered value is above the maximum or below the minimum

Every channel below the minimum is displayed when the left arrow is pressed and every channel with a value above the maximum is displayed when the right arrow is pressed.

The program can also store the last 16 values into EEPROM memory, storing the values of these channels even after a device restart
