// Button.h

#ifndef _BUTTON_h
#define _BUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define N_TESTS 10
#define HOLD_TIME 500

class Button
    {
    public:
        enum class State
            {
            unpressed,
            press,
            pressed,
            released,
            hold
            };

    private:
        bool last_isPrsd;
        byte pin;
        State curr_state;
        unsigned long int last_press;

        bool isPrsd ();

    public:
        Button (byte pinId);

        void update ();

        State state ();

    };


#endif

