// 
// 
// 

#include "Battery.h"

long Battery::readVcc ()
    {
    #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
        ADMUX = _BV (REFS0) | _BV (MUX4) | _BV (MUX3) | _BV (MUX2) | _BV (MUX1);
    #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
        ADMUX = _BV (MUX5) | _BV (MUX0);
    #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
        ADMUX = _BV (MUX3) | _BV (MUX2);
    #else
        ADMUX = _BV (REFS0) | _BV (MUX3) | _BV (MUX2) | _BV (MUX1);
    #endif
    delay (2); // Waiting for reference voltage to settle
    ADCSRA |= _BV (ADSC); // Start conversion
    while (bit_is_set (ADCSRA, ADSC)); // Measuring
    uint8_t low = ADCL; // must read ADCL first - it then locks ADCH
    uint8_t high = ADCH; // unlocks both
    long result = (high << 8) | low;

    result = REF_VOLTAGE * 1023 * 1000 / result;
    return result;
    }

double Battery::aver_analog (uint32_t times)
    {
    double result = 0.0;

    for (int i = 0; i < times; i++)
        result += analogRead (ADCpin);

    return result / static_cast<double> (times);
    }

void Battery::update ()
    {
    // Reads new voltage
    double new_bat_voltage = (readVcc () * aver_analog () / 1023 / 1000.0);

    // Smootes out voltage value
    bat_voltage = new_bat_voltage * (1.0 - VOLTAGE_SMOOTH_K) +
                      bat_voltage *        VOLTAGE_SMOOTH_K;
    }

Battery::Battery (uint8_t read_pin):
    ADCpin (read_pin)
    {
    }

double Battery::getVoltage ()
    {
    return bat_voltage;
    }
