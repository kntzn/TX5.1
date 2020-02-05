# TX5.1
Firmware for esk8 TX unit HW5.0 FW5.1

# Features
## Communication

- COBS-package-based communication
- Request-based data transmission to the remote
- Rawinput mode
- Failsafe

## Initial screen
- Startup logo
- Continue last trip

## Main screen

### Button assignment
- Light modes (Button "Up" goes to next, Hold turns off)
  - Off
  - Rear only
  - Rear+front
  - Auto 

- Main menu (middle button)

- Multiple ride modes (Button "Down" goes to next, Hold goes to previous)
  - Lock
  - Hybrid (or Neutral)
  - Eco
  - Cruise 
  - Sport

- Cruise control (Hold button "Down")

### Display
- Connection quality
- Lights mode
- TX battery volatge
  - Frequent updates with fast exp. filter smoothing
- Speedometer
- Mode
- Left disance approximation
- RX battery percents
- Odometer
- Current trip

## Main menu
### Button assignment
- Button "Up" - previous selection
- Button "Down" - next selection
- Button "Mid" - select
- Hold button "Mid" or wait for 10 seconds - return to the main screen

### Options
1. Underlights
2. Benchmark mode
3. BMS
    - Battery voltage
    - Battery consumption
4. Trip controller (*may be added in future*)
    - Graphs of the trip's parameters

## LEDS

- TX led
  - #00F - >3.8v
  - #0FF - >3.7v
  - #F00 - <=3.7v
- RX led
  - #F0F - NC
  - #0FF - >50%
  - #0F0 - >25%
  - #FF0 - >10%
  - #F00 - <=10%
