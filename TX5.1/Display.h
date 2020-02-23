// Display.h

#ifndef _DISPLAY_h
#define _DISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Adafruit_SSD1306.h>

#ifndef SSD1306_128_32 
    #error incorrect display size, check Adafruit_SSD1306.h
#endif // !SSD1306_128_32 


class Display
    {
    private:
        Adafruit_SSD1306 sreen;
        int y;

    public:
        Display ();
        
        void drawMainScr (int quality, int light_mode, int bat_v,
                          int speed, int mode, int approx, int percents,
                          double trip, double odo);
        void drawMenuScr (int cursor);

        void display ();

    };

#endif

