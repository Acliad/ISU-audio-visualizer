#include <Adafruit_NeoPixel.h>

#define PIN 20

Adafruit_NeoPixel strip = Adafruit_NeoPixel(250, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial1.begin(9600);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  if (Serial1.available() > 0)
  {
    int modeNumber = GetMode();
    Serial1.print("Value Serial1 got: ");
    Serial1.println(modeNumber);
    setStripMode(modeNumber);
    delay(250);
  }

}

int GetMode()
{
  int modeNumber = 0;

  while (Serial1.available() > 0)
  {
    char val = Serial1.read();
    modeNumber *= 10;
    modeNumber += (val - '0');
    delay(25);
  }

  return modeNumber;
}

void setStripMode(int mode) {
  switch(mode){
    case 0:
      colorWipe(strip.Color(255, 0, 0), 0); // Red
      colorWipe(strip.Color(0, 255, 0), 0); // Green
      colorWipe(strip.Color(0, 0, 255), 0); // Blue
      break;
    case 1:
      theaterChase(strip.Color(127, 0, 0), 50); // Red
      break;
    case 2:
      rainbow(0);
      rainbowCycle(1);
      break;
    default:
      colorWipe(strip.Color(0,0,0), 0);
      break;
      
  } 
 }
 
 // Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
