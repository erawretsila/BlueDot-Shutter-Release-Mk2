# BlueDot-Shutter-Release-Mk2

A remote shutter release for DSLR cmeras with electronic shutter connections (Tests on canon but would expect to work on others)

This uses an ESP32 microcontroler board to connect to the camera and the BlueDot applicaton by @martinohanlon on an android phone.

Connections on ESP32:-

Pin 12  Shutter release
Pin 13  Prefocus.

*Note This has been tested on a canon EOS 1100D but as with all Hardware projects no responsibility can be taken for any damage caused to your equipment.

The bluedot application will show 3 bluedots arranged verticaly

Dot 1 Prefocust this will for prefocus & will toggle between inactive (blue) & active Yellow.

Dot 2 Shutter, when touched it will activate the shutter (green) untill released.  if you slide your finger on the dot once activated it will lock the shutter untill released

Dot 3 Release, This will clear all signals to the camera & retur it to the idle state.

