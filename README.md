# Arduino-Data-Monitor
An Arduino program with output to an LCD screen allowing users to browse and alter data of channels

Uses Finite State Machines (FSMs) to allow a user to scroll through channels on an LCD display, and use commands to change values, descriptions and maximum and minimum boundaries for each channel.

![82F789DC-B8DA-4681-AB63-889FC419A16F](https://user-images.githubusercontent.com/109162427/187078291-7d5a8975-b2d9-4df6-bb3f-aac30187713d.JPG)

The LCD screen changes colours if an entered value is above the maximum or below the minimum

![2748DCE6-792A-456C-89D9-CDCF1F784DD3](https://user-images.githubusercontent.com/109162427/187078293-33a836d5-9a1d-4baf-8fb6-1fbd5d4309da.JPG)

Every channel below the minimum is displayed when the left arrow is pressed and every channel with a value above the maximum is displayed when the right arrow is pressed.

The program can also store the last 16 values into EEPROM memory, storing the values of these channels even after a device restart
