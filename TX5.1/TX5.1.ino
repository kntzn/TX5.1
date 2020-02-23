/*
 Name:		TX5.1.ino
 Created:	2/6/2020 8:51:50 PM
 Author:	kntzn
 Info:      Firmware v.1 for HW gen.5
*/

#include "Battery.h"
#include "Display.h"
#include "Button.h"
#include "Communication.h"
#include "Pinout.h"

#define forever for(;;)

int main()
	{
    Display OLED;

    Button b_top (BTN_TOP);
    Button b_mid (BTN_MID);
    Button b_btm (BTN_BTM);

    Communication HC12 (HC12_SET, 0); // TODO: load channel from EEPROM

    Battery battery (VCC_IN);

	forever 
		{
		
		}
	}