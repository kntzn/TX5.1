// 
// 
// 

#include "Display.h"

Display::Display ()
    {
    screen.begin (SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
    screen.display ();
    }

void Display::drawMainScr (int quality, lights_mode l_mode_sel, double bat_v,
                           int speed, mode mode_sel, double approx, int percents,
                           double trip, int odo)
    {
    screen.clearDisplay ();
    screen.setTextSize (1);
    screen.setTextColor (WHITE);

    // Quality

    // LightMode
    switch (l_mode_sel)
        {
        case lights_mode::_off:
            break;
        case lights_mode::_rear:
            break;
        case lights_mode::_all:
            break;
        case lights_mode::_auto:
            break;
        default:
            break;
        }

    // BatV
    screen.setCursor (SCR_MID_X + 32/2, 0);
    screen.print (bat_v, 1);

    // Speed
    screen.setTextSize (2);
    screen.setCursor (0, SCR_H/4 - 1);
    screen.print (speed);
    screen.setTextSize (1);
    screen.print ("km/h");
    // Mode_sel
    switch (mode_sel)
        {
        case mode::lock:
            screen.setCursor (MSCR_MODE_MIN_MARGIN_X + 5, SCR_H/4 - 1);
            screen.print ("lock");
            break;
        case mode::hybrid:
            screen.setCursor (MSCR_MODE_MIN_MARGIN_X,     SCR_H/4 - 1);
            screen.print ("hybrid");
            break;
        case mode::eco:
            screen.setCursor (MSCR_MODE_MIN_MARGIN_X + 7, SCR_H/4 - 1);
            screen.print ("eco");
            break;
        case mode::cruise:
            screen.setCursor (MSCR_MODE_MIN_MARGIN_X,     SCR_H/4 - 1);
            screen.print ("cruise");
            break;
        case mode::sport:
            screen.setCursor (MSCR_MODE_MIN_MARGIN_X + 2, SCR_H/4 - 1);
            screen.print ("sport");
            break;
        default:
            break;
        }
    // Approx
    screen.setCursor (SYMB_2_SIZE_X*4, SCR_H/2 - 1);
    screen.print ("~");
    screen.print (approx, 1);
    screen.print ("km");
    // Percents
    screen.setTextSize (2);
    screen.setCursor (SCR_W - SYMB_2_SIZE_X*4 - 2, SCR_H/4 - 1);
    screen.print (percents);
    screen.print ('%');
    
    // Trip
    screen.setTextSize (1);
    screen.setCursor (0, SCR_H*3/4 - 1);
    screen.print ("trp");
    screen.print (trip, 1);
    screen.print ("km");
    // Odo
    screen.setCursor (SYMB_SIZE_X*13 - 1, SCR_H*3/4 - 1);
    screen.print ("odo");
    screen.print (trip, 1);
    screen.print ("km");
    }

void Display::drawMenuScr (int cursor)
    {
    
    }

void Display::display ()
    {
    screen.display ();
    }
