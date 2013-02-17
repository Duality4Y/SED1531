SED1531
=======

arduino library for working with the SED1531 (controller/glcd)

Pinout display:

From LCD to arduino
Pin   LCD                                PIN Arduino
 
1     GND
2     +5V                                 Digital 13 
3     Backlight (GND)
4     AO (L - instruction/ H - data)      Digital 12
5     Read/Write (H - Read / L - Writer)  Digital 11
6     Enable Digital                      Digital 10
 
Data
7    DB 7 MSB                             Digital 9
8    DB 6                                 Digital 8
9    DB 5                                 Digital 7
10   DB 4                                 Digital 6
11   DB 3                                 Digital 5
12   DB 2                                 Digital 4
13   DB 1                                 Digital 3
14   DB 0 LSB                             Digital 2

Documentation:

http://tkkrlab.nl/wiki/Glcd_48x100
