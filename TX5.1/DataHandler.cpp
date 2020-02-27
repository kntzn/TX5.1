// 
// 
// 

#include "DataHandler.h"


DataHandler::DataHandler (mode mode_selected, lights_mode l_mode_selected, bool ul_active):
    rx_bat_percents (0.0), rx_bat_voltage (0.0), rx_bat_cell_voltage (0.0),
    rx_bat_wh_drawn (0.0), rx_bat_wh_left (0.0),
    rx_dc_speed (0.0), rx_dc_accel (0.0),
    rx_dc_odo (0.0), rx_dc_trip (0.0), rx_dc_left (0.0),
    rx_dc_consumption (0.0),
    tx_dc_mode (mode_selected), tx_dc_throttle (THR_MID),
    tx_lc_lights_mode (l_mode_selected), tx_lc_underlights (ul_active),
    tx_cont_last_trip (false)
    {
    }


void DataHandler::setThrottle (int new_throrrle_value)
    {
    tx_dc_throttle = new_throrrle_value;
    }
void DataHandler::setMode (mode new_mode_selected)
    {
    tx_dc_mode = new_mode_selected;
    }
void DataHandler::setLightsMode (lights_mode new_l_mode_selected)
    {
    tx_lc_lights_mode = new_l_mode_selected;
    }
void DataHandler::setUnderlightsPwr (bool on)
    {
    tx_lc_underlights = on;
    }

double DataHandler::getBatPercents ()
    {
    return rx_bat_percents;
    }
double DataHandler::getBatVoltage ()
    {
    return rx_bat_voltage;
    }
double DataHandler::getBatCellVoltage ()
    {
    return rx_bat_cell_voltage;
    }
double DataHandler::getBatWhDrawn ()
    {
    return rx_bat_wh_drawn;
    }
double DataHandler::getBatWhLeft ()
    {
    return rx_bat_wh_left;
    }
double DataHandler::getSpeed ()
    {
    return rx_dc_speed;
    }
double DataHandler::getOdo ()
    {
    return rx_dc_odo;
    }
double DataHandler::getTrip ()
    {
    return rx_dc_trip;
    }
double DataHandler::getApprox ()
    {
    return rx_dc_left;
    }
double DataHandler::getConsumption ()
    {
    return rx_dc_consumption;
    }

void DataHandler::saveDriveControllerParams (uint8_t * buffer)
    {
    rx_dc_speed       =  static_cast <double> (buffer [0]);
    rx_dc_accel       = (static_cast <double> (buffer [1]) - 127.0)/10.0;
    rx_dc_odo         = (static_cast <double> (buffer [2])) * 256 +
                         static_cast <double> (buffer [3]);
    rx_dc_trip        = (static_cast <double> (buffer [4])) * 256 +
                         static_cast <double> (buffer [5]);
    rx_dc_left        = (static_cast <double> (buffer [6])) * 256 +
                         static_cast <double> (buffer [7]);
    rx_dc_consumption = (static_cast <double> (buffer [8])) * 10.0;
    }
void DataHandler::saveBMSparams (uint8_t * buffer)
    {
    rx_bat_percents     =  static_cast <double> (buffer [0]);
    rx_bat_voltage      = (static_cast <double> (buffer [1])) * 10.0;
    rx_bat_cell_voltage = (static_cast <double> (buffer [2])) * 100.0 + BAT_ABS_MIN_CELL;
    rx_bat_wh_drawn     =  static_cast <double> (buffer [3]);
    rx_bat_wh_left      =  static_cast <double> (buffer [4]);
    }

void DataHandler::loadDriveControllerParams (uint8_t * buffer)
    {
    buffer [0] = tx_dc_throttle / 256;
    buffer [1] = tx_dc_throttle % 256;
    buffer [2] = static_cast <uint8_t> (tx_dc_mode);
    buffer [3] = tx_cont_last_trip;
    }
void DataHandler::loadLightControllerParams (uint8_t * buffer)
    {
    buffer [0] = static_cast <uint8_t> (tx_lc_lights_mode);
    buffer [1] = static_cast <uint8_t> (tx_lc_underlights);
    }
