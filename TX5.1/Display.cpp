// 
// 
// 

#include "Display.h"

Display::Display ()
    {
    sreen.begin (SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
    }

void Display::drawMainScr (int quality, int light_mode, int bat_v, int speed, int mode, int approx, int percents, double trip, double odo)
    {

    }

void Display::drawMenuScr (int cursor)
    {
    }

void Display::display ()
    {
    sreen.display ();
    }
