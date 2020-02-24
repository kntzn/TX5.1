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
    tx_dc_mode (mode_selected), tx_dc_throttle (0),
    tx_lc_lights_mode (l_mode_selected), tx_lc_underlights (ul_active)
    {
    }
