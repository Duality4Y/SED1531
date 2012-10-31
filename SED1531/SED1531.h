#ifndef SED1531_h
#define SED1531_h

#include "Arduino.h"
#include "Print.h"

class SED1531 : public Print{
	public:
		void setCursor(byte row);
		void begin();
		void setContrast(byte);
		void writecommand(byte);
		virtual size_t write(byte);
	//private:
};
#endif
