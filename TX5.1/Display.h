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
#include "Config.h"
#include "kstd.h"

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

#define MSCR_MODE_MIN_MARGIN_X 40

#define MENU_CURSOR_POS_UL 0
#define MENU_CURSOR_POS_BAT 1
#define MENU_CURSOR_POS_TRP 2

// TODO: move drawing to separate inline functions

class Display
    {
    public:
        enum class screen_name
            {
            main,
            menu,
            connecting,
            battery
            };
    private:
        Adafruit_SSD1306 screen;
        TIMER_SET (mscr_odo_trp_switch);
        TIMER_SET (_conn_scr_ticks_timer);

        void drawFLsymb (uint8_t x, uint8_t y);
        void drawBLsymb (uint8_t x, uint8_t y);
        void drawULsymb (uint8_t x, uint8_t y);

    public:
        Display ();
        
        void drawMainScr (lights_mode l_mode_sel, bool ul_pwr_sel,
                          int speed, mode mode_sel, double approx, int percents,
                          double trip, int odo);
        void drawMenuScr (int cursor);
        void drawBatScr (double voltage, double cellVoltage, int percents,
                         double approx, double whLeft, double consumption);
        void drawConnScr ();

        void display ();

    };

#endif

