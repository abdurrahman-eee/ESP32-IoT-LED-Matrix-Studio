#include <Arduino.h>

// =====================================================
//  ESP32 + 74HC595 + 8×8 LED MATRIX
//  SHAPE GALLERY DEMO
//
//  - Cute / emoji
//  - Geometric
//  - Mechanical
//  - Retro game
//  - Islamic patterns
//  - Math / fractal-like
// =====================================================

// ---------------- PIN SETUP ----------------
// Change these if you wire to different GPIOs
const int latchPin = 2;   // ST_CP of 74HC595
const int clockPin = 4;   // SH_CP of 74HC595
const int dataPin  = 15;  // DS   of 74HC595

// =====================================================
//  LOW-LEVEL HELPERS
//  Assumes 2×74HC595 chained:
//    - First for ROW data
//    - Second for COLUMN select (active LOW)
// =====================================================

void sendRow(uint8_t value)
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, value);
  digitalWrite(latchPin, HIGH);
}

void sendCol(uint8_t value)
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, value);
  digitalWrite(latchPin, HIGH);
}

void clearMatrix()
{
  sendRow(0x00);  // all rows OFF
  sendCol(0xFF);  // all columns inactive (HIGH)
}

// =====================================================
//  BASIC DISPLAY ROUTINE
// =====================================================

// Show one 8×8 pattern for `ms` with fast multiplexing.
// Pattern is 8 columns; each uint8_t bit = LED ON/OFF in that column.
void showPattern(const uint8_t pat[8], unsigned long ms)
{
  unsigned long t0 = millis();
  while (millis() - t0 < ms)
  {
    uint8_t colMask = 1;

    for (int c = 0; c < 8; c++)
    {
      uint8_t rows = pat[c];   // which rows ON in this column

      sendRow(rows);           // row data
      sendCol(~colMask);       // select this column (active LOW)

      // Short delay → high refresh → looks continuously ON
      delayMicroseconds(120);

      colMask <<= 1;
    }
  }
}

// Small blank between shapes (for clean separation)
void showBlank(unsigned long ms)
{
  clearMatrix();
  delay(ms);
}

// =====================================================
//  SHAPES (8×8, COLUMN-WISE, ONLY 0/1 BITS)
// =====================================================
//
// NOTE: Each shape is 8 columns (index 0..7).
//       You already have working orientation; these match that style.
//
// -----------------------------------------------------
// 💡 Cute / fun / emoji
// -----------------------------------------------------

// Smiley 🙂
const uint8_t SH_EMOJI_SMILE[8] = {
  0b00111100,
  0b01000010,
  0b10100101,
  0b10000001,
  0b10100101,
  0b10011001,
  0b01000010,
  0b00111100
};

// Wink 😉
const uint8_t SH_EMOJI_WINK[8] = {
  0b00111100,
  0b01000010,
  0b10100101,
  0b10000001,
  0b10111101,
  0b10011001,
  0b01000000,
  0b00111100
};

// Big happy smile 😄
const uint8_t SH_EMOJI_BIG_SMILE[8] = {
  0b00111100,
  0b01000010,
  0b10100101,
  0b10000001,
  0b10111101,
  0b10011001,
  0b01000010,
  0b00111100
};

// Sad ☹️
const uint8_t SH_EMOJI_SAD[8] = {
  0b00111100,
  0b01000010,
  0b10100101,
  0b10000001,
  0b10011001,
  0b10111101,
  0b01000010,
  0b00111100
};

// Surprised 😮
const uint8_t SH_EMOJI_SURPRISED[8] = {
  0b00111100,
  0b01000010,
  0b10100101,
  0b10000001,
  0b10011001,
  0b10011001,
  0b01000010,
  0b00111100
};

// -----------------------------------------------------
// 🧭 Technical / geometric
// -----------------------------------------------------

// Circle
const uint8_t SH_GEO_CIRCLE[8] = {
  0b00111100,
  0b01111110,
  0b11100111,
  0b11000011,
  0b11000011,
  0b11100111,
  0b01111110,
  0b00111100
};

