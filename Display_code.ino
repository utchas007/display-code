#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN        2
#define COLOR_ORDER    GRB
#define CHIPSET        WS2812B
#define kMatrixWidth   16
#define kMatrixHeight  16
#define NUM_LEDS       ((kMatrixWidth) * (kMatrixHeight))
#define BRIGHTNESS     255

CRGB leds[NUM_LEDS];

// Matrix configuration and XY function
uint16_t XY(uint8_t x, uint8_t y) {
  if (x >= kMatrixWidth || y >= kMatrixHeight) return NUM_LEDS;
  return (y * kMatrixWidth) + x;  // Simple row-major layout
}

void setup() {
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(250000);
}

void loop() {
  FastLED.clear();
  
  // Display text: "I N O R I Z O N"
  displayText("INORIZON", 0, 1, CRGB::Blue);

  // Display a drone as a shape (represent it in dots)
  displayDrone(5, 5, CRGB::White);  // Example position for the drone

  // Display a robot as a shape (represent it in dots)
  displayRobot(9, 10, CRGB::Green); // Example position for the robot

  // Display "A I" below the drone and robot
  displayText("A I", 12, 12, CRGB::Red);

  FastLED.show();
  delay(1000);  // Control frame rate
}

// Function to display text (basic 5x7 font representation)
void displayText(const char* text, uint8_t xOffset, uint8_t yOffset, CRGB color) {
  // Use a very simple character mapping for this example
  while (*text) {
    char c = *text++;
    // Map character to dots (5x7 font), implement a font map function
    drawCharacter(c, xOffset, yOffset, color);
    xOffset += 6;  // Move to next character position
  }
}

// Function to draw a character (simple 5x7 bitmap)
void drawCharacter(char c, uint8_t x, uint8_t y, CRGB color) {
  // Implement a small font table for "I N O R I Z O N" and "A I"
  static const uint8_t font[7] = {
    // Example bitmap for letter I (5x7 matrix)
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00000,
    0b00100,
  };
  for (int i = 0; i < 7; i++) {
    uint8_t line = font[i];
    for (int j = 0; j < 5; j++) {
      if (line & (1 << j)) {
        leds[XY(x + j, y + i)] = color;
      }
    }
  }
}

// Function to display the drone (custom shape in dots)
void displayDrone(uint8_t x, uint8_t y, CRGB color) {
  // Define the drone shape as a 5x5 or similar bitmap
  static const uint8_t droneShape[5] = {
    0b00100,  // Example drone shape (you need to refine it)
    0b01110,
    0b11111,
    0b01110,
    0b00100,
  };
  for (int i = 0; i < 5; i++) {
    uint8_t line = droneShape[i];
    for (int j = 0; j < 5; j++) {
      if (line & (1 << j)) {
        leds[XY(x + j, y + i)] = color;
      }
    }
  }
}

// Function to display the robot (custom shape in dots)
void displayRobot(uint8_t x, uint8_t y, CRGB color) {
  // Define the robot shape as a 5x5 or similar bitmap
  static const uint8_t robotShape[5] = {
    0b01110,  // Example robot shape (you need to refine it)
    0b10101,
    0b11111,
    0b10101,
    0b10101,
  };
  for (int i = 0; i < 5; i++) {
    uint8_t line = robotShape[i];
    for (int j = 0; j < 5; j++) {
      if (line & (1 << j)) {
        leds[XY(x + j, y + i)] = color;
      }
    }
  }
}
