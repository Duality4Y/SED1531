#ifndef SED1531_h
#define SED1531_h

#include "Arduino.h"
#include "Print.h"

class SED1531 : public Print{
	public:
		void setCursor(byte row);
		void init();
		void setContrast(byte);
		void writecommand(byte);
		void writePixData(byte);
		void inverse(byte);
		void setMarker(byte,boolean);
		virtual size_t write(byte);
		void rect(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);
		void resetCursor();
	//private:
};
#endif
