#include <Adafruit_NeoPixel.h>
int i = 0;
int j = 0;
int mode = 1;
bool buttonState = false;
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, 6, NEO_GRB + NEO_KHZ800);


void setup() {
  pinMode(10, INPUT);
  strip.begin();
  strip.show();
}

void checkButton() {
  buttonState = digitalRead(10);

  /*if (buttonState == HIGH) {
    if (mode <= 6) {
      mode ++;
    } else {
      mode = 1;
    }
    }*/
}

uint32_t Wheel(uint8_t WheelPos, uint8_t b) {
  if (b < 1) {
    b = 1;
  }
  if (b > 128) {
    b = 128;
  }
  WheelPos = 255 - WheelPos;
  if (WheelPos == 255) {
    return strip.Color(0, 0, 0);
  }
  if (WheelPos == 0) {
    return strip.Color(255 / b, 255 / b, 255 / b);
  }
  if (WheelPos < 85) {
    return strip.Color((255 - WheelPos * 3) / b, 0, (WheelPos * 3) / b);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, (WheelPos * 3) / b, (255 - WheelPos * 3) / b);
  }
  WheelPos -= 170;
  return strip.Color((WheelPos * 3) / b, (255 - WheelPos * 3) / b, 0);
}
bool yellowFirst = true;
uint8_t num_colors = 6;
uint8_t counter = 0;
uint32_t colors[] = {
  strip.Color(0xaf, 0x2a, 0xdb), //Abby's favorite purpliness
  strip.Color(0xaf, 0x2a, 0xdb),
  strip.Color(0xaf, 0x2a, 0xdb),
  strip.Color(0xff, 0xff, 0x00), //Yellow
  strip.Color(0xff, 0xff, 0x00),
  strip.Color(0xff, 0xff, 0x00),
};

void loop() {
  checkButton();
  if (mode == 1) {
    modeOne();
  }
  if (mode == 2) {
    modeTwo();
  }
  if (mode == 3) {
    modeThree();
  }
  if (mode == 4) {
    modeFour();
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(25);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 3; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();
      delay(70);
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 3; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void modeOne() {
  theaterChase(strip.Color(0xaf, 0x2a, 0xdb), 50); // Purple
  theaterChase(strip.Color(0xff, 0xff, 0x00), 50); // Yellow
  theaterChase(strip.Color(0xaf, 0x2a, 0xdb), 50); // Purple
  theaterChase(strip.Color(0xff, 0xff, 0x00), 50); // Yellow

  colorWipe(strip.Color(0xff, 0xff, 0x00), 50); // yellow
  colorWipe(strip.Color(0xaf, 0x2a, 0xdb), 50); // purple
  colorWipe(strip.Color(0xff, 0xff, 0x00), 50); // yellow
  colorWipe(strip.Color(0xaf, 0x2a, 0xdb), 50); // purple
}

void modeTwo() {
  rainbowCycle(10);
}

void modeThree() {
  uint32_t purple = strip.Color(0xaf, 0x2a, 0xdb); //Abby's favorite purpliness
  uint32_t yellow = strip.Color(0xff, 0xff, 0x00);
  // strip.setPixelColor(n, red, green, blue);
  for (uint16_t j = 0; j < 10; j++) { // 5 cycles of all colors on wheel
    for (uint8_t i = 0; i < 20; i++) {
      if ((i + counter) % num_colors == 0) {
        strip.setPixelColor(i, purple);
      } else {
        strip.setPixelColor(i, yellow);
      }
      uint8_t color = (((i * 12) + j) & 255);
      if (color == 0 || color == 255) {
        color = 1;                // get rid of white and black
      }
      //strip.setPixelColor(i, /*Wheel(color, 2)*/ strip.Color(0xaf, 0x2a, 0xdb));
    }
    strip.show();
    delay(100);
    counter ++;
    if (counter == num_colors) {
      counter = 0;
    }
  }

  // strip.setPixelColor(n, red, green, blue);
  for (uint16_t j = 0; j < 10; j++) { // 5 cycles of all colors on wheel
    for (uint8_t i = 0; i < 20; i++) {
      if ((i + counter) % num_colors == 0) {
        strip.setPixelColor(i, yellow);
      } else {
        strip.setPixelColor(i, purple);
      }
      uint8_t color = (((i * 12) + j) & 255);
      if (color == 0 || color == 255) {
        color = 1;                // get rid of white and black
      }
      //strip.setPixelColor(i, /*Wheel(color, 2)*/ strip.Color(0xaf, 0x2a, 0xdb));
    }
    strip.show();
    delay(100);
    counter ++;
    if (counter == num_colors) {
      counter = 0;
    }
  }
}

void modeFour() {
  colorWipe(strip.Color(0xff, 0xff, 0x00), 50); // Yellow
  colorWipe(strip.Color(0xaf, 0x2a, 0xdb), 50); // Purple
}

