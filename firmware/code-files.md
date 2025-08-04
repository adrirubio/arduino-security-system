# Why Two Arduino Files?

This project has two versions of the security system code because they use different sensors:

## 1. arduino-security-system.ino (Real Hardware)
- Uses a **laser receiver** connected to pin 7
- Detects when a laser beam is broken (outputs HIGH when interrupted)
- Designed for actual Arduino hardware with real laser components
- Alarm runs for 5 seconds after trigger, then automatically resets

## 2. tinkercad-security-system.ino (Simulation)
- Uses a **photoresistor** connected to analog pin A0
- Detects light changes (triggers when value drops below 700)
- Works in Tinkercad simulator which doesn't have laser components
- Alarm continues until light is detected

## Key Differences

### Sensors
- **Real**: Digital laser receiver (ON/OFF detection)
- **Tinkercad**: Analog photoresistor (light level measurements)

### LED Pin Assignments
- **Real**: Green=6, Red=5, Yellow=4
- **Tinkercad**: Green=4, Red=5, Yellow=6

### Alert Behaviour
- **Real**: 5-second timed alarm
- **Tinkercad**: Alarm until light restored

Both versions share the same:
- State system (disarmed/armed/alert)
- Button controls (press to arm, hold to disarm)
- Sound effects (startup, shutdown, alert tones)
- Overall security logic

The dual approach lets you test the system in Tinkercad's simulator before building the security system!
