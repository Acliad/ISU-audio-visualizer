#include <Adafruit_NeoPixel.h>

#define PIN 20
#define START_MARKER 254
#define END_MARKER 255

const int ledCount = 250;

// Flag to track when it's time to update the LED strip
boolean frameReady = false;
// One byte for each of the 3 color components
byte rgbData[3];
// Track the pixel we're updating
byte pixelNumber = 0;

// For debugging
int timeToColor = 0;

// Set up the LED strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(ledCount, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // For debugging
  // Serial.begin(9600);
  // Start the UART
  Serial1.begin(115200);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  getPixelData();
  if(frameReady){
    strip.show();
    pixelNumber = 0;
    frameReady = false;
  }
}

void getPixelData() {
  // This function gets the color for a single pixel,
  // one component at a time.

  static byte index = 0; // Index for RGB component array

  if(Serial1.available() > 0) {
    // If there is Serial data in the buffer
    byte recievedData = Serial1.read();
    Serial.println(recievedData);

    switch (recievedData){
      case START_MARKER:
        // Set up conditions to start recieving a pixel color
        index = 0;
        pixelNumber = 0;
        frameReady = false;
        break;
      case END_MARKER:
        // Done recieving the pixels' colors, ready to proccess
        frameReady = true;
        break;
      default:
        // Add recieved data to buffer
        rgbData[index] = recievedData;
        if(index == 2) {
          // When we have all 3 components, set a pixel
          setPixel();
          index = 0;
        }
        index++;
        break;
  }
  }
}

void setPixel() {
  strip.setPixelColor(pixelNumber, rgbData[0], rgbData[1], rgbData[2]);
  pixelNumber++;
}
