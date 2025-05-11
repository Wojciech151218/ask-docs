#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS  8

#define DATA_PIN    4
#define SENSOR_PIN  3

#define ASCII_START 'A'
#define ASCII_END   'Z'

Adafruit_NeoPixel strip(NUM_PIXELS, DATA_PIN, NEO_GRB + NEO_KHZ800);

const int charHeight = 8;
const int charWidth = 5;

const unsigned char font[ASCII_END - ASCII_START + 1][5] = {
  {0x7E,0x11,0x11,0x11,0x7E}, // 'A'
  {0x7F,0x49,0x49,0x49,0x36}, // 'B'
  {0x3E,0x41,0x41,0x41,0x22}, // 'C'
  {0x7F,0x41,0x41,0x22,0x1C}, // 'D'
  {0x7F,0x49,0x49,0x49,0x41}, // 'E'
  {0x7F,0x09,0x09,0x09,0x01}, // 'F'
  {0x3E,0x41,0x49,0x49,0x7A}, // 'G'
  {0x7F,0x08,0x08,0x08,0x7F}, // 'H'
  {0x00,0x41,0x7F,0x41,0x00}, // 'I'
  {0x20,0x40,0x41,0x3F,0x01}, // 'J'  
  {0x7F,0x08,0x14,0x22,0x41}, // 'K'
  {0x7F,0x40,0x40,0x40,0x40}, // 'L'
  {0x7F,0x02,0x0C,0x02,0x7F}, // 'M'
  {0x7F,0x04,0x08,0x10,0x7F}, // 'N'
  {0x3E,0x41,0x41,0x41,0x3E}, // 'O'
  {0x7F,0x09,0x09,0x09,0x06}, // 'P'
  {0x3E,0x41,0x51,0x21,0x5E}, // 'Q'
  {0x7F,0x09,0x19,0x29,0x46}, // 'R'
  {0x46,0x49,0x49,0x49,0x31}, // 'S'
  {0x01,0x01,0x7F,0x01,0x01}, // 'T'
  {0x3F,0x40,0x40,0x40,0x3F}, // 'U'
  {0x1F,0x20,0x40,0x20,0x1F}, // 'V'
  {0x7F,0x20,0x18,0x20,0x7F}, // 'W'
  {0x63,0x14,0x08,0x14,0x63}, // 'X'
  {0x07,0x08,0x70,0x08,0x07}, // 'Y'
  {0x61,0x51,0x49,0x45,0x43}, // 'Z'
};


void setup() {
  pinMode(SENSOR_PIN, INPUT);
  strip.begin();
  strip.show(); // Wyłącz diody
}

void loop() {
  // Czekaj aż czujnik zostanie aktywowany
  while (digitalRead(SENSOR_PIN) != HIGH) {
    strip.clear();
    strip.show();
  }

  displayText("HELLO");
}

// Funkcja wyświetlająca kolumnę znaku
void displayColumn(byte column, bool flipped = false) {
  strip.clear();
  for (int i = 0; i < charHeight; i++) {
    bool pixelOn = bitRead(column, flipped ? i : (7 - i));
    if (pixelOn) {
      strip.setPixelColor(i, strip.Color(0, 150, 0));
    }
  }
  strip.show();
  delayMicroseconds(750); 
}

// Wyświetla literę normalnie
void displayLetter(char ch) {
  if (ch == 'A') {
    for (int i = 0; i < charWidth; i++) {
      displayColumn(font[1][i], false);  // A to font[1]
    }
  }
}

// Wyświetla literę odwróconą
void displayLetterFlipped(char ch) {
  if (ch == 'B') {
    for (int i = charWidth - 1; i >= 0; i--) {
      displayColumn(font[2][i], true);   // B to font[2]
    }
  }
}

void displayText(const char* text) {
  for (int i = 0; i < strlen(text); i++) {
    char ch = text[i];
    if (ch >= ASCII_START && ch <= ASCII_END) { // Zakres fontu ASCII
      for (int j = 0; j < charWidth; j++) {
        displayColumn(font[ch - ASCII_START][j]);
      }
      displayColumn(0x00); // odstęp między literami
    }
  }
}
void displayTextFlipped(const char* text) {
  for (int i = strlen(text) - 1; i>= 0; i--) {
    char ch = text[i];
    if (ch >= ASCII_START && ch <= ASCII_END) { // Zakres fontu ASCII
      for (int j = charWidth-1; j >= 0; j--) {
        displayColumn(font[ch - ASCII_START][j], true);
      }
      displayColumn(0x00); // odstęp między literami
    }
  }
}