
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ========== OLED SETTINGS ==========
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
#define OLED_ADDRESS  0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET
);

// ========== ESP32 PINS ==========
const int TOUCH_PIN = 4;
const int MY_BOOT_BUTTON_PIN = 0;
const int SDA_PIN = 21;
const int SCL_PIN = 22;

// ========== TIMING SETTINGS ==========
const unsigned long DOT_DASH_THRESHOLD = 250;
const unsigned long MIN_TOUCH_DURATION = 40;
const unsigned long LETTER_GAP = 700;
const unsigned long WORD_GAP = 1800;
const unsigned long DEBOUNCE_MS = 35;

// ========== MORSE INPUT STATE ==========
String morseBuffer = "";
String decodedText = "";

bool isTouching = false;
bool hasReleased = false;

unsigned long touchStartTime = 0;
unsigned long lastReleaseTime = 0;

// ========== BOOT BUTTON STATE ==========
bool lastButtonReading = HIGH;
bool buttonState = HIGH;
unsigned long lastButtonChangeTime = 0;

// ========== MORSE DECODER ==========
char decodeMorse(const String &code) {
  if (code == ".-")    return 'A';
  if (code == "-...")  return 'B';
  if (code == "-.-.")  return 'C';
  if (code == "-..")   return 'D';
  if (code == ".")     return 'E';
  if (code == "..-.")  return 'F';
  if (code == "--.")   return 'G';
  if (code == "....")  return 'H';
  if (code == "..")    return 'I';
  if (code == ".---")  return 'J';
  if (code == "-.-")   return 'K';
  if (code == ".-..")  return 'L';
  if (code == "--")    return 'M';
  if (code == "-.")    return 'N';
  if (code == "---")   return 'O';
  if (code == ".--.")  return 'P';
  if (code == "--.-")  return 'Q';
  if (code == ".-.")   return 'R';
  if (code == "...")   return 'S';
  if (code == "-")     return 'T';
  if (code == "..-")   return 'U';
  if (code == "...-")  return 'V';
  if (code == ".--")   return 'W';
  if (code == "-..-")  return 'X';
  if (code == "-.--")  return 'Y';
  if (code == "--..")  return 'Z';

  if (code == "-----") return '0';
  if (code == ".----") return '1';
  if (code == "..---") return '2';
  if (code == "...--") return '3';
  if (code == "....-") return '4';
  if (code == ".....") return '5';
  if (code == "-....") return '6';
  if (code == "--...") return '7';
  if (code == "---..") return '8';
  if (code == "----.") return '9';

  return '?';
}

// ========== OLED DISPLAY ==========
void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setTextWrap(false);

  const int charsPerLine = SCREEN_WIDTH / 6;
  const int visibleLines = SCREEN_HEIGHT / 8;

  int totalChars = decodedText.length();
  int totalLines =
      (totalChars + charsPerLine - 1) / charsPerLine;

  int firstLine = max(0, totalLines - visibleLines);

  for (int line = firstLine; line < totalLines; line++) {
    int start = line * charsPerLine;
    int count = min(charsPerLine, totalChars - start);

    display.setCursor(0, (line - firstLine) * 8);

    for (int i = 0; i < count; i++) {
      display.print(decodedText[start + i]);
    }
  }

  display.display();
}

// ========== BACKSPACE ==========
void backspace() {
  // If a Morse sequence is being entered, cancel it first.
  if (morseBuffer.length() > 0) {
    morseBuffer = "";
    Serial.println("\nPending Morse input cleared.");
    return;
  }

  if (decodedText.length() > 0) {
    decodedText.remove(decodedText.length() - 1);
    updateDisplay();

    Serial.println();
    Serial.print("Backspace. Current text: ");
    Serial.println(decodedText);
  } else {
    Serial.println("Nothing to delete.");
  }
}

// ========== BOOT BUTTON HANDLER ==========
void handleBootButton() {
  unsigned long now = millis();
  bool reading = digitalRead(MY_BOOT_BUTTON_PIN);

  if (reading != lastButtonReading) {
    lastButtonChangeTime = now;
    lastButtonReading = reading;
  }

  if (now - lastButtonChangeTime >= DEBOUNCE_MS) {
    if (reading != buttonState) {
      buttonState = reading;

      // Active LOW: one action per press.
      if (buttonState == LOW) {
        backspace();
      }
    }
  }
}

// ========== FINISH ONE LETTER ==========
void finishLetter() {
  if (morseBuffer.length() == 0) {
    return;
  }

  char letter = decodeMorse(morseBuffer);
  decodedText += letter;
  morseBuffer = "";

  if (decodedText.length() > 500) {
    decodedText.remove(0, decodedText.length() - 500);
  }

  Serial.print(letter);
  updateDisplay();
}

// ========== SETUP ==========
void setup() {
  Serial.begin(115200);

  pinMode(TOUCH_PIN, INPUT);
  pinMode(MY_BOOT_BUTTON_PIN, INPUT_PULLUP);

  Wire.begin(SDA_PIN, SCL_PIN);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("OLED initialization failed!");
    Serial.println("Check address, wiring and controller.");

    while (true) {
      delay(100);
    }
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Morse Reader");
  display.println("ESP32 Ready");
  display.println("BOOT = Backspace");
  display.display();

  delay(1200);

  decodedText = "";
  updateDisplay();

  Serial.println("Morse Reader Ready");
  Serial.println("Short touch = dot");
  Serial.println("Long touch = dash");
  Serial.println("BOOT button = Backspace");
}

// ========== MAIN LOOP ==========
void loop() {
  unsigned long now = millis();

  // Check BOOT button continuously.
  handleBootButton();

  bool touched = digitalRead(TOUCH_PIN) == HIGH;

  // Touch starts.
  if (touched && !isTouching) {
    if (hasReleased) {
      unsigned long gap = now - lastReleaseTime;

      if (gap >= WORD_GAP) {
        finishLetter();

        if (decodedText.length() > 0 &&
            decodedText.charAt(decodedText.length() - 1) != ' ') {
          decodedText += ' ';
          Serial.print(' ');
          updateDisplay();
        }
      } else if (gap >= LETTER_GAP) {
        finishLetter();
      }
    }

    isTouching = true;
    touchStartTime = now;
  }

  // Touch ends.
  if (!touched && isTouching) {
    unsigned long duration = now - touchStartTime;

    if (duration >= MIN_TOUCH_DURATION) {
      if (duration < DOT_DASH_THRESHOLD) {
        morseBuffer += '.';
      } else {
        morseBuffer += '-';
      }

      if (morseBuffer.length() > 5) {
        morseBuffer = "";
        Serial.println("\nSequence too long; cleared.");
      }
    }

    isTouching = false;
    hasReleased = true;
    lastReleaseTime = now;
  }

  // Automatically finish a letter after the idle gap.
  if (!isTouching && hasReleased &&
      morseBuffer.length() > 0 &&
      now - lastReleaseTime >= LETTER_GAP) {S
    finishLetter();
  }

  delay(5);
}
