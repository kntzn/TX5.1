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

int main()
	{
    init ();
    Serial.begin (HC12_BAUD);
    while (!Serial);

    pinMode (POT_PWR, OUTPUT);
    digitalWrite (POT_PWR, HIGH);

    Display           OLED;
    Button            b_top          (BTN_TOP);
    Button            b_mid          (BTN_MID);
    Button            b_btm          (BTN_BTM);
    Communication     HC12           (HC12_SET, 0); // TODO: load channel from EEPROM
    DataHandler       data_container (mode::sport, lights_mode::_off, false);
    Battery           battery        (VCC_IN);
    LedStateIndicator lsi            (LED_1_R, LED_1_G, LED_1_B,
                                      LED_2_R, LED_2_G, LED_2_B);
    
    bool waitingForResponse = false;
    Communication::command prev_request = Communication::command::trip;
    


	forever 
		{
        data_container.setThrottle (readThrottle (POT_IN));
        data_container.loadDriveControllerParams (HC12.argbuf ());
        HC12.sendCommand (Communication::command::motor);
        delay (25);


        OLED.drawMainScr (0, lights_mode::_off, battery.getVoltage (), 
                          22, mode::cruise, 11.1, 100,
                          999.9, 9999);

        battery.update ();
        b_top.upd ();
        b_mid.upd ();
        b_btm.upd ();
        lsi.update (battery.getVoltage ());
        OLED.display ();
        }
	}

int readThrottle (uint8_t pot_pin)
    {
    return map (1023 - analogRead (pot_pin), 0, 1023, THR_MIN, THR_MAX);
    }
