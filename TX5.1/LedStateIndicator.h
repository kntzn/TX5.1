// LedStateIndicator.h

#ifndef _LEDSTATEINDICATOR_h
#define _LEDSTATEINDICATOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Battery.h"

class LedStateIndicator
    {
    private:
        uint8_t tx_r, tx_g, tx_b;
        uint8_t rx_r, rx_g, rx_b;

        void showColorTx (bool r, bool g, bool b);
        void showColorRx (bool r, bool g, bool b);
    public:
        LedStateIndicator (uint8_t tx_r, uint8_t tx_g, uint8_t tx_b,
                           uint8_t rx_r, uint8_t rx_g, uint8_t rx_b);

        void update (double voltage, double percents = -1);
            
    };

#endif

