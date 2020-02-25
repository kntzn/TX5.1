// Display.h

#ifndef _DISPLAY_h
#define _DISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Adafruit_SSD1306.h>
#include "SysConfig.h"

#ifndef SSD1306_128_32 
    #error incorrect display size, check Adafruit_SSD1306.h
#endif // !SSD1306_128_32 

#define SCR_H 32
#define SCR_W 128

#define SCR_MID_X (SCR_W/2)
#define SCR_MID_Y (SCR_H/2)

#define SYMB_SIZE_X 5
#define SYMB_SIZE_Y 8
#define SYMB_2_SIZE_X (SYMB_SIZE_X*2)
#define SYMB_2_SIZE_Y (SYMB_SIZE_Y*2)

#define MSCR_MODE_MIN_MARGIN_X 48

class Display
    {
    private:
        Adafruit_SSD1306 screen;
        int y;

    public:
        Display ();
        
        void drawMainScr (int quality, lights_mode l_mode_sel, double bat_v,
                          int speed, mode mode_sel, double approx, int percents,
                          double trip, int odo);
        void drawMenuScr (int cursor);

        void display ();

    };

#endif

