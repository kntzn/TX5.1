// 
// 
// 

#include "Display.h"

Display::Display ()
    {
    sreen.begin (SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
    sreen.display ();
    }

void Display::drawMainScr (int quality, int light_mode, int bat_v, int speed, int mode, int approx, int percents, double trip, double odo)
    {
    
    }

void Display::drawMenuScr (int cursor)
    {
    sreen.clearDisplay ();
    sreen.setCursor (0, 0);
    sreen.setTextSize (2);
    sreen.setTextColor (WHITE);
    sreen.print (cursor);
    }

void Display::display ()
    {
    sreen.display ();
    }
