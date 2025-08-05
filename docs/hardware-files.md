# Hardware Differences: Arduino vs Tinkercad

This markdown file outlines the hardware differences between the real Arduino implementation and the Tinkercad simulation.

## Components Differences

### Sensors
- **Arduino**: Laser receiver module (digital sensor)
- **Tinkercad**: Photoresistor with 10 kohm pulldown resistor (analog sensor)

### Pin Connections
- **Arduino**: Laser receiver - Pin 7 (digital)
- **Tinkercad**: Photoresistor - Pin A0 (analog)

### LED Wiring
Both use the same color LEDs but in different pins
- **Arduino**: Green (6), Red (5), Yellow (4)
- **Tinkercad**: Green (4), Red (5), Yellow (6)

## Circuit Design

The Tinkercad version uses a photoresistor because the simulator doesn't have laser components.

Both circuits include:
- Push button on pin 2 with internal pullup
- Buzzer on pin 8
- 220 ohm resistors for all LEDs
- Common ground connections

The hardware differences are minimal and a result of the components available in each environment.
