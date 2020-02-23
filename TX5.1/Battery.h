// Battery.h

#ifndef _BATTERY_h
#define _BATTERY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Config.h"

class Battery
    {
    private:
        double bat_voltage;
        uint8_t ADCpin;

        long readVcc ();
        double aver_analog (uint32_t times = 10U);
        
    public:
        Battery (uint8_t read_pin);

        void readVoltage (bool noFilter = false);
        double getVoltage ();
    };

#endif

