/* 
 * ---- 30/1/2013
 * 		modified begin();
 * 		to be more true to the original sketch this is  based on.
 * 		http://tkkrlab.nl/wiki/Glcd_48x100
 * 		0xe2 does not reset the display don't know why.
 * 
 * ---- 15/2/2013
 * 		fixed an issue related to setCursor();
 * 		which caused text to appear to roll accross the screen
 * 		note:
 * 		lines longer then 20 chars will display text on display
 * 		on lines it isn't supposed to go.
 * ---- 17/2/2013
 *      fixed an issue related to setMarker();
 *      which caused text to appear on the same collumn as the marker
 *      For this to work you have to call the routine resetCursor()
 * 	    after the setMarker() routine
 *      added code to reset the display on init, without it the display
 *   	doesn't work reliable
 * */

#include <SED1531.h>
#include "Arduino.h"
#include <lcdFont1.h>

int lcdA0 = 12;
int lcdRW = 11;
int lcdEnable = 10;
int displayPower = 13;
int lcdDataPins[] = {9,8,7,6,5,4,3,2};

int currentLine = 0;
int charNum = 0;

void SED1531::init(){
	pinMode(lcdA0, OUTPUT);
	pinMode(lcdRW, OUTPUT);
	pinMode(lcdEnable, OUTPUT);
	for(int i=0;i<=7;i++){
		pinMode(lcdDataPins[i], OUTPUT);
		}
	//the following action causes the display to reset 
	digitalWrite(displayPower, LOW);
	delay(2000);
	digitalWrite(displayPower, HIGH);
   	delay(3000);
	//the following actions are performed to init the lcd
	writecommand(0xe2);                                //reset display by soft
	delay(1000);
	writecommand(0xa1);                                //ADC select
	writecommand(0xa2);                                //lcd bias 1/8
	writecommand(0x2c);                                //power
	writecommand(0x2e);                                //power
	writecommand(0x2f);                                //power
	writecommand(0xa6);                                //normal / reverse
	writecommand(0x8f);                                //set electronic control
	writecommand(0xa4);                                //display off
	writecommand(0xaf);                                //display on
	writecommand(0x40); 				               //sel dram line 1 for com1
	}

void SED1531::setContrast(byte contrast){
	writecommand(0x80+contrast);
	}

void SED1531::inverse(byte reverse){
	writecommand(0xA6+reverse);
	}

void SED1531::setMarker(byte marker, boolean on){
	byte highNibble, lowNibble;
	byte markerLCD;
	switch(marker){
		case 1:
			markerLCD = 20;			// arrows on the left
			break;
		case 2:
			markerLCD = 31;			// 2 hor. dashes
			break;
		case 3:
			markerLCD = 32;			// barcode
			break;
		case 4:
			markerLCD = 57;			// battery low
			break;
		case 5:
			markerLCD = 69;			// ?
			break;
		case 6:
			markerLCD = 78;			// arrow up
			break;
		}
	lowNibble = markerLCD&0xf;
	highNibble = markerLCD;
	highNibble = highNibble >> 4;
	bitSet(highNibble, 4);
	writecommand(0xb6);
	writecommand(highNibble);
	writecommand(lowNibble);
	writePixData(on);
	}

void SED1531::setCursor(byte row){
	byte page = 0xb0+(row);
	writecommand(page);
	writecommand(0x08);
	writecommand(0x00);
	}

void SED1531::writecommand(byte cmd){
	digitalWrite(lcdRW, LOW);
	digitalWrite(lcdA0, LOW);
	
	byte data = cmd;
	
	for (int i = 7; i >= 0; i--) {
		int value = data & 0x1;
		digitalWrite(lcdDataPins[i], value);
		data = data >> 1;
	}

	digitalWrite(lcdEnable, HIGH);
	delayMicroseconds(10);
	digitalWrite(lcdEnable, LOW);
	delayMicroseconds(10);
	digitalWrite(lcdEnable, HIGH);
	}

inline size_t SED1531::write(byte lcdData){
	digitalWrite(lcdRW, LOW);
	digitalWrite(lcdA0, HIGH);
	
	if(lcdData == '\n'|| charNum==19){
		charNum = 0;
		currentLine++;
		if(currentLine==6){
			currentLine = 0;
			setCursor(currentLine);
			}
		else{
			setCursor(currentLine);
			}
		}
	else if(isprint(lcdData)){
		charNum++;
		byte character = lcdData - 32;
		for(int col = 0;col<5;col++){
			byte data = lcdFonts[character][col];
			for(int bit = 7;bit>=0;bit--){
				byte value = data & 0x01;
				digitalWrite(lcdDataPins[bit], value);
				data = data >> 1;
			digitalWrite(lcdEnable, HIGH);
			delayMicroseconds(10);
			digitalWrite(lcdEnable, LOW);
			delayMicroseconds(10);
			digitalWrite(lcdEnable, HIGH);
			}
		}
	}

void SED1531::writePixData(byte lcdData){
	digitalWrite(lcdRW, LOW);
	digitalWrite(lcdA0, HIGH);
	
	byte data = lcdData;
	
	for (int i = 7; i >= 0 ; i--) {
		int value = data & 0x01;
		digitalWrite(lcdDataPins[i], value);
		data = data >> 1;
	}
	
	digitalWrite(lcdEnable, HIGH);
	delayMicroseconds(10);
	digitalWrite(lcdEnable, LOW);
	delayMicroseconds(10);
	digitalWrite(lcdEnable, HIGH);
	}


	
void SED1531::resetCursor() {
        writecommand(0xEE);
        writecommand(0x10);
        writecommand(0x00);
        }
