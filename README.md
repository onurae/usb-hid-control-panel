## USB HID Control Panel

![Image of Control Panel](https://github.com/onurae/usb-hid-control-panel/blob/main/images/IMG_1.jpg)

### Parts
- 1 Arduino Pro Micro
- 8 Buttons
- 4 Switches
- 1 Rotary Encoder with Push Button
- 1 Enclosure
- 1 Micro USB Cable

### Connections
| Part Pin       | Arduino Pin    |
| :---           |     :---       |
| Switch 1       |  5             |
| Switch 2       |  6             |
| Switch 3       |  7             |
| Switch 4       |  8             |
| Blue Button    |  9             |
| Green Button   |  16            |
| Red Button 1   |  20 (A2)       |
| Red Button 2   |  18 (A0)       |
| Red Button 3   |  14            |
| Black Button 1 |  21 (A3)       |
| Black Button 2 |  19 (A1)       |
| Black Button 3 |  15            |
| Encoder CLK    |  2 (Interrupt) |
| Encoder DT     |  3             |
| Encoder SW     |  4             |
| Encoder GND    |  GND           |
| Encoder VCC    |  VCC           |

Connect the other ends of the buttons & switches to GND.

### Uploading
- Download and install Arduino IDE.
- Download [Arduino Joystick Library](https://github.com/MHeironimus/ArduinoJoystickLibrary) and copy the folder to the Arduino/libraries folder.
- Connect the board using the USB cable.
- Open the PanelHID.ino file with Arduino IDE.
- Select the board under the Tools menu.
- Choose correct serial port for the board.
- Click the Upload button.
