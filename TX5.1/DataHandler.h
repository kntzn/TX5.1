// DataHandler.h

#ifndef _DATAHANDLER_h
#define _DATAHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class DataHandler
    {
    private:
/*
// RX BAT
buffer [0] = static_cast <uint8_t> (percents);
buffer [1] = static_cast <uint8_t> ((bat_voltage*N_CELLS) * 10.0);
buffer [2] = static_cast <uint8_t> ((bat_voltage        ) * 10.0);
buffer [3] = static_cast <uint8_t> (whDrawn);
buffer [4] = static_cast <uint8_t> (BAT_WH - whDrawn);

// RX D_C
buffer [0] = static_cast <int> (speed);                     // Speed
buffer [1] = static_cast <int> (acceleration*10.0 + 127.0); // Accel
buffer [2] = static_cast <int> (odo/256);                   // Odo hb
buffer [3] = static_cast <int> (odo) % 256;                 // Odo lb
buffer [4] = static_cast <int> (totalTrip/256);             // Odo hb
buffer [5] = static_cast <int> (totalTrip) % 256;           // Odo lb
buffer [6] = static_cast <int> (left /256);                 // Odo hb
buffer [7] = static_cast <int> (left) % 256;                // Odo lb
buffer [8] = static_cast <int> (consumption/10.0);          // Consumption
*/
        double rx_bat_percents, rx_bat_voltage, rx_bat_cell_voltage,
               rx_bat_wh_drawn, rx_bat_wh_left;
        double rx_dc_speed, rx_dc_accel, 
               rx_dc_odo, rx_dc_trip, rx_dc_left,
               rx_dc_consumption;

        mode        tx_dc_mode;
        int         tx_dc_throttle;
        lights_mode tx_lc_lights_mode;
        bool        tx_lc_underlights;

    public:
        DataHandler (mode mode_selected, lights_mode l_mode_selected, bool ul_active);
    };

#endif

