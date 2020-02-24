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
        double rx_bat_percents, rx_bat_voltage, rx_bat_cell_voltage,
               rx_bat_wh_drawn, rx_bat_wh_left;
        double rx_dc_speed, rx_dc_accel, 
               rx_dc_odo, rx_dc_trip, rx_dc_left,
               rx_dc_consumption;

        mode        tx_dc_mode;
        int         tx_dc_throttle;
        lights_mode tx_lc_lights_mode;
        bool        tx_lc_underlights;
        bool        tx_cont_last_trip; // reserved

    public:
        DataHandler (mode mode_selected, lights_mode l_mode_selected, bool ul_active);

        void saveDriveControllerParams (uint8_t* buffer);
        void saveBMSparams (uint8_t* buffer);

        void loadDriveControllerParams (uint8_t* buffer);
        void loadLightControllerParams (uint8_t* buffer);
    };

#endif

