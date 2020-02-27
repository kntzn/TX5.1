/*
 Name:		TX5.1.ino
 Created:	2/6/2020 8:51:50 PM
 Author:	kntzn
 Info:      Firmware v.1 for HW gen.5
*/



#include "DataHandler.h"
#include "Communication.h"
#include "Display.h"
#include "Button.h"
#include "Battery.h"
#include "LedStateIndicator.h"

#include "Pinout.h"
#include "SysConfig.h"


#define forever for(;;)

int readThrottle (uint8_t pot_pin);

bool changeLightsModeBtnHandler (Button* b, lights_mode &l_mode_sel);
bool changeRideModeBtnHandler   (Button* b, mode        &mode_sel);

// TODO: interface

int main()
	{
    init ();
    
    pinMode (POT_PWR, OUTPUT);
    digitalWrite (POT_PWR, HIGH);

    // Classes
    Display           OLED;
    Button            b_top          (BTN_TOP);
    Button            b_mid          (BTN_MID);
    Button            b_btm          (BTN_BTM);
    Communication     HC12           (HC12_SET, 0); // TODO: load channel from EEPROM
    DataHandler       data_container (mode::sport, lights_mode::_off, false); // TODO: load lights from EEPROM
    Battery           battery        (VCC_IN);
    LedStateIndicator lsi            (LED_1_R, LED_1_G, LED_1_B,
                                      LED_2_R, LED_2_G, LED_2_B);
    
    // Communication vars
    bool pendingChange = false;
    bool connected = false;
    bool waitingForResponse = false;
    TIMER_SET (last_request_tmr);
    int ping = 0;
    Communication::command prev_request = Communication::command::trip;
    
    // TX vars
    bool        ul_pwr_sel = true;
    lights_mode l_mode_sel = lights_mode::_auto; // TODO: load from eeprom
    mode        r_mode_sel = mode::eco;          // TODO: load from eeprom

    // Other
    Display::screen_name scr_id = Display::screen_name::main;

    // Main cycle
	forever 
		{
        // Updates buttons
        b_top.update ();
        b_mid.update ();
        b_btm.update ();
        battery.update ();

        // If tx is in transmitting mode
        if (!waitingForResponse)
            {
            // If it is time to send request
            if (TIMER_GET (last_request_tmr) > REQUEST_PERIOD)
                {
                // Activating idle mdoe
                TIMER_RST (last_request_tmr);
                waitingForResponse = true;

                // And sending request 
                switch (prev_request)
                    {
                    case Communication::command::trip:
                        prev_request = Communication::command::battery;
                        HC12.sendCommand (prev_request);
                        break;
                    case Communication::command::battery:
                        prev_request = Communication::command::trip;
                        HC12.sendCommand (prev_request);
                        break;
                    default:
                        break;
                    }
                }
            // else sending standart Drive Controller command
            else
                {
                data_container.setThrottle (readThrottle (POT_IN));
                data_container.loadDriveControllerParams (HC12.argbuf ());
                HC12.sendCommand (Communication::command::motor);
                }
            }
        // If tx is in receiveing mode
        else
            {
            // Timeout
            if (TIMER_GET (last_request_tmr) > RESPONSE_TIMEOUT)
                {
                waitingForResponse = false;
                connected = false;
                }

            // Waiting for request
            Communication::response resp;
            if ((resp = HC12.receiveResponse ()) !=
                Communication::response::noresp)
                {
                // Calculates the delay between TX/RX
                ping = TIMER_GET (last_request_tmr) / 2.0;

                // Saves
                switch (resp)
                    {
                    case Communication::response::battery:
                        data_container.saveBMSparams (HC12.argbuf ());
                        break;
                    case Communication::response::trip:
                        data_container.saveDriveControllerParams (HC12.argbuf ());
                        break;
                    default:
                        break;
                    }

                HC12.flush ();
                waitingForResponse = false;
                connected = true;
                }
            }

        // Screen switch
        switch (scr_id)
            {
            case Display::screen_name::main:
                OLED.drawMainScr (l_mode_sel, ul_pwr_sel,
                                  static_cast <int> (data_container.getSpeed ()),
                                  r_mode_sel,
                                  data_container.getApprox (),
                                  static_cast<int> (data_container.getBatPercents ()),
                                  data_container.getTrip (), data_container.getOdo ());

                // Handles top btn (lights mode)
                changeLightsModeBtnHandler (&b_top, l_mode_sel);
                // Handles btm btn (ride   mode)
                changeRideModeBtnHandler   (&b_btm, r_mode_sel); 
                break;
            case Display::screen_name::menu:
                // reserved
                break;
            default:
                break;
            }



        lsi.update (battery.getVoltage ());
        OLED.display ();
        }
	}

int readThrottle (uint8_t pot_pin)
    {
    return map (1023 - analogRead (pot_pin), 0, 1023, THR_MIN, THR_MAX);
    }

bool changeLightsModeBtnHandler (Button* b, lights_mode &l_mode_sel)
    {
    if (b->state () == Button::State::hold)
        {
        if (l_mode_sel != lights_mode::_auto)
            l_mode_sel = lights_mode::_auto;
        else
            l_mode_sel = lights_mode::_off;
        }
    else if (b->state () == Button::State::press)
        switch (l_mode_sel)
            {
            case lights_mode::_off:
                l_mode_sel = lights_mode::_rear;
                break;
            case lights_mode::_rear:
                l_mode_sel = lights_mode::_all;
                break;
            case lights_mode::_all:
                l_mode_sel = lights_mode::_off;
                break;
            default:
                break;
            }
    }
bool changeRideModeBtnHandler   (Button *b, mode        &mode_sel)
    {
    if (b->state () == Button::State::hold)
        {
        if (mode_sel != mode::hybrid)
            mode_sel = mode::hybrid;
        else
            mode_sel = mode::lock;
        }
    else if (b->state () == Button::State::press)
        switch (mode_sel)
            {
            case mode::eco:
                mode_sel = mode::cruise;
                break;
            case mode::cruise:
                mode_sel = mode::sport;
                break;
            case mode::sport:
                mode_sel = mode::eco;
                break;
            default:
                break;
            }
    }
