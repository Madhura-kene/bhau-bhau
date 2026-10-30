ESP32 Morse Code Reader

An ESP32-based Morse Code Reader that converts touch inputs into readable text using a capacitive touch sensor. The system identifies dots (".") and dashes ("-") based on touch duration, automatically decodes Morse sequences into letters and numbers, and displays the decoded message on an OLED screen.

It also features automatic letter and word separation, live text display, and a BOOT button for deleting characters.

Features

- Touch-Based Morse Input: Use a capacitive touch sensor to enter Morse code.
- Automatic Dot and Dash Detection: Short touches generate dots ("."), while long touches generate dashes ("-").
- Automatic Letter Separation: Detects pauses between Morse sequences to identify individual characters.
- Automatic Word Separation: Detects longer pauses to insert spaces between words.
- OLED Display: Displays decoded messages on a 128×32 SSD1306 OLED.
- Backspace Functionality: Use the ESP32 BOOT button to delete the last character.
- Pending Input Cancellation: Pressing BOOT while entering a Morse sequence clears the pending sequence first.
- Serial Monitor Output: Displays decoded characters and debugging information.
- Scrolling Text: Automatically displays the latest text when the message exceeds the OLED screen capacity.
- Alphabet and Number Support: Supports A–Z and 0–9.

Components Required

Component| Quantity
ESP32 Development Board| 1
TTP223 Capacitive Touch Sensor| 1
0.91-inch OLED Display (128×32, SSD1306)| 1
Jumper Wires| As required
Breadboard| 1 (Optional)

Circuit Connections

1. TTP223 Touch Sensor

TTP223 Pin| ESP32 Pin
VCC| 3.3V
GND| GND
OUT| GPIO 4

2. OLED Display (I2C)

OLED Pin| ESP32 Pin
VCC| 3.3V
GND| GND
SDA| GPIO 21
SCL| GPIO 22

3. BOOT Button

The ESP32's onboard BOOT button is used for backspace functionality.

Component| ESP32 Pin
BOOT Button| GPIO 0

Note: The BOOT button is generally active LOW and uses the ESP32's internal pull-up configuration.

Working Principle

The system uses touch duration and idle time to interpret Morse code.

1. Dot and Dash Detection

The duration of each touch determines whether the input is a dot or a dash.

Touch Duration| Morse Symbol
40–249 ms| Dot (".")
250 ms or more| Dash ("-")
Less than 40 ms| Ignored

2. Letter Separation

When the user stops touching the sensor, the system measures the idle duration.

- A pause of 700 ms completes the current Morse letter.
- A pause of 1800 ms completes the current letter and inserts a space between words.

3. Morse Decoding

The collected Morse sequence is matched against predefined Morse code combinations.

For example:

Character| Morse Code
A| ".-"
B| "-..."
C| "-.-."
D| "-.."
E| "."
S| "..."
O| "---"
1| ".----"
2| "..---"
3| "...--"

4. OLED Display

Once a letter is decoded, it is appended to the output text and displayed on the OLED.

The display automatically updates to show the latest portion of the decoded message.

5. Backspace

Pressing the ESP32 BOOT button performs one of two actions:

- If a Morse sequence is currently being entered, it clears that pending sequence.
- Otherwise, it deletes the last decoded character.

Software Requirements

- Arduino IDE
- ESP32 Board Package
- Adafruit GFX Library
- Adafruit SSD1306 Library

Required Libraries

Install the following libraries through Arduino IDE:

1. Adafruit GFX Library
2. Adafruit SSD1306

The "Wire.h" library is included with the Arduino framework.

Installation and Setup

1. Clone or download this repository.
   
   git clone <YOUR_GITHUB_REPOSITORY_URL>

2. Open the project folder.

3. Open the ".ino" file in Arduino IDE.

4. Install the required libraries.

5. Select your ESP32 board under Tools → Board.

6. Select the correct COM port under Tools → Port.

7. Connect the OLED display and TTP223 sensor according to the wiring table.

8. Upload the code to your ESP32.

9. Open the Serial Monitor and set the baud rate to 115200.

10. Start entering Morse code using the touch sensor.

Configuration

The following parameters can be modified in the source code:

Parameter| Default Value| Description
"DOT_DASH_THRESHOLD"| 250 ms| Separates dots and dashes
"MIN_TOUCH_DURATION"| 40 ms| Minimum valid touch duration
"LETTER_GAP"| 700 ms| Idle time required to finish a letter
"WORD_GAP"| 1800 ms| Idle time required to insert a word space
"DEBOUNCE_MS"| 35 ms| BOOT button debounce interval
"OLED_ADDRESS"| "0x3C"| OLED I2C address
"SCREEN_WIDTH"| 128| OLED display width
"SCREEN_HEIGHT"| 32| OLED display height

How to Use

1. Power on the ESP32.
2. Wait for the OLED to display the startup message.
3. Touch and release the TTP223 sensor.
4. Use short touches for dots (".").
5. Use long touches for dashes ("-").
6. Wait approximately 700 ms to finish a letter.
7. Wait approximately 1800 ms to insert a space.
8. Press the ESP32 BOOT button to delete the last character or clear the pending Morse sequence.

Example

To enter the word SOS:

Letter| Morse Input
S| "..."
O| "---"
S| "..."

The OLED displays:

SOS

Limitations

- The current implementation supports English alphabets (A–Z) and numbers (0–9).
- Special characters and punctuation are not implemented.
- Touch sensitivity depends on the sensor and user input.
- Morse timing thresholds may require adjustment for different users.
- The OLED displays only the latest portion of longer messages.
- The decoded text buffer retains a maximum of 500 characters.

Future Improvements

- Add support for special characters and punctuation.
- Implement adjustable Morse timing through buttons or menus.
- Add a buzzer for audio feedback.
- Add an option to clear the entire decoded message.
- Implement Bluetooth-based message transmission.
- Add multilingual Morse decoding support.

Technologies Used

- ESP32
- Arduino C++
- TTP223 Capacitive Touch Sensor
- SSD1306 OLED Display
- I2C Communication
- Morse Code Encoding and Decoding

License

This project is open-source and available for educational and personal use.

---

Built with ESP32, Arduino C++, and a little Morse Code magic.