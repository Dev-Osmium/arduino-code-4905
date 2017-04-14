#include <Adafruit_NeoPixel.h>
int i = 0;
int j = 0;
int a = 0;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(20, 6, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}
uint32_t Wheel(uint8_t WheelPos, uint8_t b) {
  if (b < 1) {
    b=1;
  }
  if (b > 128) {
    b=128;
  }
  WheelPos = 255 - WheelPos;
  if(WheelPos == 255) {
    return strip.Color(0, 0, 0);
  }
  if(WheelPos == 0) {
    return strip.Color(255/b, 255/b, 255/b);
  }
  if(WheelPos < 85) {
    return strip.Color((255 - WheelPos * 3)/b, 0, (WheelPos * 3)/b);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, (WheelPos * 3)/b, (255 - WheelPos * 3)/b);
  }
  WheelPos -= 170;
  return strip.Color((WheelPos * 3)/b, (255 - WheelPos * 3)/b, 0);
}
bool yellowFirst = true;
bool first = true;
bool firstTime = true;

void loop() {
  uint32_t purple = strip.Color(0xaf, 0x2a, 0xdb); //Abby's favorite purpliness
  uint32_t yellow = strip.Color(0xff, 0xff, 0x00);
  theaterChase(strip.Color(0xaf, 0x2a, 0xdb), 50); // Purple
  theaterChase(strip.Color(0xff, 0xff, 0x00), 50); // Yellow
  theaterChase(strip.Color(0xaf, 0x2a, 0xdb), 50); // Purple
  theaterChase(strip.Color(0xff, 0xff, 0x00), 50); // Yellow
  colorWipe(strip.Color(0xff, 0xff, 0x00), 50); // yellow
  colorWipe(strip.Color(0xaf, 0x2a, 0xdb),50); // purple
  colorWipe(strip.Color(0xff, 0xff, 0x00), 50); // yellow
  colorWipe(strip.Color(0xaf, 0x2a, 0xdb),50); // purple
  } 
  
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    //strip.setBrightness(50);
    strip.show();
    delay(25);
  }

}
//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<3; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(70);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
 }