// Diamond
const uint8_t SH_GEO_DIAMOND[8] = {
  0b00011000,
  0b00111100,
  0b01111110,
  0b11111111,
  0b01111110,
  0b00111100,
  0b00011000,
  0b00000000
};

// Hollow square
const uint8_t SH_GEO_SQUARE_HOLLOW[8] = {
  0b11111111,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b10000001,
  0b11111111
};

// Solid square
const uint8_t SH_GEO_SQUARE_SOLID[8] = {
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111,
  0b11111111
};

// X shape
const uint8_t SH_GEO_X[8] = {
  0b10000001,
  0b01000010,
  0b00100100,
  0b00011000,
  0b00011000,
  0b00100100,
  0b01000010,
  0b10000001
};

// Arrow →
const uint8_t SH_GEO_ARROW_RIGHT[8] = {
  0b00001000,
  0b00001100,
  0b11111110,
  0b11111111,
  0b11111110,
  0b00001100,
  0b00001000,
  0b00000000
};

// Arrow ←
const uint8_t SH_GEO_ARROW_LEFT[8] = {
  0b00010000,
  0b00110000,
  0b01111111,
  0b11111111,
  0b01111111,
  0b00110000,
  0b00010000,
  0b00000000
};

// -----------------------------------------------------
// ⚙️ Mechanical look
// -----------------------------------------------------

// Gear-like
const uint8_t SH_MECH_GEAR[8] = {
  0b00111100,
  0b01111110,
  0b11011011,
  0b11111111,
  0b11111111,
  0b11011011,
  0b01111110,
  0b00111100
};

// Piston / actuator
const uint8_t SH_MECH_PISTON[8] = {
  0b00011000,
  0b00011000,
  0b00111100,
  0b01111110,
  0b00111100,
  0b00011000,
  0b00011000,
  0b00011000
};

// Hex / nut shape
const uint8_t SH_MECH_HEX[8] = {
  0b00111100,
  0b01100110,
  0b11000011,
  0b11000011,
  0b11000011,
  0b11000011,
  0b01100110,
  0b00111100
};

// Fan / turbine
const uint8_t SH_MECH_FAN[8] = {
  0b00011000,
  0b00111100,
  0b01111110,
  0b11111111,
  0b01111110,
  0b00111100,
  0b00011000,
  0b00000000
};

// -----------------------------------------------------
// 🎮 Retro game style
// -----------------------------------------------------

// Space-invader style alien
const uint8_t SH_RETRO_INVADER[8] = {
  0b00111100,
  0b01111110,
  0b11111111,
  0b10111101,
  0b11111111,
  0b01100110,
  0b11000011,
  0b10000001
};

// Player ship
const uint8_t SH_RETRO_SHIP[8] = {
  0b00011000,
  0b00011100,
  0b00111110,
  0b01111111,
  0b01111111,
  0b00111110,
  0b00011100,
  0b00011000
};

// Pixel heart (game style)
const uint8_t SH_RETRO_HEART[8] = {
  0b00000000,
  0b01100110,
  0b11111111,
  0b11111111,
  0b11111111,
  0b01111110,
  0b00111100,
  0b00011000
};

// Small alien variant
const uint8_t SH_RETRO_ALIEN_SMALL[8] = {
  0b00111100,
  0b01111110,
  0b01011010,
  0b11111111,
  0b10111101,
  0b00100100,
  0b01000010,
  0b10000001
};

// -----------------------------------------------------
// ❤️ Islamic art style
// -----------------------------------------------------

// 8-point star / rosette
const uint8_t SH_ISLAMIC_STAR[8] = {
  0b00011000,
  0b00111100,
  0b01111110,
  0b11111111,
  0b01111110,
  0b00111100,
  0b00011000,
  0b00000000
};

