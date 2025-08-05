# arduino-security-system
A simple Arduino security system that uses a laser and light sensor to spot intruders and sound an alarm

  ![Arduino Side View](https://raw.githubusercontent.com/adrirubio/arduino-security-system/main/my-build/arduino-side-view.jpeg)

## Demo & Full Video
Watch a quick preview below (GIF), or download the full demo video

### Preview (GIF)
![Arduino Security System](https://github.com/adrirubio/arduino-security-system/raw/main/my-build/demos/arduino-security-system-demo.gif)

### Full Video
[Click here to download the full demo video (MP4)](https://github.com/adrirubio/arduino-security-system/raw/main/my-build/demos/arduino-security-system-demo.mp4)

## How It Works

The security system monitors a laser beam using a light sensor. When the beam is broken, it triggers an alarm sound using a buzzer and turns a red LED on. The system can be armed/disarmed/shut down using a pushbutton with visual and audio feedback.

## Components Used

- Arduino Board (Uno R3 in my build)
- Laser module
- Laser receiver
- 3 colored LEDs (green, red, and yellow)
- 1 pushbutton
- Resistors and wiring
- 1 piezo buzzer

## Repo Structure

- `firmware/arduino-security-system/arduino-security-system.ino` - Main Arduino code for real hardware
- `firmware/tinkercad-security-system/tinkercad-security-system.ino` - Modified code for Tinkercad simulation
- `firmware/buzzer-tests/buzzer-tests.ino` - Code to test different buzzer tunes
- `docs` - Documentation including hardware differences
- `my-build/` - Build photos and demos

## Features

- Laser beam intrusion detection
- Armed/Disarmed states with LED indicators
- Audio feedback with different tones for each state
- LED feedback for each state

## Quick Start

1. **Clone this repository**
   ```bash
   git clone https://github.com/adrirubio/arduino-security-system.git
   ```

2. **Open the Arduino sketch**
   - For real hardware: Open `firmware/arduino-security-system/arduino-security-system.ino`
   - For Tinkercad: Open `firmware/tinkercad-security-system/tinkercad-security-system.ino`

3. **Wire your components**
   - Find information inside `docs/`
   - See `docs/hardware-files.md` for detailed wiring differences

4. **Upload and Use!**
   - Upload the sketch to your Arduino
   - And... catch any intruders


## Extra Screenshot

Top view of the project:

![Arduino Top View](https://raw.githubusercontent.com/adrirubio/arduino-security-system/main/my-build/arduino-top-view.jpeg)
