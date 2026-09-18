A simple Arduino DMX receiver showing the last updated dmx channel and its value on a display.
I currently have a setup using the CQRobot DMX Shield and Waveshare LCD1602 RGB display. The shield / library for it sadly only works on an UNO R3.

The shield is configured to use the UART pins of the arduino, so the jumpers for configuration may need to be adjusted accordingly.
The library I'm using for the shield is the Conceptinetics library, which is also included in this repo. The library for the display is also included. 
As a warning, both libraries have been stripped of (for me) unnecessary code. 