// Simple repeating tile pattern
const uint8_t SH_ISLAMIC_TILE[8] = {
  0b10100101,
  0b01011010,
  0b10100101,
  0b01011010,
  0b10100101,
  0b01011010,
  0b10100101,
  0b01011010
};

// Star inside border
const uint8_t SH_ISLAMIC_STAR_IN_BOX[8] = {
  0b11111111,
  0b10111101,
  0b01011010,
  0b11100111,
  0b11100111,
  0b01011010,
  0b10111101,
  0b11111111
};

// Grid / kufic-feel pattern
const uint8_t SH_ISLAMIC_GRID[8] = {
  0b11101110,
  0b10001000,
  0b11101110,
  0b00000000,
  0b11101110,
  0b10001000,
  0b11101110,
  0b00000000
};

// -----------------------------------------------------
// 🧠 Math / fractal-like
// -----------------------------------------------------

// Checkerboard
const uint8_t SH_MATH_CHECKER[8] = {
  0b10101010,
  0b01010101,
  0b10101010,
  0b01010101,
  0b10101010,
  0b01010101,
  0b10101010,
  0b01010101
};

// Small Sierpinski-like triangle
const uint8_t SH_MATH_SIERPINSKI[8] = {
  0b00010000,
  0b00101000,
  0b01000100,
  0b10101010,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000
};

// Diagonal stripe
const uint8_t SH_MATH_DIAGONAL[8] = {
  0b10000000,
  0b01000000,
  0b00100000,
  0b00010000,
  0b00001000,
  0b00000100,
  0b00000010,
  0b00000001
};

// Equalizer / bar graph
const uint8_t SH_MATH_EQUALIZER[8] = {
  0b00011000,
  0b00011000,
  0b00111100,
  0b00111100,
  0b01111110,
  0b01111110,
  0b11111111,
  0b11111111
};

// =====================================================
//  SHAPE LIST (for auto-cycling demo)
// =====================================================

const uint8_t* ALL_SHAPES[] = {
  // Cute / emoji
  SH_EMOJI_SMILE,
  SH_EMOJI_WINK,
  SH_EMOJI_BIG_SMILE,
  SH_EMOJI_SAD,
  SH_EMOJI_SURPRISED,

  // Geometric
  SH_GEO_CIRCLE,
  SH_GEO_DIAMOND,
  SH_GEO_SQUARE_HOLLOW,
  SH_GEO_SQUARE_SOLID,
  SH_GEO_X,
  SH_GEO_ARROW_RIGHT,
  SH_GEO_ARROW_LEFT,

  // Mechanical
  SH_MECH_GEAR,
  SH_MECH_PISTON,
  SH_MECH_HEX,
  SH_MECH_FAN,

  // Retro game
  SH_RETRO_INVADER,
  SH_RETRO_SHIP,
  SH_RETRO_HEART,
  SH_RETRO_ALIEN_SMALL,

  // Islamic
  SH_ISLAMIC_STAR,
  SH_ISLAMIC_TILE,
  SH_ISLAMIC_STAR_IN_BOX,
  SH_ISLAMIC_GRID,

  // Math / fractal-like
  SH_MATH_CHECKER,
  SH_MATH_SIERPINSKI,
  SH_MATH_DIAGONAL,
  SH_MATH_EQUALIZER
};

const int NUM_SHAPES = sizeof(ALL_SHAPES) / sizeof(ALL_SHAPES[0]);

// =====================================================
//  SETUP / LOOP
// =====================================================

void setup()
{
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin,  OUTPUT);

  clearMatrix();

  // Power-on test: all LEDs ON briefly
  sendRow(0xFF);   // all rows ON
  sendCol(0x00);   // all columns active (LOW)
  delay(700);
  clearMatrix();
}

void loop()
{
  // Cycle through all shapes forever
  for (int i = 0; i < NUM_SHAPES; i++)
  {
    showPattern(ALL_SHAPES[i], 800); // show each shape ~0.8s
    showBlank(120);                  // small gap between shapes
  }
}
