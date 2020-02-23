// 
// 
// 

#include "LedStateIndicator.h"

#include "Config.h"

void LedStateIndicator::showColorTx (bool r, bool g, bool b)
    {
    digitalWrite (tx_r, r);
    digitalWrite (tx_g, g);
    digitalWrite (tx_b, b);
    }
void LedStateIndicator::showColorRx (bool r, bool g, bool b)
    {
    digitalWrite (rx_r, r);
    digitalWrite (rx_g, g);
    digitalWrite (rx_b, b);
    }

LedStateIndicator::LedStateIndicator (uint8_t tx_r, uint8_t tx_g, uint8_t tx_b,
                                      uint8_t rx_r, uint8_t rx_g, uint8_t rx_b):
    tx_r (tx_r), tx_g (tx_g), tx_b (tx_b),
    rx_r (rx_r), rx_g (rx_g), rx_b (rx_b)
    {
    }

void LedStateIndicator::update (double voltage, double percents)
    {
    // TX
    if (voltage > LSI_TX_BLUE)
        showColorTx (0, 0, 1);
    else if (voltage > LSI_TX_LBLU)
        showColorTx (0, 1, 1);
    else if (voltage > LSI_TX_YEL)
        showColorTx (1, 1, 0);
    else
        showColorTx (1, 0, 0);
        
    // RX
    if (percents < LSI_RX_NC)
        showColorRx (1, 0, 1);
    else if (percents < LSI_RX_RED)
        showColorRx (1, 0, 0);
    else if (percents < LSI_RX_YEL)
        showColorRx (1, 1, 0);
    else if (percents < LSI_RX_GRN)
        showColorRx (0, 1, 0);
    else
        showColorRx (0, 1, 1);
    }
