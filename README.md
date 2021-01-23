# BlueDot-Shutter-Release-Mk2

A remote shutter release for DSLR cmeras with electronic shutter connections (Tested on canon but would expect to work on others)

This uses an ESP32 microcontroler board to connect to the camera and the BlueDot applicaton by @martinohanlon on an android phone.

Connections on ESP32:-

Pin 12  Shutter release
Pin 13  Prefocus.

*Note This has been tested on a canon EOS 1100D but as with all Hardware projects no responsibility can be taken for any damage caused to your equipment.

The bluedot application will show 3 Bluedots (Blue) arranged verticaly.

Dot 1 Prefocus: This is to prefocus the camera (the same as a half depression of the shutter) & will toggle between inactive (Blue) & active (Yellow).

Dot 2 Shutter: When touched it will activate the shutter (Green) untill released .  If you slide your finger on the dot once activated it will lock the shutter open (Red) untill released.

Dot 3 Release, This will clear all signals to the camera & return it to the idle state.

