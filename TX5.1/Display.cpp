// 
// 
// 

#include "Display.h"

void Display::drawFLsymb (uint8_t x, uint8_t y)
    {
    screen.drawLine  (x + 0, y + 1, x + 0, y + 5, WHITE);
    screen.drawLine  (x + 2, y + 0, x + 2, y + 6, WHITE);
    screen.drawPixel (x + 1, y + 0, WHITE);
    screen.drawPixel (x + 1, y + 6, WHITE);
    screen.drawFastHLine (x + 3, y + 5, 3, WHITE);
    screen.drawFastHLine (x + 3, y + 3, 3, WHITE);
    screen.drawFastHLine (x + 3, y + 1, 3, WHITE);
    }

void Display::drawBLsymb (uint8_t x, uint8_t y)
    {
    screen.fillCircle (x + 3, y + 3, 1, WHITE);
    screen.drawPixel  (x + 5, y + 6, WHITE);
    screen.drawPixel  (x + 1, y + 6, WHITE);
    screen.drawPixel  (x + 0, y + 3, WHITE);
    screen.drawPixel  (x + 6, y + 3, WHITE);
    screen.drawPixel  (x + 5, y + 0, WHITE);
    screen.drawPixel  (x + 1, y + 0, WHITE);
    }

void Display::drawULsymb (uint8_t x, uint8_t y)
    {
    screen.drawLine (x + 1, y + 0, x + 5, y + 0, WHITE);
    screen.drawLine (x + 0, y + 2, x + 6, y + 2, WHITE);
    screen.drawPixel (x + 0, y + 1, WHITE);
    screen.drawPixel (x + 6, y + 1, WHITE);
    screen.drawFastVLine (x + 5, y + 3, 3, WHITE);
    screen.drawFastVLine (x + 3, y + 3, 3, WHITE);
    screen.drawFastVLine (x + 1, y + 3, 3, WHITE);
    }

Display::Display ()
    {
    screen.begin (SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
    screen.display ();
    }

void Display::drawMainScr (lights_mode l_mode_sel, bool ul_pwr_sel,
                           int speed, mode mode_sel, double approx, int percents,
                           double trip, int odo)
    {
    screen.clearDisplay ();
    screen.setTextColor (WHITE);
    
    // Speed
    screen.setCursor (0, 0);
    screen.setTextSize (2);
    screen.print (speed);
    screen.setTextSize (1);
    screen.print ("km/h");

    // Percents
    screen.setCursor ((SCR_W - 1) - 41, 0);
    screen.setTextSize (2);
    screen.print (percents);
    screen.setTextSize (1);
    screen.print ("%");
    
    // Approx
    screen.setCursor ((SCR_W - 1) - 41, SCR_H*3/4 - 1);
    screen.setTextSize (1);
    screen.print ('~');
    screen.print (approx, 1);
    screen.print ("km");

    // Odo / trip
    screen.setCursor (0, SCR_H*3/4 - 1);
    screen.setTextSize (1);
    if (TIMER_GET (mscr_odo_trp_switch) < MSCR_ODO_TRP_SWITCH_TIME)
        {
        screen.print ("odo ");
        screen.print (odo);
        screen.print (" km");
        }
    else
        {
        if (TIMER_GET (mscr_odo_trp_switch) > 2*MSCR_ODO_TRP_SWITCH_TIME)
            TIMER_RST (mscr_odo_trp_switch);

        screen.print ("trp ");
        screen.print (trip, 1);
        screen.print (" km");
        }

    // Mode
    screen.setCursor (41, SCR_H/4 + 3);
    switch (mode_sel)
        {
        case mode::lock:
            screen.print ("  lock ");
            break;
        case mode::hybrid:
            screen.print (" hybrid");
            break;
        case mode::eco:
            screen.print ("  eco  ");
            break;
        case mode::cruise:
            screen.print (" cruise");
            break;
        case mode::sport:
            screen.print (" sport ");
            break;
        default:
            break;
        }

    // Lights mode
    if (ul_pwr_sel)
        drawULsymb (SCR_MID_X - 12, 0);
    switch (l_mode_sel)
        {
        case lights_mode::_off:
            break;
        case lights_mode::_rear:
            drawBLsymb (SCR_MID_X - 4, 0);
            break;
        case lights_mode::_all:
            drawBLsymb (SCR_MID_X - 4, 0);
            drawFLsymb (SCR_MID_X + 4, 0);
            break;
        case lights_mode::_auto:
            drawBLsymb (SCR_MID_X - 4, 0);
            drawFLsymb (SCR_MID_X + 4, 0);
            screen.setCursor (SCR_MID_X + 12, 0);
            screen.print ("A");
            break;
        default:
            break;
        }
    }

void Display::drawMenuScr (int cursor)
    {
    screen.clearDisplay ();
    screen.setCursor (SCR_MID_X - 40, 0);
    screen.setTextSize (1);
    screen.print ("Underlights");
    screen.setCursor (SCR_MID_X - 40, 8);
    screen.print ("Battery");
    screen.setCursor (SCR_MID_X - 40, 16);
    screen.print ("Trip control");

    screen.setCursor (0, 8*cursor);
    screen.print ("-->");
    }

void Display::display ()
    {
    screen.display ();
    }
