
# Automatic Lid Opening System Using Arduino and Ultrasonic Sensor

An Arduino-based touchless lid mechanism that uses an HC-SR04 ultrasonic sensor to detect nearby objects and control a servo motor. The lid opens when an object approaches and remains open while the object stays within the detection range. Once the object moves away, the lid closes automatically.

## Features

- Touchless object detection
- Automatic lid opening and closing
- Continuous distance monitoring
- Adjustable detection threshold
- Real-time distance readings through the Serial Monitor
- Low-cost and beginner-friendly hardware

## Components Required

| Component | Quantity |
|---|---:|
| Arduino Uno | 1 |
| HC-SR04 Ultrasonic Sensor | 1 |
| SG90 Servo Motor or compatible servo | 1 |
| Jumper Wires | As required |
| USB Cable | 1 |
| Lid and Mounting Mechanism | 1 |

## Circuit Connections

### HC-SR04 Ultrasonic Sensor

| Sensor Pin | Arduino Uno |
|---|---|
| VCC | 5V |
| GND | GND |
| TRIG | Digital Pin 9 |
| ECHO | Digital Pin 10 |

### Servo Motor

| Servo Wire | Arduino Uno |
|---|---|
| Signal (Orange/Yellow) | Digital Pin 6 |
| Power (Red) | 5V supply |
| Ground (Brown/Black) | GND |

> **Note:** If the servo causes the Arduino to reset or behave erratically, use a suitable external regulated 5V supply. Connect the external supply's GND to Arduino GND.

## Working Principle

1. The HC-SR04 sensor emits ultrasonic pulses.
2. The sensor measures the time taken for the echo to return.
3. The Arduino calculates the distance to the detected object.
4. If an object is detected within 15 cm, the servo moves to 0 degrees to open the lid.
5. The lid stays open while an object remains within the detection range.
6. When the object moves beyond 15 cm or no echo is received, the servo moves to 100 degrees to close the lid.

The actual opening and closing directions depend on the servo mounting.

## Software Requirements

- Arduino IDE
- Arduino Uno
- Arduino Servo library

## Installation and Setup

1. Install the Arduino IDE.
2. Connect the Arduino Uno to your computer using USB.
3. Wire the ultrasonic sensor and servo according to the connection tables.
4. Open the Arduino sketch containing the project code.
5. Select **Tools > Board > Arduino Uno**.
6. Select the correct port under **Tools > Port**.
7. Upload the code.
8. Open the Serial Monitor and set the baud rate to `9600`.
9. Move an object in front of the sensor to test the system.

## Configuration

The following values can be adjusted in the Arduino code:

| Parameter | Default Value | Description |
|---|---:|---|
| Detection Distance | 15 cm | Distance threshold for opening the lid |
| Open Position | 0 degrees | Servo angle when the lid is open |
| Closed Position | 100 degrees | Servo angle when the lid is closed |
| Serial Baud Rate | 9600 | Serial Monitor communication speed |

## Troubleshooting

### Servo Not Moving
- Check the signal connection to pin 6.
- Verify the servo power and ground connections.
- Test the servo independently.
- Check whether an external power supply is required.

### Ultrasonic Sensor Not Working
- Verify VCC, GND, TRIG, and ECHO connections.
- Check the Serial Monitor for distance readings.
- Ensure the sensor faces the object directly.
- Inspect the jumper wires for loose connections.

### Lid Moving in the Wrong Direction
Adjust the servo angles to match the physical mounting of the lid mechanism.

### Arduino Resetting or Servo Jittering
Use an appropriate regulated power supply for the servo and connect all grounds together.

## Applications

- Touchless dustbins
- Automatic storage containers
- Smart-box prototypes
- Household automation
- Embedded systems learning projects

## Future Improvements

- Add an LED or buzzer to indicate lid status.
- Implement a manual override button.
- Add distance filtering to reduce false detections.
- Improve obstruction detection and closing safety.
- Add adjustable detection settings.

## Project Information

- **Platform:** Arduino Uno
- **Programming Language:** Arduino C++
- **Sensors:** HC-SR04 Ultrasonic Sensor
- **Actuator:** Servo Motor
- **Project Status:** Prototype

## License

This project can be released under the MIT License. Include a `LICENSE` file with the appropriate license text if you choose to use it.
