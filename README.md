Own built MFA for VW Golf MK2 with tachometer.

Build with Arduino and 1.3" Oled Display. Integrated in Original Golf MK2 speedometer and Switched with MFA lever.


Upcoming functions:

- Display for battery level
- Display for time
- Display for oil temperature
- Display for oil pressure
- Display for cooler temperature
- Display for outside and inside temperature

Hardware:

CPU: Arduino UNO
Display: 1.3" SSH1106 Oled Display (I2C)
Batterysensor: DC0-25V Voltage Sensor (I2C)

Pinout:

Voltage Sensor:
-   : GND
S   : A0

Oled Display:
-   : GND
+   : 5V
SCK : A5
SDA : A4

 Button:
-   : GND
S   : D4 
