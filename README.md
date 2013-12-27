SED1531
=======

arduino library for working with the SED1531 (controller/glcd)

Pinout display:

Pin   LCD
 
1     GND
2     +5V
3     Backlight (GND)
4     AO (L - instruction/ H - data)
5     Read/Write (H - Read / L - Write)
6     Enable Digital
 
Data
7    DB 7 MSB
8    DB 6
9    DB 5
10   DB 4
11   DB 3
12   DB 2
13   DB 1
14   DB 0 LSB

Documentation:

http://tkkrlab.nl/wiki/Glcd_48x100

=======
this library is useable but I have written a better one:

https://github.com/Duality4Y/DmDisplay

DmDisplay is for the SED1531,

It can do graphical things like drawing circles rects lines and individual pixels.

but It can also just write text.

mainly 5x7 Font.
